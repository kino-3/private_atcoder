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

// TODO: 動作未検証
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

ll N, M, i, c, l, r;
vector<ll> C, L, R;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    Kruskal kruskal = Kruskal(N + 1, M);
    UnionFind uf = UnionFind(N + 1);
    REP(i, M) {
        cin >> c >> l >> r;
        kruskal.add_edge(l - 1, r, c);
        uf.unite(l - 1, r);
    }
    if (uf.size(0) != N + 1) {
        cout << -1 << endl;
    } else {
        cout << kruskal.exec() << endl;
    }
}