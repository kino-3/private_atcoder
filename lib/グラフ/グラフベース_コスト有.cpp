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


// コスト有りグラフ
class Graph {
   public:
    ll V;                               // 頂点の個数
    vector<vector<pair<ll, ll>>> conn;  // 隣接リスト(vector)
    vector<vector<pair<ll, ll>>> prev;  // 有向グラフの場合の逆辺

    Graph(ll v) : V(v), conn(v), prev(v) {}

    // 有向グラフ
    void add_directed_edge(ll from, ll to, ll cost) {
        conn[from].push_back({to, cost});
        prev[to].push_back({from, -cost});
    }

    // 無向グラフ
    void add_undirected_edge(ll v1, ll v2, ll cost) {
        add_directed_edge(v1, v2, cost);
        add_directed_edge(v2, v1, cost);
    }
};

ll mod = 998244353;
ll N, M, i, j, k, l;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    Graph graph = Graph(N);
    REP(i, M) {
        cin >> j >> k >> l;
        // graph.add_directed_edge(j - 1, k - 1, l);
        // graph.add_undirected_edge(j - 1, k - 1, l);
    }
}