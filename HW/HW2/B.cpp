#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
#include <string>

int main() {
    std::string A, B;
    std::cin >> A >> B;
    std::multiset<char, std::greater<char>> msa, msb, ms;
    for (int i = 0; i < A.size(); ++i) msa.insert(A[i]);
    for (int i = 0; i < B.size(); ++i) msb.insert(B[i]);
    std::set_intersection(msa.begin(), msa.end(), msb.begin(), msb.end(), std::inserter(ms, ms.begin()), std::greater<char>());
    if (ms.empty()) {
        std::cout << -1;
        return 0;
    }
    if (*ms.begin() == '0') {
        std::cout << 0;
        return 0;
    }
    for (auto elem : ms) std::cout << elem;
    return 0;
}