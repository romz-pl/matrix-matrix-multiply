#include "avx256.h"
#include "avx512.h"
#include "avx512_subword_parallel.h"
#include "avx512_blocked.h"
#include "basic.h"
#include "basic_blocked.h"
#include "mtx.h"
#include "dgemm_openmp.h"
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
    constexpr uint32_t n = 32*30;
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

    Mtx c_blocked(n);
    c_blocked.zero();
    t0 = get_timestamp();
    basic_blocked(n, a.data(), b.data(), c_blocked.data());
    t1 = get_timestamp();
    const timestamp_t t_blocked = t1 - t0;
    std::cout << "Elapsed time (in microseconds) for `bacis_blocked`: " << t_blocked << "\n";
    std::cout << "Time-for-basic / Time-for-basic_blocked = " << t_basic / static_cast<double>(t_blocked) << "\n";
    const double abs_sum_blocked = calc_abs_sum(n, c_basic.data(), c_blocked.data());
    std::cout << abs_sum_blocked << "\n";


    Mtx c_avx512_blocked(n);
    c_blocked.zero();
    t0 = get_timestamp();
    avx512_blocked(n, a.data(), b.data(), c_avx512_blocked.data());
    t1 = get_timestamp();
    const timestamp_t t_avx512_blocked = t1 - t0;
    std::cout << "Elapsed time (in microseconds) for `avx512_blocked`: " << t_avx512_blocked << "\n";
    std::cout << "Time-for-basic / Time-for-avx512_blocked = " << t_basic / static_cast<double>(t_avx512_blocked) << "\n";
    const double abs_sum_avx512_blocked = calc_abs_sum(n, c_basic.data(), c_avx512_blocked.data());
    std::cout << abs_sum_avx512_blocked << "\n";

    Mtx c_openmp(n);
    c_openmp.zero();
    t0 = get_timestamp();
    dgemm_openmp(n, a.data(), b.data(), c_openmp.data());
    t1 = get_timestamp();
    const timestamp_t t_openmp = t1 - t0;
    std::cout << "Elapsed time (in microseconds) for `openMP`: " << t_openmp << "\n";
    std::cout << "Time-for-basic / Time-for-openmp = " << t_basic / static_cast<double>(t_openmp) << "\n";
    const double abs_sum_openmp = calc_abs_sum(n, c_basic.data(), c_openmp.data());
    std::cout << abs_sum_openmp << "\n";


    return 0;
}

