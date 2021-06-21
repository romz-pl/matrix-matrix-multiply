#include "calc_speed_up.h"
#include "dgemm_avx256.h"
#include "dgemm_avx512.h"
#include "dgemm_unrolled.h"
#include "dgemm_blocked.h"
#include "dgemm_basic.h"
#include "dgemm_basic_blocked.h"
#include "mtx.h"
#include "dgemm_openmp.h"
#include <iostream>
#include <iomanip>
#include "get_timestamp.h"
#include <vector>
#include <string>


using dgemm_function = void (*)(const uint32_t n, const double* a, const double* b, double* c);

static timestamp_t call_dgemm(dgemm_function dgemm)
{
    constexpr uint32_t trial_no = 11;
    constexpr uint32_t n = 32 * 20;
    Mtx a(n), b(n), c(n);

    timestamp_t t{0};

    for(uint32_t i = 0; i < trial_no; i++)
    {
        a.generate();
        b.generate();
        c.zero();

        const timestamp_t t0 = get_timestamp();
        (*dgemm)(n, a.data(), b.data(), c.data());
        const timestamp_t t1 = get_timestamp();
        t += (t1 - t0);
    }
    return t / static_cast<double>(trial_no);

}

class Dgemm
{
public:
    Dgemm(dgemm_function f, const std::string& name)
        : m_f(f)
        , m_name(name)
    {

    }

public:
    dgemm_function m_f;
    const std::string m_name;
    timestamp_t m_epapsed_time{0};
};

void calc_speed_up()
{
    std::vector< Dgemm > all_dgemm =
    {
        {dgemm_basic, "dgemm_basic"},
        {dgemm_basic_blocked, "dgemm_basic_blocked"},
        {dgemm_avx256, "dgemm_avx256"},
        {dgemm_avx512, "dgemm_avx512"},
        {dgemm_unrolled, "dgemm_unrolled"},
        {dgemm_blocked, "dgemm_blocked"},
    };

    for(auto & v : all_dgemm)
    {
        v.m_epapsed_time = call_dgemm(v.m_f);

        std::cout << std::setw(20) << v.m_name << ":  elapsed-time=" << std::setw(10) << v.m_epapsed_time;
        if(v.m_name != "dgemm_basic")
        {
            std::cout << "     speed-up=" << std::setw(10) << all_dgemm[0].m_epapsed_time / static_cast<double>(v.m_epapsed_time);
        }

        std::cout << "\n";
    }

}
