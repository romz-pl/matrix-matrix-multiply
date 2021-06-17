#include "basic.h"
#include "mtx.h"

int main()
{
    constexpr uint32_t size = 64;
    Mtx a(size), b(size), c(size);

    a.generate();
    b.generate();
    c.zero();

    basic(size, a.data(), b.data(), c.data());
    return 0;
}

