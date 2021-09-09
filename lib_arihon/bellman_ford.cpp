#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct edge {
    int from;
    int to;
    ll cost;
};

// TODO: 動作未検証
// O(VE)
// 重みが負の edge があってもよい
// 終点は全て同時に計算できる
class BellmanFord {
    int V;  // 頂点の個数
    int E;  // 辺の個数
    vector<edge> edges;
    vector<ll> dist;  // dist[v]: v までの最短距離
    vector<bool>
        negative;  // negative[v]: 始点からvまでの経路中に負の閉路がある
    const ll INF = numeric_limits<ll>::max();

   public:
    BellmanFord(int v, int e) : V(v), E(e), dist(v), negative(v) {}

    void add_edge(int from, int to, ll cost) {
        edges.push_back({from, to, cost});
    }

    // 始点から到達可能な負の閉路が存在するか
    bool exec(int start_node) {
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
            negative[i] = false;
        }
        dist[start_node] = 0;
        for (int i = 0; i < V; ++i) {
            bool updated = false;
            for (int j = 0; j < E; ++j) {
                edge edge = edges[j];
                if (dist[edge.from] != INF &&
                    dist[edge.to] > dist[edge.from] + edge.cost) {
                    dist[edge.to] = dist[edge.from] + edge.cost;
                    updated = true;
                }
            }
            if (!updated) {
                return false;
            }
        }
        // 始点から到達可能な負の閉路があるなら
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < E; ++j) {
                edge edge = edges[j];
                if (dist[edge.from] != INF &&
                    dist[edge.to] > dist[edge.from] + edge.cost) {
                    negative[edge.to] = true;
                }
                if (negative[edge.from]) {
                    negative[edge.to] = true;
                }
            }
        }
        return true;
    }

    // 頂点 v までの最小コスト
    ll cost(int v) { return dist[v]; }

    // 負の閉路が存在するか(始点から到達不可能も含む)
    bool have_negative_loop() {
        vector<ll> _dist(V, 0);
        for (int i = 0; i < V; ++i) {
            bool updated = false;
            for (int j = 0; j < E; ++j) {
                edge edge = edges[j];
                if (_dist[edge.to] > _dist[edge.from] + edge.cost) {
                    _dist[edge.to] = _dist[edge.from] + edge.cost;
                    updated = true;
                }
            }
            if (!updated) {
                return false;
            }
        }
        return true;
    }
};

int main() {}