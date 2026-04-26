#include <iostream>
#include <map>
#include <utility>

std::map<std::pair<int, int>, int> mp;

int solve(int p, int su) {
    if (su == 0) {
        if (mp.count({p, su}) < 1) mp[{p, su}] = 1;
        return 1;
    }
    if (su < 0) {
        if (mp.count({p, su}) < 1) mp[{p, su}] = 0;
        return 0;
    }
    int ans = 0;
    for (int i = 1; i < p; ++i) {
        if (su - i >= 0) {
            if (mp.count({i, su - i}) < 1) ans += solve(i, su - i);
            else ans += mp[{i, su - i}];
        }
    }
    if (mp.count({p, su}) < 1) mp[{p, su}] = 0;
    mp[{p, su}] = ans;
    return ans;
}

int main() {
    int N;
    std::cin >> N;
    std::cout << solve(N + 1, N);
}