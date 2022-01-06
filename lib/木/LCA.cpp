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

// LCA の動作確認: https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6185167#1
class Tree {
   public:
    ll V;                         // 頂点の個数
    vector<vector<ll>> graph;     // 隣接リスト
    vector<ll> parent;            // 親ノード
    vector<vector<ll>> ancestor;  // ancestor[i][j]: j の 2^i 階層上
    vector<vector<ll>> children;  // 子ノード
    vector<ll> size;   // 自身を root とする部分木の大きさ
    vector<ll> depth;  // 深さ

    Tree(ll v)
        : V(v),
          graph(v),
          parent(v),
          children(v),
          size(v),
          depth(v),
          ancestor(ll(log2(v)) + 2, vector<ll>(v, -1)) {}

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
        if (parent_of_v == -1) {
            ancestor[0] = parent;
            ll i, j;
            REP(i, ancestor.size() - 1) {
                REP(j, V) {
                    if (ancestor[i][j] == -1) {
                        ancestor[i + 1][j] = -1;
                    } else {
                        ancestor[i + 1][j] = ancestor[i][ancestor[i][j]];
                    }
                }
            }
        }
        return s;
    }

    // node の distance だけ親のノード
    // O(log V)
    ll get_ancestor(ll node, ll distance) {
        ll cnt = node;
        ll i;
        REP(i, ancestor.size()) {
            if (distance == 0) {
                return cnt;
            }
            if (distance % 2 == 1) {
                cnt = ancestor[i][cnt];
            }
            distance /= 2;
        }
        return cnt;
    }

    // LCA (O(log V))
    ll lca(ll n1, ll n2) {
        if (depth[n1] > depth[n2]) n1 = get_ancestor(n1, depth[n1] - depth[n2]);
        if (depth[n1] < depth[n2]) n2 = get_ancestor(n2, depth[n2] - depth[n1]);
        ll i;
        REP_R(i, ancestor.size()) {
            if (ancestor[i][n1] != ancestor[i][n2]) {
                n1 = ancestor[i][n1];
                n2 = ancestor[i][n2];
            }
        }
        if (n1 != n2) {
            n1 = parent[n1];
            n2 = parent[n2];
        }
        return n1;
    }
};

// input
// N
// a_1   b_1
// a_2   b_2
//  :
// a_N-1 a_N-1

const ll mod = 998244353;  // 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // cin >> N;
    // Tree tree = Tree(N);
    // REP(i, N - 1) {
    //     cin >> j >> k;
    //     tree.add_edge(j - 1, k - 1);
    // }

    // cin >> Q;
    // A.resize(Q);
    // B.resize(Q);
    // REP(i, Q) {
    //     cin >> A[i];
    //     cin >> B[i];
    // }

    // tree.exec(0);
    // REP(i, Q) {
    //     cout << tree.lca(A[i], B[i]) << endl;
    // }
}
