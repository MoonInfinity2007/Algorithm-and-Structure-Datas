#include <iostream>
#include <deque>


void perm(int N, int K, std::deque<int>& st) {
    for (int i = 0; i < K; ++i) {
        st.push_back(i + 1);
        if (N > 1) perm(N - 1, K, st);
        else {
            std::deque<int> dst(st);
            while (!dst.empty()) {
                std::cout << dst.front() << " ";
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