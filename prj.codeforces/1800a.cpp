#include <iostream>
#include <algorithm>
#include <vector>
std::string solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    transform(s.begin(), s.end(), s.begin(), [](char c) {
        return tolower(c);
        });
    s.erase(unique(s.begin(), s.end()), s.end());
    return s == "meow" ? "YES" : "NO";
}

int main() {
    std::vector<std::string> answers;
    int t;
    std::cin >> t;
    while (t--) {
        answers.push_back(solve());
    }

    for (std::string a : answers) {
        std::cout << a << std::endl;
    }
}