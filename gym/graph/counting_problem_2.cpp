#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main(){
    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> adj(n * m);

    vector<string> mp(n);
    for(auto &x : mp) cin >> x;

    ll dr[4] = {-1, 1, 0,  0}, dc[4] = {0, 0, -1, 1};

    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            if(mp[i][j] == '#') continue;
            ll u = i * m + j;

            for(int k = 0; k < 4; k++){
                ll ni = i + dr[k], nj = j + dc[k];
                if(ni >= 0 && ni < n && nj >= 0 && nj < m && mp[ni][nj] == '.'){
                    int v = ni * m + nj;
                    adj[u].push_back(v);
                }
            }
        }
    }

    vector<char> seen(n * m, 0);
    ll rooms = 0;
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            ll u = i * m + j;
            if(mp[i][j] == '.' && !seen[u]){
                rooms++;
                queue<int> q;
                q.push(u);
                seen[u] = 1;
                
                while(!q.empty()){
                    int x = q.front();
                    q.pop();
                    for(ll v : adj[x]){
                        if(!seen[v]){
                            seen[v] = 1;
                            q.push(v);
                        }
                    }
                }
            }
        }
    }

    cout << rooms << "\n";

    // g.print_graph();

    return 0;
}