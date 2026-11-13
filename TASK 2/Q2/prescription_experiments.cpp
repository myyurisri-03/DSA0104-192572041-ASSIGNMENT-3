// Experiments: copy counting, timing of deep copies, self-assignment
#include <chrono>
#include <iostream>
#include <string>

class Prescription {
    int n;
    std::string* medicines;
public:
    static int copies;
    explicit Prescription(int count) : n(count), medicines(new std::string[count]) {}
    Prescription(const Prescription& o) : n(o.n), medicines(new std::string[o.n]) {
        ++copies; std::cout << "  [copy constructor called]\n";
        for (int i = 0; i < n; ++i) medicines[i] = o.medicines[i];
    }
    Prescription& operator=(const Prescription& o) {
        if (this != &o) {
            std::string* fresh = new std::string[o.n];
            for (int i = 0; i < o.n; ++i) fresh[i] = o.medicines[i];
            delete[] medicines; medicines = fresh; n = o.n;
        }
        return *this;
    }
    ~Prescription() { delete[] medicines; }
    void set(int i, const std::string& m) { medicines[i] = m; }
    std::string get(int i) const { return medicines[i]; }
    int size() const { return n; }
};
int Prescription::copies = 0;

void byValue(Prescription p) { (void)p; }
void byConstRef(const Prescription& p) { (void)p; }

int main() {
    Prescription p(3);
    p.set(0, "A"); p.set(1, "B"); p.set(2, "C");

    std::cout << "Pass by value:\n";      byValue(p);
    std::cout << "Pass by const reference:\n"; byConstRef(p);
    std::cout << "Total copies = " << Prescription::copies << " (expected 1)\n\n";

    p = p;   // self-assignment test
    std::cout << "After p = p : " << p.get(0) << p.get(1) << p.get(2) << " (unchanged)\n\n";

    std::cout << "Deep-copy timing (average of 20 copies, copy messages suppressed in count)\n";
    int sizes[] = {10, 1000, 100000};
    for (int n : sizes) {
        std::streambuf* old = std::cout.rdbuf(nullptr);   // silence copy messages while timing
        Prescription big(n);
        for (int i = 0; i < n; ++i) big.set(i, "Medicine");
        auto t0 = std::chrono::steady_clock::now();
        for (int k = 0; k < 20; ++k) { Prescription c(big); }
        auto t1 = std::chrono::steady_clock::now();
        std::cout.rdbuf(old);
        double us = std::chrono::duration<double, std::micro>(t1 - t0).count() / 20.0;
        std::cout << "n = " << n << " : " << us << " microseconds per copy\n";
    }
}
