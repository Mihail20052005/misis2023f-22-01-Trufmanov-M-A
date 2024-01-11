#include <iostream>
std::string result;
int n, k, i, b[30], s = 1e8;
int main() {
    std::cin >> n >> k >> result;
    for (i = 0; i < n; i++)
        b[result[i] - 'A']++;
    for (i = 0; i < k; i++)
        s = std::min(s, b[i]);
    std::cout << s * k;
    return 0;
}