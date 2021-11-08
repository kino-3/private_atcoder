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
    vector<ll> size;    // 自身を root とする部分木の大きさ
    vector<bool> is_a;  // a かどうか
    vector<ll> tw;      // 満たす部分木の数
    vector<ll> fw;      // 満たさない部分木の数
    ll mod = 1000000007;

    Tree(ll v)
        : V(v),
          graph(v),
          parent(v),
          children(v),
          size(v),
          is_a(v),
          tw(v),
          fw(v) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // 頂点 v で吊ったときの木探索
    ll exec(ll v, ll parent_of_v = -1) {
        // if (parent_of_v == -1) {}
        parent[v] = parent_of_v;
        ll s = 1;
        tw[v] = 1;
        fw[v] = 1;
        for (const auto& child : graph[v]) {
            if (child == parent_of_v) continue;
            exec(child, v);
            children[v].push_back(child);
            if (is_a[v] == is_a[child]) {
                fw[v] *= (fw[child] + tw[child]);
                fw[v] %= mod;
            } else {
                fw[v] *= tw[child];
                fw[v] %= mod;
            }
            tw[v] *= (fw[child] + tw[child] * 2);
            tw[v] %= mod;
        }
        tw[v] += mod;
        tw[v] -= fw[v];
        tw[v] %= mod;
        size[v] = s;
        return tw[v];
    }
};

ll mod = 1000000007;
ll N, i, j, k, l;
char c;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    Tree tree = Tree(N);
    REP(i, N) {
        cin >> c;
        tree.is_a[i] = (c == 'a');
    }
    REP(i, N - 1) {
        cin >> j >> k;
        tree.add_edge(j - 1, k - 1);
    }
    cout << tree.exec(0) << endl;
}