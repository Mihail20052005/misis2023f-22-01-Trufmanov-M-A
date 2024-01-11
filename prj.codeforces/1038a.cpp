#include <iostream>
using namespace std;
string a;
int n, k, i, b[30], s = 1e8;
int main() {
    cin >> n >> k >> a;
    for (i = 0; i < n; i++)
        b[a[i] - 'A']++;
    for (i = 0; i < k; i++)
        s = min(s, b[i]);
    cout << s * k;
    return 0;
}