#include "avx256.h"
#include "basic.h"
#include "mtx.h"
#include <iostream>
#include "get_timestamp.h"

double calc_abs_sum(const uint32_t n, double* c, double* q)
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
    constexpr uint32_t n = 64;
    Mtx a(n), b(n);

    a.generate();
    b.generate();

    Mtx c_basic(n);
    c_basic.zero();


        const timestamp_t t0 = get_timestamp();
        basic(n, a.data(), b.data(), c_basic.data());
        const timestamp_t t1 = get_timestamp();
        std::cout << "Elapsed time (in microseconds) for `basic`: " << t1 - t0 << "\n";
    


    Mtx c_avx256(n);
    c_avx256.zero();
    //avx256(n, a.data(), b.data(), c_avx256.data());

    const double abs_sum = calc_abs_sum(n, c_basic.data(), c_avx256.data());

    // std::cout << std::scientific;
    std::cout << abs_sum << "\n";
    return 0;
}

