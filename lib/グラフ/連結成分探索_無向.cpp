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

class Graph {
   public:
    ll V;                      // 頂点の個数
    vector<vector<ll>> graph;  // 隣接リスト
    vector<ll> visited;
    map<ll, vector<ll>> connected;  // root -> (root を含む連結成分の頂点一覧)
    map<ll, ll> count_node;  // root -> (root を含む連結成分の node の個数)
    map<ll, ll> count_edge;  // root -> (root を含む連結成分の edge の個数)
    vector<ll> root;

    Graph(ll v) : V(v), graph(v, vector<ll>(0)), visited(v, false), root(v) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    void exec() {
        for (ll i = 0; i < V; i++) {
            if (!visited[i]) {
                vector<ll> res;
                stack<ll> tmp;
                visited[i] = true;
                tmp.push(i);
                res.push_back(i);
                root[i] = i;
                count_edge[i] = graph[i].size();
                while (!tmp.empty()) {
                    ll node = tmp.top();
                    tmp.pop();
                    for (const auto v : graph[node]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            tmp.push(v);
                            res.push_back(v);
                            root[v] = i;
                            count_edge[i] += graph[v].size();
                        }
                    }
                }
                connected[i] = res;
                count_edge[i] /= 2;
                count_node[i] = res.size();
            }
        }
    }
};

ll mod = 1000000007;
ll N, M, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;  // 頂点の数, 辺の数
    Graph graph = Graph(N);
    REP(i, M) {
        cin >> j >> k;
        graph.add_edge(j - 1, k - 1);
    }
    graph.exec();
    for (auto it = graph.connected.begin(), e = graph.connected.end(); it != e;
         ++it) {
        ll root = it->first;
        cout << graph.count_node[root] << " " << graph.count_node[root] << endl;
    }
}