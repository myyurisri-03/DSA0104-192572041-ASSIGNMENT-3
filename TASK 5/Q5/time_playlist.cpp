#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Time {
    int h, m, s;
public:
    Time(int hh = 0, int mm = 0, int ss = 0) : h(hh), m(mm), s(ss) {}
    Time& operator++() {                       // prefix: increment, return the new value
        if (++s == 60) { s = 0; if (++m == 60) { m = 0; ++h; } }
        return *this;
    }
    Time operator++(int) {                     // postfix: dummy int, return the OLD value
        Time old = *this;
        ++(*this);
        return old;
    }
    bool operator==(const Time& o) const { return h == o.h && m == o.m && s == o.s; }
    bool operator<(const Time& o) const {
        if (h != o.h) return h < o.h;
        if (m != o.m) return m < o.m;
        return s < o.s;
    }
    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        return os << t.h << ':' << (t.m < 10 ? "0" : "") << t.m << ':' << (t.s < 10 ? "0" : "") << t.s;
    }
};

class Playlist {
    std::vector<std::string> tracks;
public:
    void add(const std::string& t) { tracks.push_back(t); }
    int size() const { return static_cast<int>(tracks.size()); }
    std::string& operator[](int i) {                     // non-const: can modify the track
        if (i < 0 || i >= size()) throw std::out_of_range("playlist index out of range");
        return tracks[i];
    }
    const std::string& operator[](int i) const {         // const: read-only access
        if (i < 0 || i >= size()) throw std::out_of_range("playlist index out of range");
        return tracks[i];
    }
};

int main() {
    Time t(0, 59, 58);
    Time a = t++;            // a = 0:59:58, t = 0:59:59
    Time b = ++t;            // t = 1:00:00, b = 1:00:00
    std::cout << "a=" << a << " b=" << b << " t=" << t << '\n';
    std::cout << std::boolalpha << (a < b) << ' ' << (b == t) << '\n';

    Playlist playlist;
    playlist.add("Track 1"); playlist.add("Track 2");
    const Playlist& view = playlist;
    std::cout << playlist[0] << ' ' << view[1] << '\n';
    try { playlist[-1]; } catch (const std::out_of_range& e) { std::cout << "Error: " << e.what() << '\n'; }
    try { playlist[playlist.size()]; } catch (const std::out_of_range& e) { std::cout << "Error: " << e.what() << '\n'; }
}
