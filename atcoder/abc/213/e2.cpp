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

// 単始点全終点最短距離
// O(E logV)
// 条件: edge の重みは非負
// 動作確認
// - https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6080524#1
// - https://atcoder.jp/contests/abc218/tasks/abc218_f
class Dijkstra {
    ll V;                                // 頂点の個数
    vector<vector<pair<ll, ll>>> edges;  // {to, cost}
    const ll INF = numeric_limits<ll>::max();

   public:
    vector<ll> dist;         // dist[v]: v までの最短距離
    vector<bool> reachable;  // 到達可能か
    vector<ll> prev;  // prev[v]: v までの最短経路における直前の node

    Dijkstra(ll v) : V(v), edges(v) {}

    void add_edge(ll from, ll to, ll edge_cost) {
        edges[from].push_back({to, edge_cost});
    }

    void exec(ll start_node) {
        typedef pair<ll, ll> P;  // first は最短距離, second は node
        priority_queue<P, vector<P>, greater<P>> que;
        dist.resize(V, INF);
        prev.resize(V, -1);
        dist[start_node] = 0;
        que.push({0, start_node});
        while (!que.empty()) {
            P p = que.top();  // ノード p.second には距離 p.first で到達可能
            que.pop();
            ll node = p.second;
            if (dist[node] < p.first) {
                continue;
            }
            for (auto &&edge : edges[node]) {
                if (dist[edge.first] > dist[node] + edge.second) {
                    dist[edge.first] = dist[node] + edge.second;
                    que.push({dist[edge.first], edge.first});
                    prev[edge.first] = node;
                }
            }
        }
        reachable.resize(V);
        for (ll v = 0; v < V; v++) {
            reachable[v] = (dist[v] != INF);
        }
    }

    // 経路復元(最短経路の1つ)
    vector<ll> path(ll v) {
        vector<ll> res;
        while (v > -1) {
            res.push_back(v);
            v = prev[v];
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

class Dijkstra2D {
   public:
    ll R;
    ll C;
    Dijkstra dijkstra;

    Dijkstra2D(ll row, ll col) : R(row), C(col), dijkstra(row * col) {}

    ll convert_2d_to_1d(pair<ll, ll> x) { return x.first * C + x.second; }

    pair<ll, ll> convert_1d_to_2d(ll x) { return {x / C, x % C}; }

    // フィールド内か
    bool is_field(pair<ll, ll> pos) {
        if (pos.first < 0) return false;
        if (pos.first >= R) return false;
        if (pos.second < 0) return false;
        if (pos.second >= C) return false;
        return true;
    }

    // 有向辺の追加(領域外なら無視する)
    // 辺を追加出来たかを返す
    bool add_edge(pair<ll, ll> from, pair<ll, ll> to, ll edge_cost) {
        if (!is_field(from)) return false;
        if (!is_field(to)) return false;
        ll from1d = convert_2d_to_1d(from);
        ll to1d = convert_2d_to_1d(to);
        dijkstra.add_edge(from1d, to1d, edge_cost);
        return true;
    }

    // 無向辺の追加(領域外なら無視する)
    // 辺を追加出来たか
    bool add_edge_undirected(pair<ll, ll> pos1, pair<ll, ll> pos2,
                             ll edge_cost) {
        add_edge(pos1, pos2, edge_cost);
        return add_edge(pos2, pos1, edge_cost);
    }

    void exec(pair<ll, ll> start_node) {
        dijkstra.exec(convert_2d_to_1d(start_node));
    }

    ll dist(pair<ll, ll> end_node) {
        return dijkstra.dist[convert_2d_to_1d(end_node)];
    }

    // 経路復元(最短経路の1つ)
    vector<pair<ll, ll>> path(pair<ll, ll> end_node) {
        vector<ll> res1d = dijkstra.path(convert_2d_to_1d(end_node));
        vector<pair<ll, ll>> res;
        for (auto v : res1d) {
            res.push_back(convert_1d_to_2d(v));
        }
        return res;
    }
};

const ll mod = 998244353;
ll H, W, i, j, k, l;
string S;
vector<vector<bool>> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W;

    A.resize(H);
    REP(i, H) {
        cin >> S;
        REP(j, W) {
            // . が移動可能とする
            A[i].push_back(S[j] == '.');
        }
    }

    Dijkstra2D dijkstra2d = Dijkstra2D(H, W);

    REP(i, H) {
        REP(j, W) {
            if (!A[i][j]) continue;
            vector<pair<ll, ll>> direction = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
            for (auto d : direction) {
                ll row = i + d.first;
                ll col = j + d.second;
                if (dijkstra2d.is_field({row, col})) {
                    if (A[row][col]) {
                        dijkstra2d.add_edge({i, j}, {row, col}, 1);
                    }
                }
            }
        }
    }

    dijkstra2d.exec({0, 0});
    REP(i, H) {
        REP(j, W) { cout << dijkstra2d.dist({i, j}); }
        cout << endl;
    }
    cout << dijkstra2d.dist({H - 1, W - 1}) << endl;
}