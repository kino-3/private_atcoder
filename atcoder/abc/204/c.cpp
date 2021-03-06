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

// O(V^3)
// edge ???????????????????????????
// ????????????????????????????????????
// dist[v][v] < 0 ??????????????? v ????????????, ???????????????????????????
// ????????????: https://atcoder.jp/contests/abc208/tasks/abc208_d
class WarshallFloyd {
    ll V;                     // ???????????????
    vector<vector<ll>> dist;  // dist[from][to]: from -> to ??????????????????
    const ll INF = numeric_limits<ll>::max() / 10;

   public:
    WarshallFloyd(ll v) : V(v) {
        dist = vector<vector<ll>>(V, vector<ll>(V, INF));
        for (ll i = 0; i < V; ++i) {
            dist[i][i] = 0;  // ?????????????????????????????? cost ??? 0
        }
    }

    void add_edge(ll from, ll to, ll edge_cost) {
        dist[from][to] = edge_cost;  // k = -1 (i,j ????????????)
    }

    void exec() {
        for (ll k = 0; k < V; ++k) {
            // i,j ??? k ??????????????????????????????????????????, i -> j ???????????????
            for (ll i = 0; i < V; ++i) {
                for (ll j = 0; j < V; ++j) {
                    // dist[i][k] ??? i,k ??? k-1 ????????????
                    // (or i,k ??? k ????????????)
                    // (i,k ??????????????????????????????)
                    // ??????????????????????????????, i -> k ???????????????
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    ll count() {
        ll ans = 0;
        REP(i, V) {
            REP(j, V) {
                if (dist[i][j] < INF) {
                    ans++;
                } else {
                    ;  // debug_print(i, j);
                }
            }
        }
        return ans;
    }
};

ll mod = 998244353;
ll N, M, i, j, k, l;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    WarshallFloyd graph = WarshallFloyd(N);
    REP(i, M) {
        cin >> j >> k;
        graph.add_edge(j - 1, k - 1, 1);
    }
    graph.exec();
    cout << graph.count() << endl;
}