#include <iostream>
#include <string>

int main() {
    int n(0), num_del(0);
    std::string stones;
    std::cin >> n >> stones;
    for (int i(0); i < n; i++) {
        if (stones[i] == stones[i + 1]) {
            num_del++;
        }
    }
    std::cout << num_del;
}