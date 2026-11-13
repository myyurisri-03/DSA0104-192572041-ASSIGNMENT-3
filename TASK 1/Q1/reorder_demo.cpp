// Experiment: members initialised in declaration order, not list order (-Wreorder)
#include <iostream>
struct Bad {
    int first;
    int second;
    Bad() : second(10), first(second * 2) {}   // first is initialised BEFORE second
};
int main() {
    Bad b;
    std::cout << "first=" << b.first << " (garbage), second=" << b.second << '\n';
}
