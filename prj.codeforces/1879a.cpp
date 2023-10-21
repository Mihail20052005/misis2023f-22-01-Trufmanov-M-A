#include <iostream>
const int N = 109;

int t;
int n;
int s[N], e[N];

int main() {
    std::cin >> t;
    for (int tc = 0; tc < t; ++tc) {
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> s[i] >> e[i];
        }

        bool ok = true;
        for (int i = 1; i < n; ++i)
            if (s[i] >= s[0] && e[i] >= e[0])
                ok = false;

        if (!ok) {
            puts("-1");
            continue;
        }

        std::cout << s[0] << std::endl;
    }
    return 0;
}