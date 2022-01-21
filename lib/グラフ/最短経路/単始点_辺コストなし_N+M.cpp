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

// 単始点単終点最短距離
// O(N + M)
// 動作確認
// - https://atcoder.jp/contests/abc218/tasks/abc218_f
class BFS {
    ll V;                      // 頂点の個数
    vector<vector<ll>> edges;  // to

   public:
    const ll INF = numeric_limits<ll>::max();
    vector<ll> dist;  // dist[v]: v までの最短距離のメモ(途中で打ち切り)
    vector<ll> prev;  // prev[v]: v までの最短経路における直前の node

    BFS(ll v) : V(v), edges(v) {}

    void add_edge(ll from, ll to) { edges[from].push_back(to); }

    // 単一始点単一終点の最短距離(到達不可能なら-1)
    ll exec(ll start_node, ll end_node) {
        deque<ll> que;
        dist.resize(V, INF);
        prev.resize(V, -1);
        dist[start_node] = 0;
        que.push_back(start_node);
        while (!que.empty()) {
            ll node = que.front();
            que.pop_front();
            if (node == end_node) return dist[end_node];
            for (const auto v : edges[node]) {
                if (dist[v] == INF) {
                    dist[v] = dist[node] + 1;
                    prev[v] = node;
                    que.push_back(v);
                }
            }
        }
        return -1;
    }

    // 単一始点全終点の最短距離
    void exec_all(ll start_node) {
        deque<ll> que;
        dist.resize(V, INF);
        prev.resize(V, -1);
        dist[start_node] = 0;
        que.push_back(start_node);
        while (!que.empty()) {
            ll node = que.front();
            que.pop_front();
            for (const auto v : edges[node]) {
                if (dist[v] == INF) {
                    dist[v] = dist[node] + 1;
                    prev[v] = node;
                    que.push_back(v);
                }
            }
        }
    }

    // 経路復元(最短経路の1つ)
    vector<ll> path(ll v) {
        vector<ll> res;
        while (v > -1) {
            res.push_back(v);
            v = prev[v];
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

ll mod = 998244353;
ll N, M, i, j, k, l;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    BFS graph = BFS(N);
    REP(i, M) {
        cin >> j >> k;
        graph.add_edge(j - 1, k - 1);
    }
    graph.exec(0, N - 1);
}