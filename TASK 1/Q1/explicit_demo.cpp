// Experiment: explicit constructor. Compile as is (works). Then add 'explicit' to Book(std::string)
// and the call shelve(std::string("Gitanjali")) fails to compile.
#include <iostream>
#include <string>
class Book {
    std::string title;
public:
#ifdef USE_EXPLICIT
    explicit
#endif
    Book(const std::string& t) : title(t) {}
    const std::string& getTitle() const { return title; }
};
void shelve(const Book& b) { std::cout << "Shelved: " << b.getTitle() << '\n'; }
int main() {
    shelve(std::string("Gitanjali"));   // implicit conversion string -> Book
}
