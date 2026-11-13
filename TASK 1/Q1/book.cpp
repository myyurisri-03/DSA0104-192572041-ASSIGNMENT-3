#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    std::string author;
    int copies;

    static int validate(int c) {
        if (c < 0) throw std::invalid_argument("copies must be >= 0");
        return c;
    }
public:
    Book(const std::string& t, const std::string& a, int c)
        : title(t), author(a), copies(validate(c)) {}                 // target constructor
    explicit Book(const std::string& t) : Book(t, "Unknown", 1) {}    // donated book
    Book() : Book("Untitled", "Unknown", 0) {}                        // empty record

    void print() const {
        std::cout << '[' << title << " | " << author << " | copies=" << copies << "]\n";
    }
};

int main() {
    Book a("Wings of Fire", "A. P. J. Abdul Kalam", 5);
    Book b("Gitanjali");
    Book c;
    a.print(); b.print(); c.print();
    try {
        Book bad("Broken", "Nobody", -3);
    } catch (const std::invalid_argument& e) {
        std::cout << "Rejected: " << e.what() << '\n';
    }
}
