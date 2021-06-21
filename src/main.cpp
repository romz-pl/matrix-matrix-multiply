#include "calc_speed_up.h"

/*
double calc_abs_sum(const uint32_t n, const double* c, const double* q)
{
    double ret{ 0.0 };
    for(uint32_t i = 0; i < n * n; i++)
    {
        ret += std::abs(c[i] - q[i]);
    }
    return ret;
}
*/

int main()
{

    calc_speed_up();
    return 0;

    // const double abs_sum_avx256 = calc_abs_sum(n, c_basic.data(), c_avx256.data());
    // std::cout << abs_sum_avx256 << "\n";
}

