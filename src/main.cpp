#include "avx256.h"
#include "avx512.h"
#include "avx512_subword_parallel.h"
#include "basic.h"
#include "mtx.h"
#include <iostream>
#include "get_timestamp.h"

double calc_abs_sum(const uint32_t n, const double* c, const double* q)
{
    double ret{ 0.0 };
    for(uint32_t i = 0; i < n * n; i++)
    {
        ret += std::abs(c[i] - q[i]);
    }
    return ret;
}

int main()
{
    constexpr uint32_t n = 1024;
    Mtx a(n), b(n);

    a.generate();
    b.generate();

    Mtx c_basic(n);
    c_basic.zero();


    timestamp_t t0 = get_timestamp();
    basic(n, a.data(), b.data(), c_basic.data());
    timestamp_t t1 = get_timestamp();
    const timestamp_t t_basic = t1 - t0;
    std::cout << "Elapsed time (in microseconds) for `basic`: " << t_basic << "\n";
    


    Mtx c_avx256(n);
    c_avx256.zero();
    t0 = get_timestamp();
    avx256(n, a.data(), b.data(), c_avx256.data());
    t1 = get_timestamp();
    const timestamp_t t_avx256 = t1 - t0;
    std::cout << "Elapsed time (in microseconds) for `avx256`: " << t_avx256 << "\n";
    std::cout << "Time-for-basic / Time-for-avx256 = " << t_basic / static_cast<double>(t_avx256) << "\n";

    const double abs_sum_avx256 = calc_abs_sum(n, c_basic.data(), c_avx256.data());
    std::cout << abs_sum_avx256 << "\n";


    Mtx c_avx512(n);
    c_avx512.zero();
    t0 = get_timestamp();
    avx512(n, a.data(), b.data(), c_avx512.data());
    t1 = get_timestamp();
    const timestamp_t t_avx512 = t1 - t0;
    std::cout << "Elapsed time (in microseconds) for `avx512`: " << t_avx512 << "\n";
    std::cout << "Time-for-basic / Time-for-avx512 = " << t_basic / static_cast<double>(t_avx512) << "\n";
    const double abs_sum_avx512 = calc_abs_sum(n, c_basic.data(), c_avx512.data());
    std::cout << abs_sum_avx512 << "\n";


    Mtx c_avx512_sp(n);
    c_avx512_sp.zero();
    t0 = get_timestamp();
    avx512_subword_parallel(n, a.data(), b.data(), c_avx512_sp.data());
    t1 = get_timestamp();
    const timestamp_t t_avx512_sp = t1 - t0;
    std::cout << "Elapsed time (in microseconds) for `avx512_subword_parallel`: " << t_avx512_sp << "\n";
    std::cout << "Time-for-basic / Time-for-avx512_sp = " << t_basic / static_cast<double>(t_avx512_sp) << "\n";
    const double abs_sum_avx512_sp = calc_abs_sum(n, c_basic.data(), c_avx512_sp.data());
    std::cout << abs_sum_avx512_sp << "\n";




    return 0;
}

