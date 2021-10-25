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

class StronglyConnectedComponents {
    int V;  // 頂点の個数
    vector<vector<ll>> graph;
    vector<vector<ll>> rev_graph;  // 逆辺
    vector<vector<ll>> scc;  // 結果を(execの戻り値とは別形式で)保存するだけ

    void dfs(ll v, vector<bool>& used, vector<ll>& nodes) {
        used[v] = true;
        for (const auto& to : graph[v]) {
            if (!used[to]) {
                dfs(to, used, nodes);
            }
        }
        nodes.push_back(v);  // 帰りがけ順
    }

    void rev_dfs(ll v, ll current_order, vector<bool>& used, vector<ll>& res) {
        used[v] = true;
        res[v] = current_order;
        scc[current_order].push_back(v);
        for (const auto& to : rev_graph[v]) {
            if (!used[to]) {
                rev_dfs(to, current_order, used, res);
            }
        }
    }

   public:
    StronglyConnectedComponents(int v) : V(v), graph(v), rev_graph(v) {}

    void add_edge(ll from, ll to) {
        graph[from].push_back(to);
        rev_graph[to].push_back(from);
    }

    // O(V + E)
    vector<ll> exec() {
        vector<bool> used(V, false);
        vector<ll> nodes;
        for (ll v = 0; v < V; v++) {
            if (!used[v]) dfs(v, used, nodes);
        }
        fill(used.begin(), used.end(), false);
        ll current_order = 0;
        vector<ll> res(V);
        scc.clear();
        for (ll i = V - 1; i >= 0; i--) {
            if (!used[nodes[i]]) {
                scc.push_back(vector<ll>(0));
                rev_dfs(nodes[i], current_order, used, res);
                current_order++;
            }
        }
        return res;
    }

    vector<vector<ll>> get_scc() { return scc; }
};

ll N, M, i, j, k;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    StronglyConnectedComponents scc = StronglyConnectedComponents(N);
    REP(i, M) {
        cin >> j >> k;
        scc.add_edge(j - 1, k - 1);
    }
    scc.exec();

    ll ans = 0;
    vector<vector<ll>> result = scc.get_scc();
    for (const auto& res : result) {
        ll size = res.size();
        ans += size * (size - 1) / 2;
    }
    cout << ans << endl;
}