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

#ifdef _DEBUG
void debug_print() {
    cout << endl;
}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {
    std::cout << head << ", ";
    debug_print(std::forward<Tail>(tail)...);
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}
template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto &&item : vec) {
        print_v(item);
    }
}
template <typename K, typename V>
void print_map(const map<K, V> dict) {
    for (const auto v: dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v: data) {
        cout << v << ", ";
    }
    cout << endl;
}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {
    cout << "(" << data.first << "," << data.second << ")";
    // cout << endl;
}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {
    cout << "(";
    cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
    cout << ")";
    // cout << endl;
}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
}
#else
void debug_print() {}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {}
void debug_print_count() {}
template <typename T>
void print_v(const vector<T> vec) {}
template <typename T>
void print_vv(const vector<T> vec) {}
template <typename K, typename V>
void print_map(const map<K, V> dict) {}
template <typename T>
void print_set(const set<T> data) {}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {}
#endif

// https://atcoder.jp/contests/typical90/tasks/typical90_u で確認済み
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

ll mod = 998244353;
ll N, M, i, j, k, l;
vector<ll> cost;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    StronglyConnectedComponents scc = StronglyConnectedComponents(N);
    REP(i, M) {
        cin >> j >> k;
        scc.add_edge(j - 1, k - 1);
        scc.add_edge(k - 1, j - 1);
    }
    cost.resize(N);
    REP(i, N) {
        cin >> cost[i];
    }
    print_v(cost);
}