#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// O(V^3)
// edge の重みは負でもよい
// 全点対の最短距離がわかる
// 動作確認: https://atcoder.jp/contests/typical90/tasks/typical90_ci
class WarshallFloyd {
    int V;                    // 頂点の個数
    vector<vector<ll>> dist;  // コスト
    const ll INF = numeric_limits<ll>::max();

   public:
    WarshallFloyd(int v) : V(v), dist(v, vector<ll>(v, INF)) {
        for (int i = 0; i < V; ++i) {
            dist[i][i] = 0;
        }
    }

    void add_edge(int from, int to, ll edge_cost) {
        dist[from][to] = edge_cost;
    }

    void exec() {
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // from から to の最小コスト
    ll cost(int from, int to) { return dist[from][to]; }
};

int main() {}