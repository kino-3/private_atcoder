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


// 自身を root とする部分木以外が存在しない考えた時の情報
struct subtree_info {
    ll d;
};
// 親ノードから伝播される情報
// 自身 -> 親 -> 自身 と伝播される可能性に注意する必要がある
struct parent_info {
    // first はどの接続 node 情報によるものか
    pair<ll, ll> best;
    pair<ll, ll> best2;
    ll ans;
};

// 全方位木DP (例は全始点最長距離)
// 動作確認: https://atcoder.jp/contests/abc222/tasks/abc222_f
class Tree {
   public:
    ll V;                         // 頂点の個数
    vector<vector<ll>> graph;     // 隣接リスト
    vector<ll> parent;            // 親ノード
    vector<vector<ll>> children;  // 子ノード
    vector<subtree_info> subtree_i;
    vector<parent_info> parent_i;

    Tree(ll v) : V(v), graph(v) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    void reset_data() {
        parent.clear();
        children.clear();
        subtree_i.clear();
        parent_i.clear();
        parent.resize(V);
        children.resize(V);
        subtree_i.resize(V);
        parent_i.resize(V);
    }

    void exec() {
        // 頂点数が 2 以下のとき
        if (V == 1) {
            // TODO
            assert(false);
            return;
        } else if (V == 2) {
            // TODO
            reset_data();
            parent_i[0].ans = 1;
            parent_i[1].ans = 1;
            return;
        }
        reset_data();
        // 頂点数が 3 以上のとき, 接続数が 2 以上の頂点を探す
        ll root = -1;
        REP(i, V) {
            if (graph[i].size() >= 2) {
                root = i;
                break;
            }
        }
        // 部分木情報を求める
        compute_subtree(root);
        // 答を求める
        compute_ans(root);
    }

    // 頂点 v 以下の部分木情報を求める
    void compute_subtree(ll v, ll parent_of_v = -1) {
        parent[v] = parent_of_v;
        for (const auto &node : graph[v]) {
            if (node == parent_of_v) continue;
            children[v].push_back(node);
            compute_subtree(node, v);
        }
        // 子ノードの部分木から subtree_i を求める
        if (children[v].size() == 0) {
            // TODO: 葉の場合
            subtree_i[v].d = 0;  // 例
        } else {
            // TODO: 葉以外の場合
            for (const auto &cv : children[v]) {
                subtree_i[v].d =
                    max(subtree_i[v].d, subtree_i[cv].d + 1);  // 例
            }
        }
    }

    // 頂点 v の答を求める
    // 使える情報は v の子ノードの subtree_i と v の親ノードの parent_i
    void compute_ans(ll v) {
        ll pv = parent[v];  // v の親ノード
        // 隣接ノードが 1 の時のための初期化
        parent_i[v].best = {v, 0};
        parent_i[v].best2 = {v, 0};
        if (pv != -1) {
            // v が親ノードを持つとき, 親ノードからの伝播
            if (parent_i[pv].best.first != v) {
                parent_i[v].best = {pv, parent_i[pv].best.second + 1};
            } else {
                parent_i[v].best = {pv, parent_i[pv].best2.second + 1};
            }
        }
        // 子ノードからの伝播
        for (const auto cv : children[v]) {
            ll cvl = subtree_i[cv].d + 1;
            if (cvl > parent_i[v].best.second) {
                parent_i[v].best2 = parent_i[v].best;
                parent_i[v].best = {cv, cvl};
            } else if (cvl > parent_i[v].best2.second) {
                parent_i[v].best2 = {cv, cvl};
            }
        }
        parent_i[v].ans = parent_i[v].best.second;
        // DFS
        for (const auto &child : children[v]) {
            compute_ans(child);
        }
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

    tree.exec();
    REP(i, N) cout << tree.parent_i[i].ans << endl;
}