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

// コスト無しグラフ
class Graph {
   public:
    ll V;                     // 頂点の個数
    vector<vector<ll>> conn;  // 隣接リスト(vector)
    vector<vector<ll>> prev;  // 有向グラフの場合の逆辺

    Graph(ll v) : V(v), conn(v), prev(v) {}

    // 有向グラフ
    void add_directed_edge(ll from, ll to) {
        conn[from].push_back(to);
        prev[to].push_back(from);
    }

    // 無向グラフ
    void add_undirected_edge(ll v1, ll v2) {
        add_directed_edge(v1, v2);
        add_directed_edge(v2, v1);
    }
};

ll mod = 1000000007;
ll N, M, i, j, k, l;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    Graph graph = Graph(N);
    REP(i, M) {
        cin >> j >> k;
        // graph.add_directed_edge(j - 1, k - 1);
        graph.add_undirected_edge(j - 1, k - 1);
    }
    vector<bool> flg(N, false);
    vector<ll> dp(N, 0);
    set<ll> node;
    flg[0] = true;
    dp[0] = 1;
    node.insert(0);
    while (true) {
        set<ll> new_node;
        for (auto v : node) {
            for (auto vv : graph.conn[v]) {
                if (flg[vv]) continue;
                new_node.insert(vv);
                dp[vv] += dp[v];
                dp[vv] %= mod;
            }
        }
        node = new_node;
        for (auto v : node) {
            flg[v] = true;
        }
        if (flg[N - 1]) {
            cout << dp[N - 1] << endl;
            return 0;
        }
        if (node.empty()) {
            cout << 0 << endl;
            return 0;
        }
    }
}