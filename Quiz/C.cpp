#include <iostream>
#include <stack>
#include <string>
#include <map>

int main() {
    int N, x;
    std::cin >> N;
    std::stack<int> st;
    int mi = 1e9;
    std::string s;
    int r = 0;
    std::map<int, int> mp;
    for (int i = 0; i < N; ++i) {
        std::cin >> s;
        if (s == "push") {
            std::cin >> x;
            st.push(x);
            if (mp.count(x) < 1) mp[x] = 0;
            mp[x] += 1;
        } else if (s == "pop") {
            mp[st.top()] -= 1;
            st.pop();
        } else {
            for (auto elem : mp) {
                if (elem.second != 0) {
                    std::cout << elem.first << "\n";
                    break;
                }
            }
        }
    }
}