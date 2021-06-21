#include "check.h"
#include "dgemm_avx256.h"
#include "dgemm_avx512.h"
#include "dgemm_unrolled.h"
#include "dgemm_blocked.h"
#include "dgemm_basic.h"
#include "dgemm_basic_blocked.h"
#include "dgemm_openmp.h"
#include "mtx.h"
#include <iostream>
#include <vector>
#include <string>


using dgemm_function = void (*)(const uint32_t n, const double* a, const double* b, double* c);

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
};


static double calc_abs_sum(const uint32_t n, const double* c, const double* q)
{
    double ret{ 0.0 };
    for(uint32_t i = 0; i < n * n; i++)
    {
        ret += std::abs(c[i] - q[i]);
    }
    return ret;
}

void check()
{
    constexpr uint32_t trial_no = 11;
    constexpr uint32_t n = 32 * 4;
    constexpr double eps = 1e-6;

    std::vector< Dgemm > all_dgemm =
    {
        {dgemm_basic_blocked, "dgemm_basic_blocked"},
        {dgemm_avx256, "dgemm_avx256"},
        {dgemm_avx512, "dgemm_avx512"},
        {dgemm_unrolled, "dgemm_unrolled"},
        {dgemm_blocked, "dgemm_blocked"},
    };


    Mtx a(n), b(n);
    Mtx c_basic(n);
    Mtx c(n);

    for(uint32_t i = 0; i < trial_no; i++)
    {
        a.generate();
        b.generate();
        c.zero();
        c_basic.zero();

        dgemm_basic(n, a.data(), b.data(), c_basic.data());

        for(auto & e : all_dgemm)
        {
            c.zero();

            (*e.m_f)(n, a.data(), b.data(), c.data());
            const double abs_sum = calc_abs_sum(n, c.data(), c_basic.data());
            if(abs_sum > eps)
            {
                std::cout << abs_sum << "  Error in algorithm " << e.m_name << "\n";
            }
        }
    }
}
