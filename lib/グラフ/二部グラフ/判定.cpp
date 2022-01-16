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

// 森の二部グラフ判定と構成
class Graph {
   public:
    ll V;                      // 頂点の個数
    vector<vector<ll>> graph;  // 隣接リスト
    // 各要素が 1 つの連結成分に対応
    // result[0].first は最初の連結成分の二部グラフの一方に属する頂点集合
    // second は空集合のことがありうる (独立した頂点の場合)
    vector<pair<vector<ll>, vector<ll>>> result;

    Graph(ll v) : V(v), graph(v) {}

    void add_edge(ll n1, ll n2) {
        assert(n1 != n2);
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // 全ての連結成分が二部グラフか
    // true のとき適切な結果が result に格納される
    bool exec() {
        // 0: 未到達
        // 1: res.first の要素
        // -1: res.second の要素
        vector<ll> checked = vector<ll>(V, 0);
        ll tmp = -1;  // 連結成分の始点
        while (tmp < V - 1) {
            tmp++;
            if (checked[tmp] != 0) continue;
            pair<vector<ll>, vector<ll>> res;
            queue<ll> que;  // bfs
            que.push(tmp);
            res.first.push_back(tmp);
            checked[tmp] = 1;
            while (!que.empty()) {
                ll cnt = que.front();
                que.pop();
                for (auto v : graph[cnt]) {
                    if (checked[v] != 0) {
                        // 周囲の色を検証する
                        if (checked[v] * checked[cnt] == 1) {
                            return false;
                        }
                    } else {
                        // 色を確定する
                        if (checked[cnt] == 1) {
                            res.second.push_back(v);
                            checked[v] = -1;
                            que.push(v);
                        } else {
                            res.first.push_back(v);
                            checked[v] = 1;
                            que.push(v);
                        }
                    }
                }
            }
            result.push_back(res);
        }
        return true;
    }
};

// input
// N
// a_1   b_1
// a_2   b_2
//  :
// a_N-1 a_N-1

ll N, M, i, j, k;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    Graph graph = Graph(N);
    REP(i, M) {
        cin >> j >> k;
        graph.add_edge(j - 1, k - 1);
    }
    graph.exec();

    for (auto v : graph.result) {
        for (auto vv : v.first) cout << vv;
        cout << ";";
        for (auto vv : v.second) cout << vv;
        cout << endl;
    }
}