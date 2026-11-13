// Alternative: std::complex<double>
#include <complex>
#include <iostream>
int main() {
    using Z = std::complex<double>;
    Z R(10, 0), XL(0, 10), XC(0, -20);
    Z series = R + XL + XC;
    Z par = ((R * XL) / (R + XL)) * XC / (((R * XL) / (R + XL)) + XC);
    std::cout << "Series   : " << series << "  |Z| = " << std::abs(series) << '\n';
    std::cout << "Parallel : " << par << "  |Z| = " << std::abs(par) << '\n';
    Z bad = R / Z(0, 0);     // no exception: returns inf/nan
    std::cout << "R / 0    : " << bad << '\n';
}
