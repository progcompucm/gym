#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define F first
#define S second
#define pb push_back
#define pll pair<ll, ll>
#define vll vector<ll>
#define mpll map<pll, ll> 
#define mll map<ll, ll>
#define vpp vector<pll, pll>
#define sz(x) ((ll)) x.size()
#define all(x) x.begin(), x.end()
#define endl "\n"

template <typename T, typename... V>
void p(T&& t, V&&... v){
    cout << t;
    initializer_list<int>{ (cout << ' ' << v, 0)... };
    cout << endl;
}

ll lee(vector<vll>& grid, pll start, pll end){
    ll n = grid.size();
    ll m = grid[0].size();
    
    vector<vll> dist(n, vll(m, -1));
    queue<pll> q;
    q.push(start);
    dist[start.F][start.S] = 0;

    ll dx [] = {-1, 1, 0, 0};
    ll dy[] = {0, 0, -1, 1};
    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop();

        for(ll d = 0; d < 4; d++){
            ll nx = x + dx[d];
            ll ny = y + dy[d];
            
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if(grid[nx][ny] == 1) continue;
            if(dist[nx][ny] != -1) continue;

            dist[nx][ny] = dist[x][y] + 1,
            q.push({ nx, ny });
        }
    }

    return dist[end.F][end.S];
}

void solve(){
    ll n = 5, m = 6;

    /**
        S . . # . .
        . # . # . .
        . # . . . .
        . # # # # .
        . . . . . E

        0 = camino
        1 = obstáculo
        S = (0,0)
        E = (4,5)

        Camino minimo: S → ↓ → ↓ → → → ↓ → → → E
     */
    vector<vll> grid = {
        {0, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0}
    };

    pll start = {0, 0};
    pll end = {4, 5};

    p(lee(grid, start, end));
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    ll t;
    // cin >> t;
    while(t--) solve();

    return 0;
}