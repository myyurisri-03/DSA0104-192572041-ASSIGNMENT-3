// Bill calculation with operators + comparison with a double-based version (1,000,000 additions)
#include <chrono>
#include <iomanip>
#include <iostream>

class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}
    Money operator+(const Money& o) const { Money r; r.paise = paise + o.paise; return r; }
    Money operator-(const Money& o) const { Money r; r.paise = paise - o.paise; return r; }
    Money& operator+=(const Money& o) { paise += o.paise; return *this; }
    bool operator<(const Money& o) const { return paise < o.paise; }
    bool operator==(const Money& o) const { return paise == o.paise; }
    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long v = m.paise; if (v < 0) { os << '-'; v = -v; }
        char old = os.fill('0'); os << "Rs " << v / 100 << '.' << std::setw(2) << v % 100; os.fill(old); return os;
    }
};

int main() {
    Money price(499, 50), tax(89, 91), discount(50);
    Money total = price + tax - discount;               // readable bill code
    std::cout << "Bill total: " << total << '\n';

    auto t0 = std::chrono::steady_clock::now();
    Money m;
    for (int i = 0; i < 1000000; ++i) m += Money(0, 10);
    auto t1 = std::chrono::steady_clock::now();
    double d = 0.0;
    for (int i = 0; i < 1000000; ++i) d += 0.10;
    auto t2 = std::chrono::steady_clock::now();

    std::cout << "Money  after 1,000,000 x Rs 0.10 : " << m << "  ("
              << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms)\n";
    std::cout << std::setprecision(12) << "double after 1,000,000 x 0.10    : " << d << "  ("
              << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms)\n";
    std::cout << "double error = " << d - 100000.0 << '\n';
}
