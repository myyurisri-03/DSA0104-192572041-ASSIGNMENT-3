// Experiment: default constructor removed -> array of Books does not compile
#include <string>
class Book {
    std::string title; int copies;
public:
    Book(const std::string& t, int c) : title(t), copies(c) {}
};
int main() {
    Book shelf[3];      // ERROR: no matching function for call to 'Book::Book()'
    (void)shelf;
}
