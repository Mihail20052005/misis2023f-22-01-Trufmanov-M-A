#include <iostream>
#include <algorithm>
using namespace std;
 
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    int n,k,l,c,d,p,nl,np;
    cin>>n>>k>>l>>c>>d>>p>>nl>>np;
 
    int total_drinks = k * l;
    total_drinks = total_drinks/nl;
 
    int total_slices = c*d;
 
    int total_salt = p/np;
 
    int ans = min(min(total_drinks,total_slices),total_salt)/n;//50 /4 =12
    cout<<ans<<"\n";
    return 0;
}