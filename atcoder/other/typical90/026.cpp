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
    ll V;                      // 頂点の個数
    vector<vector<ll>> graph;  // 隣接リスト

   public:
    vector<ll> parent;        // 頂点の親ノード
    vector<ll> subtree_size;  // subtree_size
    vector<ll> centroids;     // 木の重心
    vector<ll> depth;         // ある点からの距離
    vector<ll> sub;           // どの sub の部分木か
    vector<ll> sub_list;      // sub の種類を集めたもの
    vector<vector<pair<ll, ll>>> child_info;

    Tree(ll v)
        : V(v),
          graph(v),
          depth(v),
          sub(v),
          parent(v, -1),
          subtree_size(v, -1) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // v の部分木(vを含む)のサイズ
    // 計算量 O(V)
    // (parent, subtree_size も更新する)
    // すなわち, (vと隣接する) parent_of_v を取り除いたときの
    // v を含む木の頂点数
    // 外部から呼び出すときは calc_subtree_size(root) とすること
    ll calc_subtree_size(ll v, ll parent_of_v = -1) {
        parent[v] = parent_of_v;
        ll size = 1;
        for (const auto& child : graph[v]) {
            if (child == parent_of_v) continue;  // 隣接リストなので
            size += calc_subtree_size(child, v);
        }
        subtree_size[v] = size;
        return size;
    }

    // depth と sub に以下の情報を格納する
    // depth[v] == (root から vの距離)
    // sub[v] == (rootからvまでの経路でrootに隣接する頂点)
    // sub_list == (sub の集合)
    // 外部から呼び出すときは calc_depth(root) とすること
    void calc_depth(ll v, ll parent_of_v = -1) {
        if (parent_of_v == -1) {
            calc_subtree_size(v);
            sub_list.clear();
            depth[v] = 0;
            for (const auto& child : graph[v]) {
                // child は root に隣接する node
                depth[child] = 1;
                sub[child] = child;
                sub_list.push_back(child);
                calc_depth(child, v);
            }
        } else {
            for (const auto& child : graph[v]) {
                if (child == parent_of_v) continue;  // 隣接リストなので
                depth[child] = depth[v] + 1;
                sub[child] = sub[v];
                calc_depth(child, v);
            }
        }
    }

    // 木を root で吊ったときの木の深さに関する情報を調べる
    // - 戻り値は, v を含む v 以下の部分木の深さ
    // - child_info[v] に以下の情報を格納する
    // 全ての v の子 child について,
    // {child 以下の部分木の深さ, child} を要素とする vector
    // https://atcoder.jp/contests/typical90/tasks/typical90_c で動作確認済み
    ll calc_child_info(ll v, ll parent_of_v = -1) {
        if (parent_of_v == -1) {
            child_info.clear();
            for (ll i = 0; i < V; i++) {
                child_info.push_back(vector<pair<ll, ll>>(0));
            }
        }
        ll max_depth = 1;  // child がいないときの深さは 1
        for (const auto& child : graph[v]) {
            if (child == parent_of_v) continue;
            ll depth = calc_child_info(child, v);
            child_info[v].push_back({depth, child});
            max_depth = max(max_depth, depth + 1);
        }
        return max_depth;
    }

    // calc_subtree_size + 重心分解
    // 計算量 O(V)
    // (parent, subtree_size, centroids も更新する)
    // 外部から呼び出すときは find_centroid(root) とすること
    void find_centroid(ll v, ll parent_of_v = -1) {
        if (parent_of_v == -1) {  // 外部呼出し時に初期化
            centroids.clear();
            fill(subtree_size.begin(), subtree_size.end(), 1);
        }
        parent[v] = parent_of_v;
        bool is_centroid = true;
        for (const auto& child : graph[v]) {
            if (child == parent_of_v) continue;
            find_centroid(child, v);
            if (subtree_size[child] > V / 2) is_centroid = false;
            subtree_size[v] += subtree_size[child];
        }
        if (subtree_size[v] < (V + 1) / 2) {
            // v を親としたときの parent_of_v のサイズが V / 2 より大きい
            is_centroid = false;
        }
        if (is_centroid) centroids.push_back(v);
    }
};

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
    tree.calc_depth(0);
    ll even = 0;
    REP(i, N) {
        if (tree.depth[i] % 2 == 0) {
            even++;
        }
    }
    ll counter = 0;

    if (even < N / 2) {
        REP(i, N) {
            if (tree.depth[i] % 2 == 1) {
                counter++;
                cout << i + 1;
                if (counter == N / 2) {
                    cout << endl;
                    return 0;
                } else {
                    cout << " ";
                }
            }
        }
    } else {
        REP(i, N) {
            if (tree.depth[i] % 2 == 0) {
                counter++;
                cout << i + 1;
                if (counter == N / 2) {
                    cout << endl;
                    return 0;
                } else {
                    cout << " ";
                }
            }
        }
    }
}