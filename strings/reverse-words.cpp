#include <bits/stdc++.h>
using namespace std;

#define ll long long

string rev_words(string s){
    reverse(s.begin(), s.end());
    ll l = 0;
    for(ll r = 0; r <= s.size(); r++){
        if(r == s.size() || s[r] == ' '){
            reverse(s.begin() + l, s.begin() + r);
            l = r + 1;
        }
    }
    return s;
}

int main(){
    string s = "hello world";
    cout << rev_words(s) << "\n";
    
    return 0;
}