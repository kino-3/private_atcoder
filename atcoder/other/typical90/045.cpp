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
    vector<set<ll>> scc;  // 結果を(execの戻り値とは別形式で)保存するだけ

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
        scc[current_order].insert(v);
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
                scc.push_back({});
                rev_dfs(nodes[i], current_order, used, res);
                current_order++;
            }
        }
        return res;
    }

    vector<set<ll>> get_scc() { return scc; }
};

class TwoSAT {
    int V;                            // 頂点の個数
    StronglyConnectedComponents scc;  // 0~v-1 は true, v~2v-1 は false のノード
    vector<bool> solution;            // 存在する場合の解

   public:
    TwoSAT(int v) : V(v), scc(2 * v), solution(v) {}

    // 制約 a => b を加える
    void add_a_b(int a, int b) { scc.add_edge(a, b); }

    // 制約 ￢a => b を加える
    void add_na_b(int a, int b) { scc.add_edge(a + V, b); }

    // 制約 a => ￢b を加える
    void add_a_nb(int a, int b) { scc.add_edge(a, b + V); }

    // 制約 ￢a => ￢b を加える
    void add_na_nb(int a, int b) { scc.add_edge(a + V, b + V); }

    // 制約 a or b を加える
    void add_a_or_b(int a, int b) {
        add_na_b(a, b);
        add_na_b(b, a);
    }

    // 制約 a xor b を加える
    void add_a_xor_b(int a, int b) {
        add_a_nb(a, b);
        add_a_nb(b, a);
    }

    // 制約 a を加える
    void add_a(int a) {
        // ￢A=>A は ￢￢AorA すなわち A と同値
        add_na_b(a, a);
    }

    // 制約 not a を加える
    void add_na(int a) { add_a_nb(a, a); }

    // 充足可能か
    bool exec() {
        scc.exec();
        auto components = scc.get_scc();
        vector<bool> determined(V, false);
        fill(solution.begin(), solution.end(), false);
        for (const auto& component : components) {
            for (const auto& node : component) {
                if (node < V) {
                    if (component.count(node + V) > 0) {
                        // true と false が同じ強連結成分
                        return false;
                    }
                    if (!determined[node]) {
                        determined[node] = true;
                        solution[node] = false;
                    }
                } else {
                    if (!determined[node - V]) {
                        determined[node - V] = true;
                        solution[node - V] = true;
                    }
                }
            }
        }
        return true;
    }

    vector<bool> get_solution() { return solution; }
};

ll N, K, i, j, k;
vector<ll> X, Y;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    REP(i, N) {
        cin >> j >> k;
        X.push_back(j);
        Y.push_back(k);
    }
    vector<vector<ll>> dist(N, vector<ll>(N));
    vector<pair<ll, pair<ll, ll>>> dist_list;
    REP(i, N) {
        REP(j, N) {
            ll d =
                (X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]);
            d = i < j ? 0 : d;
            dist[i][j] = d;
            dist_list.push_back({-d, {i, j}});
        }
    }
    sort(ALL(dist_list));
    TwoSAT twosat = TwoSAT((K + 1) * N);  // N * k + n: n がクラス k に属する
    REP(i, N) {
        twosat.add_na(N * K + i);
        REP(k, K) { twosat.add_a_or_b(N * K + i, N * k + i); }
    }
    REP(i, N * N) {
        twosat.add_na(N * 0 + 0);
        cout << twosat.exec() << endl;
        auto E = dist_list[i];
        ll x = E.second.first;
        ll y = E.second.second;
        cout << x << "," << y << endl;
        REP(k, K) {
            twosat.add_a_nb(N * k + x, N * k + y);
            twosat.add_a_nb(N * k + y, N * k + x);
        }
        if (!twosat.exec()) {
            cout << -E.first << endl;
            break;
        }
    }
}