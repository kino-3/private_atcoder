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

void debug_print() { cout << endl; }
template <class Head, class... Tail>
void debug_print(Head &&head, Tail &&...tail) {
    std::cout << head << ", ";
    debug_print(std::forward<Tail>(tail)...);
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}
template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto &&item : vec) {
        print_v(item);
    }
}
template <typename K, typename V>
void print_map(const map<K, V> dict) {
    for (const auto v : dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v : data) {
        cout << v << ", ";
    }
    cout << endl;
}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {
    cout << "(" << data.first << "," << data.second << ")";
    // cout << endl;
}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {
    cout << "(";
    cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
    cout << ")";
    // cout << endl;
}

// 単始点全終点最短距離
// O(E logV)
// 条件: edge の重みは非負
// 動作確認
// - https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=6080524#1
// - https://atcoder.jp/contests/abc218/tasks/abc218_f
class Dijkstra {
    ll V;                                // 頂点の個数
    vector<vector<pair<ll, ll>>> edges;  // {to, cost}
    const ll INF = numeric_limits<ll>::max();

   public:
    vector<ll> dist;         // dist[v]: v までの最短距離
    vector<bool> reachable;  // 到達可能か
    vector<ll> prev;  // prev[v]: v までの最短経路における直前の node

    Dijkstra(ll v) : V(v), edges(v) {}

    void add_edge(ll from, ll to, ll edge_cost) {
        edges[from].push_back({to, edge_cost});
    }

    void exec(ll start_node) {
        typedef pair<ll, ll> P;  // first は最短距離, second は node
        priority_queue<P, vector<P>, greater<P>> que;
        dist.resize(V, INF);
        prev.resize(V, -1);
        dist[start_node] = 0;
        que.push({0, start_node});
        while (!que.empty()) {
            P p = que.top();  // ノード p.second には距離 p.first で到達可能
            que.pop();
            ll node = p.second;
            if (dist[node] < p.first) {
                continue;
            }
            for (auto &&edge : edges[node]) {
                if (dist[edge.first] > dist[node] + edge.second) {
                    dist[edge.first] = dist[node] + edge.second;
                    que.push({dist[edge.first], edge.first});
                    prev[edge.first] = node;
                }
            }
        }
        reachable.resize(V);
        for (ll v = 0; v < V; v++) {
            reachable[v] = (dist[v] != INF);
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

const ll mod = 998244353;
ll N, M, Q, i, j, k, l;
vector<ll> L, R, X;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    L.resize(M);
    R.resize(M);
    X.resize(M);
    REP(i, M) {
        cin >> L[i] >> R[i] >> X[i];
        L[i]--;
        R[i]--;
    }

    // d[i]: i 未満の j のうち, A[j] が 0 のものの個数
    // 制約
    // - d[i+1] >= d[i] (単調増加)
    // - d[i] + 1 >= d[i] (増加量は高々1)
    // - d[r+1] - d[l] <= r - l + 1 - x (X[i] に関する制約)
    //   すなわち, d[l] + (r - l + 1 - x) >= d[r+1]
    // 答: d[N] - d[0]

    Dijkstra graph = Dijkstra(N + 1);
    REP(i, N) {
        graph.add_edge(i + 1, i, 0);
        graph.add_edge(i, i + 1, 1);
    }
    REP(i, M) { graph.add_edge(L[i], R[i] + 1, R[i] - L[i] + 1 - X[i]); }
    graph.exec(0);

    // print_v(graph.dist);

    REP(i, N) {
        cout << (graph.dist[i + 1] - graph.dist[i] == 1 ? '0' : '1') << " ";
    }
    cout << endl;
}