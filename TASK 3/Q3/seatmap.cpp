#include <iostream>
#include <stdexcept>
#include <string>

class Event {
    std::string name;
    int rows, cols;
    char** seats;      // array of row pointers; each row is a char array
    int booked;
public:
    Event(const std::string& nm, int r, int c) : name(nm), rows(r), cols(c), seats(nullptr), booked(0) {
        if (r < 0 || c < 0) throw std::invalid_argument("negative size");
        seats = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            seats[i] = new char[cols];
            for (int j = 0; j < cols; ++j) seats[i][j] = '.';   // '.' = free, 'X' = booked
        }
        std::cout << "+Event " << name << " (" << rows << 'x' << cols << ")\n";
    }
    Event(const Event&) = delete;              // prevent shallow copies
    Event& operator=(const Event&) = delete;

    bool book(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || seats[r][c] == 'X') return false;
        seats[r][c] = 'X'; ++booked; return true;
    }
    bool cancel(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || seats[r][c] != 'X') return false;
        seats[r][c] = '.'; --booked; return true;
    }
    ~Event() {
        for (int i = 0; i < rows; ++i) delete[] seats[i];   // release every row
        delete[] seats;                                     // then the row-pointer array
        std::cout << "-Event " << name << " summary: " << booked << " of " << rows * cols << " seats booked\n";
    }
};

int main() {
    Event stackEv("Stack", 2, 3);
    stackEv.book(0, 1);
    {
        Event blockEv("Block", 1, 2);
        blockEv.book(0, 0); blockEv.book(0, 1); blockEv.cancel(0, 1);
    }                                   // blockEv destroyed here
    Event* heapEv = new Event("Heap", 3, 3);
    heapEv->book(2, 2);
    delete heapEv;                      // destroyed here
    Event empty("Empty", 0, 5);         // zero rows test
}
