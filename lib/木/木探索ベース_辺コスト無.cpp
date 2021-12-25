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

class Tree {
   public:
    ll V;                         // 頂点の個数
    vector<vector<ll>> graph;     // 隣接リスト
    vector<ll> parent;            // 親ノード
    vector<vector<ll>> children;  // 子ノード
    vector<ll> size;   // 自身を root とする部分木の大きさ
    vector<ll> depth;  // 深さ

    Tree(ll v) : V(v), graph(v), parent(v), children(v), size(v), depth(v) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // 頂点 v で吊ったときの木探索
    ll exec(ll v, ll parent_of_v = -1) {
        if (parent_of_v == -1) {
            depth[v] = 0;
        }
        parent[v] = parent_of_v;
        ll s = 1;
        for (const auto &child : graph[v]) {
            if (child == parent_of_v) continue;
            depth[child] = depth[v] + 1;
            s += exec(child, v);
            children[v].push_back(child);
        }
        size[v] = s;
        return s;
    }

    // LCA (O(n))
    ll lca(ll n1, ll n2) {
        while (depth[n1] > depth[n2]) n1 = parent[n1];
        while (depth[n1] < depth[n2]) n2 = parent[n2];
        while (n1 != n2) {
            n1 = parent[n1];
            n2 = parent[n2];
        }
        return n1;
    }

    // (始点と終点を含む)経路
    vector<ll> path(ll from_node, ll to_node) {
        vector<ll> res;
        ll path_lca = lca(from_node, to_node);
        while (from_node != path_lca) {
            res.push_back(from_node);
            from_node = parent[from_node];
        }
        vector<ll> rev_path;
        while (to_node != path_lca) {
            rev_path.push_back(to_node);
            to_node = parent[to_node];
        }
        reverse(rev_path.begin(), rev_path.end());
        res.push_back(path_lca);
        for (auto v : rev_path) {
            res.push_back(v);
        }
        return res;
    }
};

// input
// N
// a_1   b_1
// a_2   b_2
//  :
// a_N-1 a_N-1

ll N, i, j, k;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    Tree tree = Tree(N);
    REP(i, N - 1) {
        cin >> j >> k;
        tree.add_edge(j - 1, k - 1);
    }
    tree.exec(0);
}