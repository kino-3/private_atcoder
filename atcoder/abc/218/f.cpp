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

struct edge {
    int to;
    ll cost;
};

// TODO: 動作未検証
// TODO: アルゴリズム未検証
// dijkstra.cpp を改造
class Dijkstra2 {
    int V;                       // 頂点の個数
    vector<vector<edge>> edges;  // edges[v] の要素は, v から 要素.to への edge
    vector<ll> dist;             // dist[v]: v までの最短距離
    vector<ll> dist2;            // dist2[v]: v までの2番目に短い距離
    vector<int> prev;            // 最短経路における直前の node
    vector<int> prev2;  // 2番目に短い経路における直前の node
    const ll INF = numeric_limits<ll>::max();

   public:
    Dijkstra2(int v)
        : V(v), edges(v, vector<edge>(0)), dist(v), prev(v), prev2(v) {}

    void add_edge(int from, int to, ll edge_cost) {
        edges[from].push_back({to, edge_cost});
    }

    void exec(int start_node) {
        typedef pair<ll, int> P;  // first は最短距離, second は node
        priority_queue<P, vector<P>, greater<P>> que;
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
            dist2[i] = INF;
            prev[i] = -1;
            prev2[i] = -1;
        }
        dist[start_node] = 0;
        que.push({0, start_node});
        while (!que.empty()) {
            P p = que.top();  // ノード p.second には距離 p.first で到達可能
            que.pop();
            int node = p.second;
            if (dist[node] < p.first) {
                continue;
            }
            for (auto &&edge : edges[node]) {
                ll distance = p.first + edge.cost;
                if (dist[edge.to] > distance) {
                    swap(dist[edge.to], distance);
                    que.push({dist[edge.to], edge.to});
                    prev[edge.to] = node;
                }
                if (dist2[edge.to] > distance && dist[edge.to] < distance) {
                    // dist[edge.to] < distance は 最短距離 == 2番目に短い距離
                    // とならないようにするため
                    dist2[edge.to] = distance;
                    que.push({dist2[edge.to], edge.to});
                    prev2[edge.to] = node;
                }
            }
        }
    }

    // 頂点 v までの最小コスト
    ll cost(int v) { return dist[v]; }

    // 頂点 v までの2番目に小さいコスト
    ll cost2(int v) { return dist2[v]; }

    int get_prev(int v) { return prev[v]; }

    int get_prev2(int v) { return prev2[v]; }
};

const ll mod = 998244353;
ll N, M, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    A.resize(M);
    B.resize(M);
    REP(i, M) { cin >> A[i] >> B[i]; }

    Dijkstra2 graph = Dijkstra2(N);

    REP(i, M) { graph.add_edge(A[i] - 1, B[i] - 1, 1); }

    graph.exec(0);

    ll ans1 = graph.cost(N - 1);
    ll ans2 = graph.cost2(N - 1);

    if (ans1 == ans2) {
        REP(i, M) cout << ans1 << endl;
    } else {
        set<pair<ll, ll>> path;
        ll cnt = N - 1;
        while (cnt != 0) {
            ll prev_n = graph.get_prev(cnt);
            path.insert({prev_n, cnt});
            cnt = prev_n;
        }
        REP(i, M) {
            if (path.count({A[i] - 1, B[i] - 1}) > 0) {
                Dijkstra2 g2 = Dijkstra2(N);
                REP(j, M) {
                    if (i == j) continue;
                    g2.add_edge(A[i] - 1, B[i] - 1, 1);
                }
                g2.exec(0);
                ll cc = g2.cost(N - 1);
                if (cc > 1000)
                    cout << -1 << endl;
                else
                    cout << cc << endl;
            } else {
                cout << ans1 << endl;
            }
        }
    }
}