#include<iostream>
#include<vector>


int main() {
    const int N(200000);
    int t(0);

    std::cin >> t;
    for (int tc = 0; tc < t; ++tc) {
        std::string s;
        long long pos;
        std::cin >> s >> pos;
        --pos;

        int curLen = s.size();
        std::vector<char>st;
        bool ok = pos < curLen;
        s += '$';

        for (auto c : s) {
            while (!ok && st.size() > 0 && st.back() > c) {
                pos -= curLen;
                --curLen;
                st.pop_back();

                if (pos < curLen)
                    ok = true;
            }
            st.push_back(c);
        }

        std::cout << st[pos];
    }
    return 0;
}