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


// 動作確認: https://atcoder.jp/contests/abc222/tasks/abc222_f
class Tree {
   public:
    ll V;                                // 頂点の個数
    vector<map<ll, ll>> graph;  // 隣接リスト{node,cost}
    // exec により更新される情報
    vector<ll> parent;            // 親ノード
    vector<vector<ll>> children;  // 子ノード
    vector<ll> depth;             // root からの距離
    pair<ll, ll> max_depth;       // {最大深さ,node}

    Tree(ll v) : V(v), graph(v) {}

    void add_edge(ll n1, ll n2, ll cost = 1) {
        graph[n1][n2] = cost;
        graph[n2][n1] = cost;
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
}