#include <iostream>
#include <array>

//89172371807
void solve(){  
    int count_zero(0), count_one(0);
    std::array<std::array<int, 2>, 2> a;
    for(int j = 0; j < 2; j++ ){
        std::cin >> a[0][j];
        a[0][j] == 0 ? count_zero += 1 : count_one += 1;
    }

    for (int j = 0; j < 2; j += 1) {
        std::cin >> a[1][j];
        a[1][j] == 0 ? count_zero += 1 : count_one += 1;
    }

    if (count_one == 0) {
        std::cout << 0 << std::endl;
    }

    else if (count_one == 4) {
        std::cout << 2 << std::endl;
    }

    else std::cout << 1 << std::endl;
}

int main(){
    int n(0);
    std::cin >> n;

    while(n--){
        solve();
    }
}