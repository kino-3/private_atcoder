#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
#define ALL(c) std::begin(c), std::end(c)

using namespace std;
using ll = long long;

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));

struct edge {
    int to;
    ll cost;
};

// TODO: 動作未検証
// O(E logV)
// 条件: edge の重みは非負
class Dijkstra {
    int V;                       // 頂点の個数
    vector<vector<edge>> edges;  // edges[v] の要素は, v から 要素.to への edge
    vector<ll> dist;             // dist[v]: v までの最短距離
    vector<int> prev;            // 最短経路における直前の node
    const ll INF = numeric_limits<ll>::max();

   public:
    Dijkstra(int v) : V(v), edges(v, vector<edge>(0)), dist(v), prev(v) {}

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

ll N, M, i, a, b, c;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;

    Dijkstra graph = Dijkstra(N);
    Dijkstra graph2 = Dijkstra(N);
    REP(i, M) {
        cin >> a >> b >> c;
        graph.add_edge(a - 1, b - 1, c);
        graph.add_edge(b - 1, a - 1, c);
        graph2.add_edge(a - 1, b - 1, c);
        graph2.add_edge(b - 1, a - 1, c);
    }
    graph.exec(0);
    graph2.exec(N - 1);
    REP(i, N) { cout << graph.cost(i) + graph2.cost(i) << endl; }
}