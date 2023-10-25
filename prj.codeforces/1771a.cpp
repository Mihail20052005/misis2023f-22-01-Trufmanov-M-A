#include <iostream>
#include <array>
#include <algorithm>


void solve(){
	long long int t;
	std::cin >> t;
	std::array<int, 100001> a;
	long long int max = -1000000;
	long long int min = 10000000;
	long long int min_count(0), max_count(0);
	for(int i = 0; i < t; i++){
		std::cin >> a[i];
	}

	for(int i = 0; i < t; i++){
		if(a[i] < min){
			min = a[i];
			min_count = 1;
		}
		else if(a[i] == min ){
			min_count += 1;
		}

		if (a[i] > max) {
			max = a[i];
			max_count = 1;
		}
		else if (a[i] == max) {
			max_count += 1;
		}
	
	}
	if((max - min) == 0){
		long long int a = t * (t - 1);
		std::cout << a << std::endl;
	}
	else {
		//std::cout << max_count << min_count << max << min;
		long long ans = min_count * max_count * 2;
		std::cout << ans << std::endl;
	}

}
int main(){
	int n(0);
	std::cin >> n;
	while (n--) solve();
}