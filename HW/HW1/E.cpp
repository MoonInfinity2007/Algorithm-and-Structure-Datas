#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <algorithm> 

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, x;
    std::cin >> N;
    std::stack<std::pair<int, int>> st;
    std::string s;
    for (int i = 0; i < N; ++i) {
        std::cin >> s;
        if (s == "push") {
            std::cin >> x;
            if (st.empty()) st.push({x, x});
            else st.push({x, std::max(x, st.top().second)});
        } else if (s == "pop") st.pop();
        else std::cout << st.top().second << "\n";
    }
}