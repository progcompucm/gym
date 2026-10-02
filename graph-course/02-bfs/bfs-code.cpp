#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<ll>
#define pb push_back

void bfs(vector<vll>& adj, ll root_node){
    vector<bool> vis(adj.size(), false);
    queue<ll> q;
    q.push(root_node);
    vis[root_node] = true;
    while(!q.empty()){
        // here we can do some stuff for every node
        ll u = q.front();
        cout << u << "\n";
        q.pop();
        // push the nbrs of curr node inside q if they arent visited
        for(ll v : adj[u]){
            if(vis[v]) continue;
            vis[v] = true;
            q.push(v);
        }
    }
}

int main(){
    vector<vll> adj(7);
    adj[0].pb(1);
    adj[1].pb(0);

    adj[1].pb(2);
    adj[2].pb(1);

    adj[3].pb(5);
    adj[5].pb(3);

    adj[5].pb(6);
    adj[6].pb(5);

    adj[4].pb(5);
    adj[5].pb(4);

    adj[0].pb(4);
    adj[4].pb(0);

    adj[3].pb(4);
    adj[4].pb(3);

    bfs(adj, 1);
    return 0;
}