#include <iostream>
#include<vector>

void solve() {
    int n(0);
    std::cin >> n;

    std::vector<int> numbers = {};
    for (int i = 0; i < n; i += 1) {
        int tmp = 0;
        std::cin >> tmp;
        numbers.push_back(tmp);
    }
    int cnt_0(0), cnt_1(0);
    for (int i = 0; i < n; i += 1) {
        if (numbers[i] == 0) cnt_0 += 1;
        else cnt_1 += 1;
    }
    if (cnt_1 <= n / 2) {
        for (int i = 0; i < n; i += 1) {
            if (numbers[i] == 1) numbers[i] = -1;
        }
        std::cout << n - cnt_1 << std::endl;
        for (auto c : numbers) {
            if (c != -1) std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    else {
        for (int i = 0; i < numbers.size(); i += 1) {
            if (numbers[i] == 0) numbers[i] = -1;
        }
        if (cnt_1 % 2 == 1) {
            bool flag = true;
            for (int i = 0; i < n; i += 1) {
                if (flag && numbers[i] == 1) {
                    numbers[i] = -1;
                    flag = false;
                    break;
                }
            }
            std::cout <<  n - (cnt_0 + 1) << std::endl;
            for (auto c : numbers) {
                if (c != -1) std::cout << c << ' ';
            }
            std::cout << std::endl;
        }
        else {
            std::cout << n - cnt_0 << std::endl;
            for (auto c : numbers) {
                if (c != -1) std::cout << c << ' ';
            }
            std::cout << std::endl;
        }
    }
}

int main(){
    int t(0);
    std::cin >> t;
    while (t--) solve();

}