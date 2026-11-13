// Alternative: one contiguous block (std::vector<char>) indexed r*cols + c
#include <iostream>
#include <vector>
class Event {
    int rows, cols;
    std::vector<char> seats;
public:
    Event(int r, int c) : rows(r), cols(c), seats(r * c, '.') {}
    bool book(int r, int c) { char& s = seats[r * cols + c]; if (s == 'X') return false; s = 'X'; return true; }
    int size() const { return rows * cols; }
};
int main() {
    Event e(3, 4);
    std::cout << e.book(1, 2) << e.book(1, 2) << " of " << e.size() << " seats (1 allocation, no destructor needed)\n";
}
