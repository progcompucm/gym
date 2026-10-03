#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll count_palindromic_substrings(string s){
    ll n = s.size();
    ll ans = 0;

    auto expand = [&](ll l, ll r){
        while(l >= 0 && r < n && s[l] == s[r]){
            ans++;
            l--;
            r++;
        }
    };

    for(ll i = 0; i < n; i++){
        expand(i, i);
        expand(i, i + 1);
    }

    return ans;
}

int main(){
    return 0;
}