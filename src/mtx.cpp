#include "mtx.h"
#include <random>
#include <cassert>
#include <algorithm>
#include <immintrin.h>

Mtx::Mtx(uint32_t n)
    : m_n(n)
{
    // m_data = new double[n * n];
    m_data = (double*) _mm_malloc (n * n * sizeof(double), 64);
    if (m_data == nullptr) 
        throw std::bad_alloc{}; // ("failed to allocate largest problem size");
}

Mtx::~Mtx()
{
    // delete[] m_data;
    free(m_data);
}

void Mtx::generate(double min_val, double max_val)
{   
    assert(max_val > min_val);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min_val, max_val);
    for(uint32_t i = 0; i < m_n * m_n; ++i)
    {
        m_data[i] = dis(gen);
    }
}

void Mtx::zero()
{
    std::fill(m_data, m_data + m_n * m_n, 0);
}

