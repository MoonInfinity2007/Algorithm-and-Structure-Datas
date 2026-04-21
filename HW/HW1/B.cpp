#include <iostream>
#include <vector>

bool check(const std::vector<int>& a) {
    if(a.size() == 1 && a[0] == 24) return true;
    else if (a.size() == 1 && a[0] != 24) return false;
    for (int i = 0; i < a.size(); ++i) {
        for (int j = i + 1; j < a.size(); ++j) {
            std::vector<int> b = {};
            for (int k = 0; k < a.size(); ++k) {
                if (k != i && k != j) b.push_back(a[k]);
            }
            b.push_back(a[i] + a[j]);
            if (check(b)) return true;
            b.pop_back();
            b.push_back(a[i] * a[j]);
            if (check(b)) return true;
            b.pop_back();
            b.push_back(a[i] - a[j]);
            if (check(b)) return true;
            b.pop_back();
            b.push_back(a[j] - a[i]);
            if (check(b)) return true;
            b.pop_back();
        }
    }
    return false;
}


int main() {
    std::vector<int> a(4);
    for (int i = 0; i < 4; ++i) std::cin >> a[i];
    if (check(a)) std::cout << "YES";
    else std::cout << "NO";
}

// bool solve(const std::vector<int>& a) {
//     std::vector<int> b = a;
//     for (int it1 = 0; it1 < 4; ++it1) {
//         for (int it2 = 0; it2 < 4; ++it2) {
//             if (it1 == it2) continue;
//             for (int it3 = 0; it3 < 4; ++it3) {
//                 if (it1 == it2 || it1 == it3) continue;
//                 for (int it4 = 0; it4 < 4; ++it4) {
//                     if (it1 == it4 || it2 == it4 || it3 == it4)
//                     b = {a[it1], a[it2], a[it3], a[it4]};
//                     if (check(b)) return true;
//                 }
//             }
//         }
//     }
//     return false;
// }
