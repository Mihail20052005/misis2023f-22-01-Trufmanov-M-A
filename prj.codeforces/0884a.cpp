#include <iostream>

int main(){
	int n(0), t(0), time_read(0);
	std::cin >> n >> t;
	for(int i = 0; i < n; i++){
		int days(0);
		std::cin >> days;
		time_read += 86400 - days;
		if((t - time_read) <= 0){
			std::cout << i + 1;
			break;
		}
	}
}