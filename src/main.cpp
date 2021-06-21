#include "calc_speed_up.h"
#include "check.h"

int main()
{
    check();
    calc_speed_up();
    return 0;

    // const double abs_sum_avx256 = calc_abs_sum(n, c_basic.data(), c_avx256.data());
    // std::cout << abs_sum_avx256 << "\n";
}

