#include <cstdint>

//
// Squared matrix.
// The mumber of rows is equal to the number of columns.
//

class Mtx
{
public:

    Mtx(uint32_t n);
    ~Mtx();


    Mtx(const Mtx&) = delete;
    Mtx(Mtx&&) = delete;

    Mtx& operator=(const Mtx&) = delete;
    Mtx& operator=(Mtx&&) = delete;

    const double* data() const { return m_data; }
    double* data() { return m_data; }

    void generate(double min_val = 1.0, double max_val = 10.0);
    void zero();

private:
    double* m_data{nullptr};

    // The mumber of rows is equal to the number of columns.
    const uint32_t m_n;
};
