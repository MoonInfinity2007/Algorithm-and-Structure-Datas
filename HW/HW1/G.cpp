#include <stack>
#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N;
    std::cin >> N;
    std::string s;
    int x;
    std::stack<std::pair<int, int>> in, out;
    for (int i = 0; i < N; ++i) {
        std::cin >> s;
        if (s == "+") {
            std::cin >> x;
            if (in.empty()) in.push({x, x});
            else in.push({x, std::min(x, in.top().second)});
        } else {
            if (out.empty()) {
                int mi;
                while (!in.empty()) {
                    if (out.empty()) mi = in.top().first;
                    else mi = std::min(in.top().first, out.top().second);
                    out.push({in.top().first, mi});
                    in.pop();
                }
            }
            if (in.empty()) std::cout << out.top().second << " " << out.top().first << "\n";
            else std::cout << std::min(in.top().second, out.top().second) << " " << out.top().first << "\n";
            out.pop();
        }
    }
}