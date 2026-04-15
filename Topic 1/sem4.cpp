#include <random>
#include <iostream>
#include <vector>
#include <ctime>
#include <queue>

std::mt19937 rd(time(nullptr));

int main() {
    size_t n = 20;
    std::vector<int> v(n);
    for (auto& item: v) {
        item = rd() % 100;
    }
    for (int k = 0; k < sizeof(int); ++k) {
        std::vector<std::queue<int>> buckets(255);
        for (int item : v) {
            int num = (item >> k * 8) & 255;
            buckets[num].push(item);
        }
        size_t i = 0;
        for (auto& q: buckets) {
            while (!q.empty()) {
                v[i] = q.front();
                q.pop();
                i++;
            }
        }
    } 
}
