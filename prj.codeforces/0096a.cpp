#include <iostream>
int main(){
    std::string s;
    std::cin >> s;
    int pos = s.find("1111111");
    int pos1 = s.find("0000000");
    if (pos + 1 || pos1 + 1)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}