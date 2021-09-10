#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct edge {
    int to;
    ll cost;
};

// dijkstra.cpp を改造
class Dijkstra2 {
    int V;                       // 頂点の個数
    vector<vector<edge>> edges;  // edges[v] の要素は, v から 要素.to への edge
    vector<ll> dist;             // dist[v]: v までの最短距離
    vector<int> prev;            // 最短経路における直前の node
    const ll INF = numeric_limits<ll>::max();

   public:
    Dijkstra2(int v) : V(v), edges(v, vector<edge>(0)), dist(v), prev(v) {}

    void add_edge(int from, int to, ll edge_cost) {
        edges[from].push_back({to, edge_cost});
    }

    void exec(int start_node) {
        typedef pair<ll, int> P;  // first は最短距離, second は node
        priority_queue<P, vector<P>, greater<P>> que;
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
            prev[i] = -1;
        }
        dist[start_node] = 0;
        que.push({0, start_node});
        while (!que.empty()) {
            P p = que.top();  // ノード p.second には距離 p.first で到達可能
            que.pop();
            int node = p.second;
            if (dist[node] < p.first) {
                continue;
            }
            for (auto&& edge : edges[node]) {
                if (dist[edge.to] > dist[node] + edge.cost) {
                    dist[edge.to] = dist[node] + edge.cost;
                    que.push({dist[edge.to], edge.to});
                    prev[edge.to] = node;
                }
            }
        }
    }

    // 頂点 v までの最小コスト
    ll cost(int v) { return dist[v]; }

    int get_prev(int v) { return prev[v]; }
};

int main() {}