#include <iostream>
#include <queue>

int main() {
    int n, k;
    std::cin >> n >> k;
    int a[n];
    std::queue<int> q;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < k - 1; ++i) {
        if (q.empty()) q.push(a[i]);
        else if (q.front() >= a[i]) {
            while (!q.empty()) q.pop();
            q.push(a[i]);
        } else q.push(a[i]);
    }
    for (int i = k - 1; i < n; ++i) {
        if (q.size() == k) {
            q.pop();
            int mi = 1e9;
            std::queue<int> dq(q);
            while (!dq.empty()) {
                mi = std::min(mi, dq.front());
                dq.pop();
            }
            while (!q.empty() && q.front() != mi) q.pop();
        }
        if (q.empty()) q.push(a[i]);
        else if (q.front() >= a[i]) {
            while (!q.empty()) q.pop();
            q.push(a[i]);
        } else q.push(a[i]);
        std::cout << q.front() << " ";
    }
}