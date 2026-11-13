// Alternative design: one constructor with default arguments
#include <iostream>
#include <stdexcept>
#include <string>
class Book {
    std::string title, author;
    int copies;
    static int validate(int c) { if (c < 0) throw std::invalid_argument("copies must be >= 0"); return c; }
public:
    Book(const std::string& t = "Untitled", const std::string& a = "Unknown", int c = 0)
        : title(t), author(a), copies(validate(c)) {}
    void print() const { std::cout << '[' << title << " | " << author << " | copies=" << copies << "]\n"; }
};
int main() {
    Book a("Wings of Fire", "A. P. J. Abdul Kalam", 5), b("Gitanjali"), c;
    a.print(); b.print(); c.print();
    try { Book bad("X", "Y", -1); } catch (const std::invalid_argument& e) { std::cout << "Rejected: " << e.what() << '\n'; }
}
