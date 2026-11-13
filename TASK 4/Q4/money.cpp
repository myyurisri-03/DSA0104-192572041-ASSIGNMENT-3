#include <iomanip>
#include <iostream>

class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    // TODO 1: + as a member function that returns a new Money object
    Money operator+(const Money& o) const { Money r; r.paise = paise + o.paise; return r; }
    Money operator-(const Money& o) const { Money r; r.paise = paise - o.paise; return r; }
    Money& operator+=(const Money& o) { paise += o.paise; return *this; }
    bool operator<(const Money& o) const { return paise < o.paise; }

    // TODO 2: == as a member, << as a friend that prints "Rs 200.00"
    bool operator==(const Money& o) const { return paise == o.paise; }

    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        long long v = m.paise;
        if (v < 0) { os << '-'; v = -v; }
        char old = os.fill('0');
        os << "Rs " << v / 100 << '.' << std::setw(2) << v % 100;
        os.fill(old);
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Money& m) {
        long long r; int p;
        if (is >> r >> p) m = Money(r, p);
        return is;
    }
};

int main() {
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    std::cout << Money(0, 75) + Money(0, 50) << '\n';   // carry test: Rs 1.25
    std::cout << Money(5) - Money(8, 50) << '\n';        // negative: -Rs 3.50
}
