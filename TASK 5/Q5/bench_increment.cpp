// Times 10,000,000 prefix vs postfix increments and checked vs unchecked access.
// Build once with -O0 and once with -O2.
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <vector>

struct Time {
    int h = 0, m = 0, s = 0;
    Time& operator++() { if (++s == 60) { s = 0; if (++m == 60) { m = 0; ++h; } } return *this; }
    Time operator++(int) { Time old = *this; ++(*this); return old; }
};

int main() {
    const int N = 10000000;
    using clk = std::chrono::steady_clock;

    Time t1;
    auto a0 = clk::now();
    for (int i = 0; i < N; ++i) ++t1;
    auto a1 = clk::now();
    Time t2;
    for (int i = 0; i < N; ++i) t2++;
    auto a2 = clk::now();
    std::cout << "prefix  ++t : " << std::chrono::duration<double, std::milli>(a1 - a0).count() << " ms  (h=" << t1.h << ")\n";
    std::cout << "postfix t++ : " << std::chrono::duration<double, std::milli>(a2 - a1).count() << " ms  (h=" << t2.h << ")\n";

    std::vector<int> v(1000, 1);
    long long sum = 0;
    auto b0 = clk::now();
    for (int i = 0; i < N; ++i) { int k = i % 1000; if (k < 0 || k >= 1000) throw std::out_of_range("x"); sum += v[k]; }
    auto b1 = clk::now();
    for (int i = 0; i < N; ++i) sum += v[i % 1000];
    auto b2 = clk::now();
    std::cout << "checked access   : " << std::chrono::duration<double, std::milli>(b1 - b0).count() << " ms\n";
    std::cout << "unchecked access : " << std::chrono::duration<double, std::milli>(b2 - b1).count() << " ms  (sum=" << sum << ")\n";
}
