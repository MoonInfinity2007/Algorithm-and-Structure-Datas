#include <iostream>
#include <cstdint>
#include <stack>
#include <string>

int main() {
    int64_t n;
    std::cin >> n;
    std::stack<std::pair<std::string, std::string>> in, out;
    for (int64_t i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        if (s == "push") {
            std::cin >> s;
            if (in.empty()) in.push({s, s});
            else in.push({s, std::min(s, in.top().second)});
        } else {
            if (out.empty()) {
                while (!in.empty()) {
                    std::string mi = in.top().first;
                    if (!out.empty()) mi = std::min(mi, out.top().second); 
                    out.push({in.top().first, mi});
                    in.pop();
                }
            }
            if (s == "pop") out.pop();
            else {
                if (in.empty()) std::cout << out.top().second << "\n";
                else std::cout << std::min(out.top().second, in.top().second) << "\n";
            }
        }
    }

}