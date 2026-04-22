#include <iostream>

int main() {
    int N;
    std::cin >> N;
    int a[N];
    for (int i = 0; i < N; ++i) std::cin >> a[i];
    for (int i = N - 1; i >= 0; --i) std::cout << a[i] << " ";
}