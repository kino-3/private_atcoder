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
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto&& item : vec) {
        print_v(item);
    }
}
template <typename K, typename V>
void print_map(const map<K, V> dict) {
    for (const auto v : dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v : data) {
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

// copy from union_find_tree.cpp
class UnionFind {
   public:
    // 根ノードなら -(データ数)
    // それ以外なら親ノード
    // が格納される
    std::vector<ll> data;

    UnionFind(ll size) : data(size, -1) {}

    // 集合を併合する
    // 併合できたかを返す(すでに同じ木に属するなら併合不要なのでfalse)
    bool unite(ll x, ll y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (data[y] < data[x]) std::swap(x, y);
            // 要素数の大きな方(x)へyを合併する
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }

    // 同じ木に属するか
    bool find(ll x, ll y) { return root(x) == root(y); }

    // 属する木の根を返す
    // (その過程で根まで辿ったノードを根に付ける)
    ll root(ll x) { return (data[x] < 0) ? x : data[x] = root(data[x]); }

    // 集合の要素数を返す
    ll size(ll x) { return -data[root(x)]; }
};

// from, to の区別はない(無向グラフ)
struct edge {
    ll from;
    ll to;
    ll cost;
};

bool comp(const edge& e1, const edge& e2) { return e1.cost < e2.cost; }

// 動作確認: https://atcoder.jp/contests/typical90/tasks/typical90_aw
// O(E logV)
class Kruskal {
    ll V;  // 頂点の個数
    ll E;  // 辺の個数
    vector<edge> edges;
    vector<pair<ll, ll>> links;

    const ll INF = numeric_limits<ll>::max();

   public:
    Kruskal(ll v, ll e) : V(v), E(e) {}

    // from, to の区別はない(無向グラフ)
    void add_edge(ll from, ll to, ll cost) {
        edges.push_back({from, to, cost});
    }

    ll exec() {
        ll total_cost = 0;
        sort(edges.begin(), edges.end(), comp);  // コストの小さい順にソート
        UnionFind union_find = UnionFind(V);
        for (const auto& edge : edges) {
            if (!union_find.find(edge.from, edge.to)) {
                union_find.unite(edge.from, edge.to);
                total_cost += edge.cost;
                links.push_back({edge.from, edge.to});
            }
        }
        return total_cost;
    }
};

const ll mod = 998244353;
ll N, M, i, j, k, l;
vector<ll> A, B, C;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    A.resize(M);
    B.resize(M);
    C.resize(M);
    REP(i, M) { cin >> A[i] >> B[i] >> C[i]; }

    Kruskal tree = Kruskal(N, M);
    REP(i, M) { tree.add_edge(A[i] - 1, B[i] - 1, max(0LL, C[i])); }

    ll ans = 0;
    REP(i, M) { ans += max(0LL, C[i]); }

    cout << ans - tree.exec() << endl;
}