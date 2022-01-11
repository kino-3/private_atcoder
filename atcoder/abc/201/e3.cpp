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
            depth[node] = depth[v] ^ cost; // ここが XOR
            exec(child.first, v);
            children[v].push_back(node);
        }
    }
};

const ll mod = 1000000007;  // 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, B, C;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N - 1);
    B.resize(N - 1);
    C.resize(N - 1);
    REP(i, N - 1) cin >> A[i] >> B[i] >> C[i];

    Tree tree = Tree(N);
    REP(i, N - 1) tree.add_edge(A[i] - 1, B[i] - 1, C[i]);
    tree.exec(0);

    ll ans = 0;
    ll pow = 1;
    vector<std::bitset<100>> dist;
    // print_v(tree.depth);
    REP(i, N) {
        std::bitset<100> bs(tree.depth[i]);
        dist.push_back(bs);
    }

    REP(i, 60) {
        ll res = 0;
        REP(j, N) {
            if (dist[j][i]) res++;
        }
        debug_print(res);
        res *= (N - res);
        // debug_print(res);
        res %= mod;
        ans += res * pow;
        ans %= mod;
        pow *= 2;
        pow %= mod;
    }
    cout << ans << endl;
}