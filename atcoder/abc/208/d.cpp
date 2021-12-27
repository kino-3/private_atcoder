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
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
}

class Graph {
   public:
    ll V;                               // 頂点の個数
    vector<vector<pair<ll, ll>>> conn;  // 隣接リスト(vector)
    vector<vector<pair<ll, ll>>> prev;  // 有向グラフの場合の逆辺

    Graph(ll v) : V(v), conn(v), prev(v) {}

    // 有向グラフ
    void add_directed_edge(ll from, ll to, ll cost) {
        conn[from].push_back({to, cost});
        prev[to].push_back({from, cost});
    }
};

const ll mod = 998244353;
ll N, M, Q, i, j, k, l, s, t;
vector<ll> A, B, C;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    const ll INF = 100000000000;

    cin >> N >> M;
    A.resize(M);
    B.resize(M);
    C.resize(M);
    REP(i, M) {
        cin >> A[i] >> B[i] >> C[i];
        A[i]--;
        B[i]--;
    }

    Graph G = Graph(N);
    REP(i, M) { G.add_directed_edge(A[i], B[i], C[i]); }

    ll ans = 0;
    REP(s, N) {
        vector<ll> tmp_cost(N, INF);
        tmp_cost[s] = 0;
        for (auto v : G.conn[s]) {
            tmp_cost[v.first] = v.second;
        }
        REP(k, N) {
            // Dijkstra とかだと O(N^4) が必要
            for (auto v : G.conn[k]) {
                tmp_cost[v.first] =
                    min(tmp_cost[v.first], tmp_cost[k] + v.second);
            }
            REP(t, N) {
                if (tmp_cost[t] != INF && s != t) {
                    ans += tmp_cost[t];
                }
            }
        }
    }
    cout << ans << endl;
}