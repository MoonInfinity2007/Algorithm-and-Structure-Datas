#include <iostream>
#include <vector>
#include <string>

#define LL long long

int main() {
    std::string s;
    std::vector<LL> v = {};
    int l = 0, r = 0;
    while (s != "exit") {
        if (s == "push") {
            LL x;
            std::cin >> x;
            ++r;
            if (r > v.size()) v.push_back(x);
            else v[r - 1] = x;
            std::cout << "ok\n";
        } else if (s == "pop") {
            if (r - l <= 0) std::cout << "error\n";
            else {
                std::cout << v[l] << "\n";
                ++l;
            }
        } else if (s == "front") {
            if (r - l <= 0) std::cout << "error\n";
            else std::cout << v[l] << "\n";
        } else if (s == "size") std::cout << r - l << "\n";
        else if (s == "clear") {
            v.clear();
            l = 0;
            r = 0;
            std::cout << "ok\n";
        }
        std::cin >> s;
    }
    std::cout << "bye";
}