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

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

ll threshold = 500;
ll N, M, Q, i, j, k, l;
vector<ll> X, Y;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    Graph graph = Graph(N);
    // 解説参照
    vector<ll> query_color(N, 1);  // node がクエリで指定された色
    vector<ll> query_time(N, -1);  // node がクエリで指定された時刻
    vector<bool> is_main(N, false);  // 多くの edge を持つ node か
    vector<ll> main_color(N, 1);  // (is_main に限り保証される)現在の色
    vector<vector<ll>> conn_main(N, vector<ll>(0));  // 隣接する is_main
    REP(i, M) {
        cin >> j >> k;
        graph.add_undirected_edge(j - 1, k - 1);
    }
    REP(i, N) {
        if (graph.conn[i].size() > threshold) is_main[i] = true;
    }
    REP(i, N) {
        for (const auto v : graph.conn[i]) {
            if (is_main[v]) conn_main[i].push_back(v);
        }
    }
    cin >> Q;
    REP(i, Q) {
        cin >> j >> k;
        X.push_back(j - 1);
        Y.push_back(k);
    }
    REP(i, Q) {
        ll node = X[i];
        ll next_color = Y[i];
        if (is_main[node]) {
            cout << main_color[node] << endl;
            main_color[node] = next_color;
        } else {
            ll latest = query_time[node];
            ll latest_color = query_color[node];
            for (const auto v : graph.conn[node]) {
                if (latest < query_time[v]) {
                    latest = query_time[v];
                    latest_color = query_color[v];
                }
            }
            cout << latest_color << endl;
        }
        query_time[node] = i;
        query_color[node] = next_color;
        for (const auto v : conn_main[node]) {
            main_color[v] = next_color;
        }
    }
}