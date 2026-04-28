#include <iostream>
#include <stack>

#define LL long long

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    LL N;
    std::cin >> N;
    LL a[N];
    std::stack<std::pair<LL, LL>> st;
    for (LL i = 0; i < N; ++i) std::cin >> a[i];
    LL ans = 0;
    for (LL i = 0; i < N; ++i) {
        LL start = i;
        while (!st.empty() && st.top().first > a[i]) {
            ans = std::max(st.top().first * (i - st.top().second), ans);
            start = st.top().second;
            st.pop();
        }
        st.push({a[i], start});
    }
    while (!st.empty()) {
        ans = std::max(st.top().first * (N - st.top().second), ans);
        st.pop();
    }
    std::cout << ans;
}