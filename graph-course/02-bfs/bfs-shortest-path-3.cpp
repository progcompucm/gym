#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<ll>
#define pb push_back

vll bfs(vector<vll>& adj, ll N, ll root_node, ll dest = -1){
    vll dist(N, -1);
    vll parent(N, -1);
    queue<ll> q;
    q.push(root_node);
    parent[root_node] = root_node;
    dist[root_node] = 0;
    while(!q.empty()){
        ll u = q.front();
        q.pop();
        for(ll v : adj[u]){
            if(dist[v] != -1) continue;
            q.push(v);
            parent[v] = u;
            dist[v] = dist[u] + 1;
        }
    }

    if(dest != -1){
        ll temp = dest;
        while(temp != root_node){
            cout << temp << " -- ";
            temp = parent[temp];
        }
        cout << root_node << "\n";
    }

    return dist;
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

    vll dists = bfs(adj, 7, 1, 6);

    return 0;
}