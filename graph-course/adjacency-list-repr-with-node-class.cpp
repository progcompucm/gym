// i think that this is not for competivie programming but can be helpful...

#include <bits/stdc++.h>
using namespace std;

#define ll long long

class Node{
public:
    string name;
    list<string> nbrs;

    Node(string name){
        this->name = name;
    }
};

class Graph{
    unordered_map<string, Node*> m;

public:
    Graph(vector<string> n){
        for(string v : n){
            m[v] = new Node(v);
        }
    }

    void add_edge(string u, string v, bool undir = false){
        m[u]->nbrs.push_back(v);
        if(undir) m[v]->nbrs.push_back(u);
    }

    void print(){
        for(auto x : m){
            cout << x.first << " -> ";
            for(auto v : x.second->nbrs){
                cout << v << " ";
            }
            cout << endl;
        }
    }
};

int main(){
    vector<string> cities = {"Delhi", "London", "Paris", "New York"};
    Graph g(cities);

    g.add_edge("Delhi", "London");
    g.add_edge("New York", "London");
    g.add_edge("Delhi", "Paris");
    g.add_edge("Paris", "New York");
    
    g.print();
    
    return 0;
}