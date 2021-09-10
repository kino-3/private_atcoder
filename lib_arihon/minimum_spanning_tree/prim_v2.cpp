#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// TODO: 動作未検証
// O(V^2)
class Prim {
    int V;                    // 頂点の個数
    vector<vector<ll>> cost;  // コスト
    vector<pair<int, int>> links;
    const ll INF = numeric_limits<ll>::max();

   public:
    Prim(int v) : V(v), cost(v, vector<ll>(v, INF)) {}

    void add_edge(int from, int to, ll edge_cost) {
        cost[from][to] = edge_cost;
    }

    // 最小全域木のコストの総和
    int exec(int start_node = 0) {  // 最初の最小全域木は start_node のみ含む
        // 構築済みの部分木と v の間の辺の最小コスト
        vector<ll> mincost(V, INF);
        vector<bool> used(V, false);  // 構築済みの部分木に v が含まれるか
        vector<int> parent(V, -1);
        ll total_cost = 0;
        mincost[start_node] = 0;
        while (true) {
            int next_node = -1;
            for (int u = 0; u < V; u++) {
                if (!used[u] &&
                    (next_node == -1 || mincost[u] < mincost[next_node])) {
                    next_node = u;
                }
            }
            if (next_node == -1) {
                break;
            }
            used[next_node] = true;
            total_cost += mincost[next_node];
            for (int u = 0; u < V; u++) {
                if (mincost[u] > cost[next_node][u]) {
                    mincost[u] = cost[next_node][u];
                    if (!used[u]) {
                        parent[u] = next_node;
                    }
                }
            }
        }
        for (int u = 0; u < V; u++) {
            if (u == start_node) {
                continue;
            }
            links.push_back({u, parent[u]});
        }
    }
};

int main() {}