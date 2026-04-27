#include <iostream>
#include <stack>

#define LL long long

int main() {
    LL N;
    std::cin >> N;
    LL a[N];
    for (LL i = 0; i < N; ++i) std::cin >> a[i];
    LL c[N], bl[N], br[N];
    std::stack<LL> st;
    LL cur;
    for (LL i = 0; i < N; ++i) {
        while (!st.empty() && a[st.top()] > a[i]) st.pop();
        if (st.empty()) bl[i] = (i + 1) * a[i];
        else {
            LL j = st.top();
            bl[i] = bl[j] + (i - j) * a[i];
        }
        st.push(i);
    }
    while (!st.empty()) st.pop();
    for (LL i = N - 1; i >= 0; --i) {
        while (!st.empty() && a[st.top()] > a[i]) st.pop();
        if (st.empty()) br[i] = (N - i) * a[i];
        else {
            LL j = st.top();
            br[i] = br[j] + (j - i) * a[i];
        }
        st.push(i);
    }
    LL pos = 0, ma = 0;
    for (LL i = 0; i < N; ++i) {
        if (bl[i] + br[i] - a[i] >= ma) {
            ma = bl[i] + br[i] - a[i];
            pos = i;
        }
    }
    c[pos] = a[pos];
    cur = a[pos];
    for (LL i = pos + 1; i < N; ++i) {
        cur = std::min(cur, a[i]);
        c[i] = cur;
    }
    cur = a[pos];
    for (LL i = pos - 1; i >= 0; --i) {
        cur = std::min(cur, a[i]);
        c[i] = cur;
    }
    for (LL i = 0; i < N; ++i) std::cout << c[i] << " ";
}