// PROBLEM VERSION: no copy constructor, no copy assignment (compiler-generated shallow copies).
// Run under -fsanitize=address to see the double-free.
#include <iostream>
#include <string>

class Prescription {
    int n;
    std::string* medicines;
public:
    explicit Prescription(int count) : n(count), medicines(new std::string[count]) {}
    ~Prescription() { delete[] medicines; }
    void set(int i, const std::string& m) { medicines[i] = m; }
    std::string get(int i) const { return medicines[i]; }
};

int main() {
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");
    Prescription q = p;      // shallow copy: q.medicines == p.medicines
    q.set(1, "Cetirizine");  // also changes p!
    std::cout << p.get(0) << ' ' << p.get(1) << " | " << q.get(0) << ' ' << q.get(1) << '\n';
}   // p and q both delete[] the same array -> double free
