#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}
    Complex(double r) : re(r), im(0) {}                  // implicit: allows 5 + z
    Complex(double r, double i) : re(r), im(i) {}

    double magnitude() const { return std::hypot(re, im); }
    bool operator==(const Complex& o) const {
        return std::fabs(re - o.re) < 1e-9 && std::fabs(im - o.im) < 1e-9;
    }

    friend Complex operator+(const Complex& a, const Complex& b) { return Complex(a.re + b.re, a.im + b.im); }
    friend Complex operator-(const Complex& a, const Complex& b) { return Complex(a.re - b.re, a.im - b.im); }
    friend Complex operator*(const Complex& a, const Complex& b) {
        return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
    }
    friend Complex operator/(const Complex& a, const Complex& b) {
        double d = b.re * b.re + b.im * b.im;
        if (d == 0.0) throw std::domain_error("division by zero impedance");
        return Complex((a.re * b.re + a.im * b.im) / d, (a.im * b.re - a.re * b.im) / d);
    }
    friend std::ostream& operator<<(std::ostream& os, const Complex& z) {
        return os << std::fixed << std::setprecision(4) << z.re
                  << (z.im < 0 ? " - " : " + ") << std::fabs(z.im) << 'j';
    }
};

Complex parallel(const Complex& a, const Complex& b) { return (a * b) / (a + b); }

int main() {
    const double w = 100.0, Rv = 10.0, L = 0.1, C = 500e-6;
    Complex R(Rv), XL(0, w * L), XC(0, -1.0 / (w * C));

    Complex series = R + XL + XC;
    std::cout << "Series   : " << series << "  |Z| = " << series.magnitude() << '\n';

    Complex par = parallel(parallel(R, XL), XC);
    std::cout << "Parallel : " << par << "  |Z| = " << par.magnitude() << '\n';

    std::cout << std::boolalpha << (par == Complex(8, 4)) << '\n';

    try {
        Complex bad = R / Complex(0, 0);
        std::cout << bad << '\n';
    } catch (const std::domain_error& e) {
        std::cout << "Error: " << e.what() << '\n';
    }
}
