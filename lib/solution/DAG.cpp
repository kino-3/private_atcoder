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

template <typename T>
void debug_print(const T item) {
    cout << item << endl;
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}

// - DAG であるかの判定
// - DAG のトポロジカルソート(辞書順最小 or 任意の順)
class DAG {
    int V;  // 頂点の個数
    vector<vector<ll>> edges;

   public:
    DAG(int v) : V(v), edges(v) {}

    void add_edge(ll from, ll to) { edges[from].push_back(to); }

    // O(V log V) ?
    // 辞書順最小であることを保証
    // DAG ではないときは,  res.size() != (ノード数)
    vector<ll> topological_sort_abc() {
        vector<ll> res;
        vector<ll> indegree(V, 0);
        for (const auto& edge : edges) {
            for (const auto& to : edge) {
                indegree[to]++;
            }
        }
        // 入次数 0 の頂点を入れる
        priority_queue<ll, vector<ll>, greater<ll>> que;
        for (ll v = 0; v < V; v++) {
            if (indegree[v] == 0) {
                que.push(v);
            }
        }
        while (!que.empty()) {
            ll node = que.top();
            que.pop();
            res.push_back(node);
            for (const auto& to : edges[node]) {
                indegree[to]--;
                if (indegree[to] == 0) {
                    // 閉路に属するノードはいつまでも入次数
                    // が正なので, que に追加されない
                    que.push(to);
                }
            }
        }
        return res;
    }

    // O(V + E)
    // 辞書順最小であることを保証しない
    // DAG ではないときは,  res.size() != (ノード数)
    vector<ll> topological_sort() {
        vector<ll> res;
        vector<ll> indegree(V, 0);
        for (const auto& edge : edges) {
            for (const auto& to : edge) {
                indegree[to]++;
            }
        }
        // 入次数 0 の頂点を入れる
        queue<ll> que;
        for (ll v = 0; v < V; v++) {
            if (indegree[v] == 0) {
                que.push(v);
            }
        }
        while (!que.empty()) {
            ll node = que.front();
            que.pop();
            res.push_back(node);
            for (const auto& to : edges[node]) {
                indegree[to]--;
                if (indegree[to] == 0) {
                    // 閉路に属するノードはいつまでも入次数
                    // が正なので, que に追加されない
                    que.push(to);
                }
            }
        }
        return res;
    }
};

ll mod = 1000000007;
ll N, M, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    DAG dag = DAG(N);
    REP(i, M) {
        cin >> j >> k;
        dag.add_edge(j - 1, k - 1);
    }
    auto ans = dag.topological_sort_abc();
    // if (ans.size() == N) {
    //     REP(i, N - 1) { cout << ans[i] + 1 << " "; }
    //     cout << ans[N - 1] + 1 << endl;
    // } else {
    //     cout << -1 << endl;
    // }
}