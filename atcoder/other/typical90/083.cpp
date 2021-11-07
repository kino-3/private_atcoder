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

ll mod = 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> X, Y;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    Graph graph = Graph(N);
    vector<ll> color(N, 1);
    REP(i, M) {
        cin >> j >> k;
        graph.add_undirected_edge(j - 1, k - 1);
    }
    cin >> Q;
    REP(i, Q) {
        cin >> j >> k;
        X.push_back(j - 1);
        Y.push_back(k);
    }
    REP(i, Q) {
        // print_v(color);
        cout << color[X[i]] << endl;
        color[X[i]] = Y[i];
        for (const auto v : graph.conn[X[i]]) {
            color[v] = Y[i];
        }
    }
}