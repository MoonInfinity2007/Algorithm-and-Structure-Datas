#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

std::string add(std::string a, std::string b) {
    std::string result;
    int i = a.size() - 1;
    int j = b.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }
        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }
        result.push_back(char('0' + sum % 10));
        carry = sum / 10;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::string removeLeadingZeros(std::string s) {
    int i = 0;
    while (i + 1 < (int)s.size() && s[i] == '0') i++;
    return s.substr(i);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::string> numbers(n);
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
        numbers[i] = removeLeadingZeros(numbers[i]);
        maxLength = std::max(maxLength, (int)numbers[i].size());
    }
    std::unordered_set<std::string> fibonacci;
    std::string a = "1", b = "1";
    fibonacci.insert(a);
    while ((int)b.size() <= maxLength) {
        fibonacci.insert(b);
        std::string c = add(a, b);
        a = b;
        b = c;
    }
    for (int i = 0; i < n; i++) {
        if (fibonacci.count(numbers[i])) std::cout << "Yes\n";
        else std::cout << "No\n";
    }
    return 0;
}