#include <iostream>
#include <deque>
#include <string>

void perm(int N, int K, std::deque<int>& st) {
    std::string s = "0123456789abcdefghijklmnopqrstuvwxyz";
    for (int i = K - 1; i >= 0; --i) {
        st.push_back(i);
        if (N > 1) perm(N - 1, K, st);
        else {
            std::deque<int> dst(st);
            while (!dst.empty()) {
                std::cout << s[dst.front()];
                dst.pop_front();
            }
            std::cout << "\n";
        }
        st.pop_back();
    }
}

int main() {
    int N, K;
    std::cin >> N >> K;
    std::deque<int> st;
    perm(N, K, st);
}