#include <iostream>
#include <vector>

void solve(){
    int t(0);
    std::cin >> t;
    std::vector<int>a(t);
    for (auto& i : a) {
        std::cin >> i;
    }
    int ans = 0;
    for (int i = t - 2; i >= 0; i--) {
        while (a[i] >= a[i + 1] && a[i] > 0) {
            a[i] /= 2;
            ans++;
        }
        if (a[i] == a[i + 1]) {
            std::cout << -1 << '\n';
            return;
        }
    }
    std::cout << ans << '\n';
}

int main(){
    int n(0);
    std::cin >> n;

    while (n--) solve();

}