// Counts bytes requested by operator new[] for different seat-map sizes
#include <cstdio>
#include <cstdlib>
#include <new>
static size_t total = 0;
void* operator new[](size_t n) { total += n; return std::malloc(n); }
void operator delete[](void* p) noexcept { std::free(p); }
void operator delete[](void* p, size_t) noexcept { std::free(p); }

void build(int rows, int cols) {
    total = 0;
    char** seats = new char*[rows];
    for (int i = 0; i < rows; ++i) seats[i] = new char[cols];
    std::printf("%5d x %-5d : %zu bytes requested in %d allocations (rows*(8+cols) = %d)\n",
                rows, cols, total, rows + 1, rows * (8 + cols));
    for (int i = 0; i < rows; ++i) delete[] seats[i];
    delete[] seats;
}
int main() { build(10, 20); build(100, 200); build(1000, 2000); }
