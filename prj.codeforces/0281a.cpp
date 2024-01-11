#include <iostream>
#include <string>

int main() {
    std::string str;
    int len = str.length();
    std::cin >> str;
    char word = str[0];
    if ('a' <= word && word <= 'z') {
        word = word - 32;
    }
    str = str.erase(0, 1);
    std::cout << word << str;
}