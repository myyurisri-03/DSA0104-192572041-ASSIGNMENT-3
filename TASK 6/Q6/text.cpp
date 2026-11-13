#include <chrono>
#include <cstring>
#include <iostream>
#include <string>

class Text {
    char* data;
    std::size_t len;
public:
    static int copies;
    Text(const char* s = "") : data(new char[std::strlen(s) + 1]), len(std::strlen(s)) {
        std::memcpy(data, s, len + 1);
    }
    Text(const Text& o) : data(new char[o.len + 1]), len(o.len) {
        std::memcpy(data, o.data, len + 1);
        ++copies;
    }
    Text& operator=(const Text& o) {
        if (this != &o) {                          // self-assignment guard
            char* fresh = new char[o.len + 1];
            std::memcpy(fresh, o.data, o.len + 1);
            delete[] data;
            data = fresh; len = o.len;
        }
        return *this;
    }
    ~Text() { delete[] data; }

    friend Text operator+(const Text& a, const Text& b) {
        char* buf = new char[a.len + b.len + 1];
        std::memcpy(buf, a.data, a.len);
        std::memcpy(buf + a.len, b.data, b.len + 1);
        Text r(buf);
        delete[] buf;
        return r;
    }
    friend bool operator==(const Text& a, const Text& b) { return std::strcmp(a.data, b.data) == 0; }
    friend bool operator!=(const Text& a, const Text& b) { return !(a == b); }
    friend std::ostream& operator<<(std::ostream& os, const Text& t) { return os << t.data; }
};
int Text::copies = 0;

int main() {
    Text a("Hello, "), b("SMS "), c("Gateway");
    Text d = a + b + c;
    std::cout << d << '\n';
    std::cout << std::boolalpha << (d == Text("Hello, SMS Gateway")) << ' ' << (a != b) << '\n';
    Text empty;
    std::cout << '[' << empty << "]\n";
    d = d;                                          // self-assignment test
    std::cout << d << '\n';

    std::cout << "Copy-constructor calls so far: " << Text::copies << '\n';

    // long message test
    Text longMsg;
    for (int i = 0; i < 1000; ++i) longMsg = longMsg + Text("0123456789");
    std::cout << "Long message built (10,000 characters)\n";

#ifndef NO_BENCH
    // timing: 100,000 concatenations, Text vs std::string
    using clk = std::chrono::steady_clock;
    auto t0 = clk::now();
    Text t;
    for (int i = 0; i < 100000; ++i) t = t + Text("x");
    auto t1 = clk::now();
    std::string s;
    for (int i = 0; i < 100000; ++i) s = s + "x";
    auto t2 = clk::now();
    std::cout << "Text        (t = t + x) x100000 : " << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms\n";
    std::cout << "std::string (s = s + x) x100000 : " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";
#endif
}
