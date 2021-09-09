#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// TODO: 動作未検証
// O(V^2)
// 条件: edge の重みは非負
class Dijkstra2 {
    int V;                    // 頂点の個数
    vector<vector<ll>> cost;  // コスト
    vector<ll> dist;          // dist[v]: v までの最短距離
    const ll INF = numeric_limits<ll>::max();

   public:
    Dijkstra2(int v) : V(v), cost(v, vector<ll>(v, INF)), dist(v) {}

    void add_edge(int from, int to, ll edge_cost) {
        cost[from][to] = edge_cost;
    }

    void exec(int start_node) {
        vector<bool> used(V);  // フラグ
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
            used[i] = false;
        }
        dist[start_node] = 0;
        while (true) {
            int v = -1;
            for (int u = 0; u < V; u++) {
                if (!used[u] && (v == -1 || dist[u] < dist[v])) {
                    v = u;
                }
            }
            if (v == -1) {
                break;
            }
            used[v] = true;
            for (int u = 0; u < V; u++) {
                dist[u] = std::min(dist[u], dist[v] + cost[v][u]);
            }
        }
    }

    // 頂点 v までの最小コスト
    ll cost(int v) { return dist[v]; }
};

int main() {}