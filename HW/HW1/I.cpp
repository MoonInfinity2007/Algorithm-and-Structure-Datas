#include <iostream>
#include <stack>
#include <vector>

int main() {
    int N;
    std::cin >> N;
    std::vector<long long> a(N), ans(N);
    for (int i = 0; i < N; ++i) std::cin >> a[i];
    std::stack<int> st;
    for (int i = N - 1; i >= 0; --i) {
        ans[i] = -1;
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        if (!st.empty()) ans[i] = st.top();
        st.push(i);
    }
    // for (int i = 0; i < N; ++i) {
    //     if (i > 0) std::cout << ' ';
    //     std::cout << ans[i];
    // }
    // std::cout << '\n';
}
