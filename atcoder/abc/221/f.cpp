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

template <typename T>
void debug_print(const T item) {
    cout << item << endl;
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
    for (auto it = dict.begin(); it != dict.end(); ++it) {
        cout << it->first << ":" << it->second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (auto it = data.begin(); it != data.end(); ++it) {
        cout << *it << ", ";
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

ll radius = 0;

// 動作確認: https://atcoder.jp/contests/abc222/tasks/abc222_f
class Tree {
   public:
    ll V;                                // 頂点の個数
    vector<vector<pair<ll, ll>>> graph;  // 隣接リスト{node,cost}
    // exec により更新される情報
    vector<ll> parent;            // 親ノード
    vector<vector<ll>> children;  // 子ノード
    vector<ll> depth;             // root からの距離
    pair<ll, ll> max_depth;       // {最大深さ,node}
    ll cc;

    Tree(ll v) : V(v), graph(v) {}

    void add_edge(ll n1, ll n2, ll cost = 1) {
        graph[n1].push_back({n2, cost});
        graph[n2].push_back({n1, cost});
    }

    void reset() {
        parent.clear();
        children.clear();
        depth.clear();
        parent.resize(V);
        children.resize(V);
        depth.resize(V, -1);
        max_depth = {-1, -1};
    }

    // 頂点 v で吊ったときの木探索(DFS)
    // O(V)
    void exec(ll v, ll parent_of_v = -1) {
        if (parent_of_v == -1) {
            reset();
            depth[v] = 0;
        }
        parent[v] = parent_of_v;
        for (const auto &child : graph[v]) {
            ll node = child.first;
            ll cost = child.second;
            if (node == parent_of_v) continue;
            depth[node] = depth[v] + cost;
            if (max_depth.first < depth[node]) {
                max_depth = {depth[node], node};
            }
            exec(child.first, v);
            children[v].push_back(node);
        }
    }

    vector<ll> exec2(ll v, ll parent_of_v = -1) {
        vector<ll> ans;
        if (parent_of_v == -1) {
            reset();
            depth[v] = 0;
        }
        parent[v] = parent_of_v;
        for (const auto &child : graph[v]) {
            if (parent_of_v == -1) cc = 0;
            ll node = child.first;
            ll cost = child.second;
            if (node == parent_of_v) continue;
            depth[node] = depth[v] + cost;
            if (depth[node] == radius) {
                cc++;
            }
            exec2(child.first, v);
            ans.push_back(cc);
        }
        return ans;
    }

    // {直径, {s,t}} を返す
    // O(N)
    // 動作確認: https://atcoder.jp/contests/abc222/tasks/abc222_f
    // 全始点最長経路の場合は, このあと exec(s), exec(t) を行い,
    // 各 i について depth[i] の大きい方
    pair<ll, pair<ll, ll>> calc_diameter() {
        exec(0);
        ll s = max_depth.second;
        exec(s);
        return {max_depth.first, {s, max_depth.second}};
    }
};

// input
// N
// a_1   b_1   c_1
// a_2   b_2   c_2
//  :
// a_N-1 b_N-1 c_N-1

const ll mod = 998244353;
ll N, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N - 1);
    B.resize(N - 1);
    REP(i, N - 1) cin >> A[i] >> B[i];

    Tree tree = Tree(N);
    REP(i, N - 1) tree.add_edge(A[i] - 1, B[i] - 1);

    auto diameter = tree.calc_diameter();
    ll d = diameter.first;
    if (d % 2 == 1) {
        ll tmp = diameter.second.second;
        REP(i, d / 2) { tmp = tree.parent[tmp]; }
        ll c1 = tmp;
        ll c2 = tree.parent[tmp];
        tree.reset();
        tree.depth[c1] = 0;
        tree.exec(c1, c2);
        ll tmp1 = count(ALL(tree.depth), d / 2);
        tree.reset();
        tree.depth[c2] = 0;
        tree.exec(c2, c1);
        ll tmp2 = count(ALL(tree.depth), d / 2);
        cout << tmp1 * tmp2 % mod << endl;
    } else {
        ll tmp = diameter.second.second;
        radius = d / 2;
        REP(i, d / 2) { tmp = tree.parent[tmp]; }
        ll c = tmp;
        vector<ll> counts = tree.exec2(c);
        // print_v(tree.depth);
        // print_v(counts);
        ll ans = 1;
        ll accum = 0;
        for (auto v : counts) {
            ans *= v + 1;
            ans %= mod;
            accum += v;
        }
        ans += mod;
        ans -= 1 + accum;
        ans %= mod;
        cout << ans << endl;
    }
}