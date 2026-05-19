#include <iostream>
#include <cstdint>
#include <deque>

int main() {
    int64_t n;
    std::cin >> n;
    std::deque<int64_t> q;
    int64_t cur_time = 0;
    for (int64_t i = 0; i < n; ++i) {
        int64_t h = 0, m = 0, angry = 0;
        std::cin >> h >> m >> angry;
        int64_t t = h * 60 + m;
        while (!q.empty() && q.front() < t) {
            std::cout << q.front() / 60 << " " << q.front() % 60;
            q.pop_front();
        }
        if (q.empty()) q.push_back(t + 20);
        else if (q.size() <= angry) q.push_back(q.back() + 20);
        else std::cout <<
    }
    while (!q.empty() && q.front() < t) {
            std::cout << q.front() / 60 << " " << q.front() % 60;
            q.pop_front();
        }
}