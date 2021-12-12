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

void debug_print() { cout << endl; }
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
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto&& item : vec) {
        print_pair(item);
    }
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
    ll idx;
};

// 負の辺があってもよい
// 自己ループや多重辺があってもよい
// 動作確認
// - https://atcoder.jp/contests/typical90/tasks/typical90_aw
// - https://atcoder.jp/contests/abc218/tasks/abc218_e
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
    void add_edge(ll from, ll to, ll cost, ll idx) {
        edges.push_back({from, to, cost, idx});
    }

    // 最小全域木の総コストを返す
    vector<bool> exec() {
        vector<bool> use(E, false);
        ll total_cost = 0;
        sort(edges.begin(), edges.end(), [](const edge& e1, const edge& e2) {
            return e1.cost < e2.cost;
        });  // コストの小さい順にソート
        UnionFind union_find = UnionFind(V);
        for (const auto& edge : edges) {
            if (!union_find.find(edge.from, edge.to)) {
                union_find.unite(edge.from, edge.to);
                use[edge.idx] = true;
                total_cost += edge.cost;
                links.push_back({edge.from, edge.to});
            }
        }
        return use;
    }
};

const ll mod = 998244353;
ll N, M, i, j, k, l;
vector<ll> X, Y;
vector<pair<ll, ll>> graph;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    N = 400;
    M = 1995;
    X.resize(N);
    Y.resize(N);
    // 事前入力
    REP(i, N) { cin >> X[i] >> Y[i]; }
    REP(i, M) {
        cin >> j >> k;
        graph.push_back({j, k});
    }
    // 前処理
    vector<ll> dist;
    REP(i, M) {
        ll dx = X[graph[i].first] - X[graph[i].second];
        ll dy = Y[graph[i].first] - Y[graph[i].second];
        ll dist2 = dx * dx + dy * dy;
        dist.push_back(int(sqrt(dist2) + 0.500000001));
    }
    // print_v(dist);
    Kruskal tree = Kruskal(N, M);
    REP(i, M) { tree.add_edge(graph[i].first, graph[i].second, dist[i], i); }
    auto used = tree.exec();

    // // クエリ処理
    REP(i, M) {
        cin >> j;
        bool should_use = used[i];
        if (should_use) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
}