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

// コスト無しグラフ
class Graph {
   public:
    ll V;                     // 頂点の個数
    vector<vector<ll>> conn;  // 隣接リスト(vector)
    vector<vector<ll>> prev;  // 逆辺の場合

    Graph(ll v) : V(v), conn(v, vector<ll>(0)), prev(v, vector<ll>(0)) {}

    void add_directed_edge(ll from, ll to) {
        conn[from].push_back(to);
        prev[to].push_back(from);
    }

    void add_undirected_edge(ll v1, ll v2) {
        add_directed_edge(v1, v2);
        add_directed_edge(v2, v1);
    }
};

ll mod = 1000000007;
ll thresh = 400;
ll N, M, Q, i, j, k, l;
vector<ll> query;
vector<pair<ll, ll>> memo;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M >> Q;
    Graph graph = Graph(N);
    REP(i, M) {
        cin >> j >> k;
        graph.add_undirected_edge(j - 1, k - 1);
    }
    vector<bool> huge(N, false);
    vector<vector<ll>> huge_conn(N);
    REP(i, N) {
        if (graph.conn.size() > thresh) {
            huge[i] = true;
        }
    }
    REP(i, N) {
        for (const auto v : graph.conn[i]) {
            if (huge[v]) {
                huge_conn[i].push_back(v);
            }
        }
    }

    query.resize(Q);
    REP(i, Q) { 
        cin >> query[i];
        query[i]--;
    }

    vector<ll> tmp;
    REP(i, N) tmp.push_back(i);

    vector<ll> up_time(N, -1);
    REP(i, Q) {
        ll p = query[i];
        if (huge[p]) {
            for (auto v: huge_conn[p]) {
                tmp[v] = tmp[p];
            }
        } else {
            // 更新
            pair<ll, ll> time_num = {up_time[p], tmp[p]};
            for (auto v: graph.conn[p]) {
                if (time_num.first < up_time[v]) {
                    time_num = {up_time[v], tmp[v]};
                }
            }
            up_time[p] = i;
            for (auto v: huge_conn[p]) {
                if (time_num.first < up_time[v]) {
                    time_num = {up_time[v], tmp[v]};
                }
            }
        }
    }
}