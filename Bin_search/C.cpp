#include<iostream>

int main() {
    int N, K;
    std::cin >> N >> K;
    int a[N];
    for (int i = 0; i < N; ++i) std::cin >> a[i];
    for (int i = 0; i < K; ++i) {
        int key;
        std::cin >> key;
        int left = -1, right = N;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            if (a[mid] < key) left = mid;
            else right = mid;
        }
        std::cout << ((key == a[right]) ? "YES\n" : "NO\n");
    }
}