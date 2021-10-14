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
    vector<vector<pair<ll, ll>>> child_info;

    Tree(ll v) : V(v), graph(v) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // 木を root で吊ったときの木の深さに関する情報を調べる
    // - 戻り値は, v を含む v 以下の部分木の深さ
    // - child_info[v] に以下の情報を格納する
    // 全ての v の子 child について,
    // {child 以下の部分木の深さ, child} を要素とする vector
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
};

ll N, i, p, q;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    Tree tree = Tree(N);
    REP(i, N - 1) {
        cin >> p >> q;
        tree.add_edge(p - 1, q - 1);
    }
    tree.calc_child_info(0);
    ll answer = -1;
    for (ll v = 0; v < N; v++) {
        auto depth_list = tree.child_info[v];
        if (depth_list.size() == 0) {
            continue;
        } else if (depth_list.size() == 1) {
            answer = max(answer, depth_list[0].first + 1);
        } else {
            sort(ALL(depth_list));
            reverse(ALL(depth_list));
            answer = max(answer, depth_list[0].first + depth_list[1].first + 1);
        }
    }
    cout << answer << endl;
}