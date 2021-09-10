#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// TODO: 動作未検証
// O(V^2)
// 条件: edge の重みは非負
class Dijkstra {
    int V;                    // 頂点の個数
    vector<vector<ll>> cost;  // コスト
    vector<ll> dist;          // dist[v]: v までの最短距離
    vector<int> prev;         // 最短経路における直前の node
    const ll INF = numeric_limits<ll>::max();

   public:
    Dijkstra(int v) : V(v), cost(v, vector<ll>(v, INF)), dist(v), prev(v) {}

    void add_edge(int from, int to, ll edge_cost) {
        cost[from][to] = edge_cost;
    }

    void exec(int start_node) {
        vector<bool> used(V);  // フラグ
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
            used[i] = false;
            prev[i] = -1;
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
                if (dist[u] > dist[v] + cost[v][u]) {
                    dist[u] = dist[v] + cost[v][u];
                    prev[u] = v;
                }
            }
        }
    }

    // 頂点 v までの最小コスト
    ll cost(int v) { return dist[v]; }

    int get_prev(int v) { return prev[v]; }
};

int main() {}