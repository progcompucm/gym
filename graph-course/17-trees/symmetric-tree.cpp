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

struct Node{
    ll val;
    Node* left;
    Node* right;

    Node(ll v): val(v), left(nullptr), right(nullptr){}
};

bool is_mirror(Node* a, Node *b){
    if(a == nullptr && b == nullptr) return true;
    if(a == nullptr || b == nullptr) return false;
    if(a->val != b->val) return false;
    return is_mirror(a->left, b->right) && is_mirror(a->right, b->left);
}

bool is_symmetric(Node* root){
    if(root == nullptr) return true;
    return is_mirror(root->left, root->right);
}

void solve(){
        Node* root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(2);

    root->left->left = new Node(3);
    root->left->right = new Node(4);

    root->right->left = new Node(4);
    root->right->right = new Node(3);

    cout << is_symmetric(root) << endl;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    
    ll t;
    cin >> t;
    while(t--) solve();

    return 0;
}