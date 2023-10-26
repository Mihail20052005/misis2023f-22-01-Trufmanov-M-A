#include <iostream>

int main()
{
    long long n, m, pos(1), res(0), temp;
    std::cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        std::cin >> temp;
        if (temp < pos)
            res += n - pos + temp;
        else
            res += temp - pos;
        pos = temp;
    }
    std::cout << res << std::endl;
    return 0;
}