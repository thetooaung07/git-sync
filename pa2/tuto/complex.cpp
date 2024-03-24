//
// Created by Thet Oo Aung on 29/02/2024.
//

#include "cassert"
#include "iostream"

class Complex {
public:
    double mReal, mImag;

    Complex(double real = 0, double imag = 0) {
        mReal = real;
        mImag = imag;
    }

    [[nodiscard]]  Complex add(const Complex &other) const {
        return Complex{mReal + other.mReal, mImag + other.mImag};
    }

    void print(std::ostream &os) const {
        os << "[" << mReal << ", " << mImag << "]";
    }


};

int main() {
    const Complex x(1, 2);
    const Complex y(5);

    Complex z = x.add(y);
    assert(z.mReal == 6 && z.mImag == 2);
    return 0;
}
