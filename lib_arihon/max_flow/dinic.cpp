#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct edge {
    ll to;
    ll capacity;
    ll rev;  // graph[to][rev] が逆辺を表す
};

class Dinic {
    // graph[i] の要素 e は, i から e.to へあと e.capacity
    // だけ流せるという情報をもつ。
    // また, graph[e.to][e.rev] は e の逆辺である。
    vector<vector<edge>> graph;
    const ll INF = numeric_limits<ll>::max();
    vector<ll> level;
    vector<ll> iter;
    ll source;  // 流入口
    ll sink;    // 流出口

   public:
    Dinic(ll v) : graph(v), source(0), sink(v - 1), level(v, -1), iter(v, 0) {}

    void add_edge(ll from, ll to, ll capacity) {
        graph[from].push_back({to, capacity, graph[to].size()});
        graph[to].push_back({from, 0, graph[from].size() - 1});  // 逆辺
    }

    void bfs() {
        // level に以下の情報を格納する
        // level[v] は source から v までに経由する(最小)ノード数
        // (ただし, 正の capacity の辺 (及び逆辺)のみ通過できる)
        // 到達不可能な場合は -1 とする
        std::fill(level.begin(), level.end(), -1);
        queue<ll> que;
        level[source] = 0;
        que.push(source);
        while (!que.empty()) {
            ll node = que.front();
            que.pop();
            for (const auto& edge : graph[node]) {
                if (edge.capacity > 0 && level[edge.to] < 0) {
                    // edge.to はまだ探索していない到達可能ノード
                    level[edge.to] = level[node] + 1;
                    que.push(edge.to);
                }
            }
        }
    }

    ll dfs(ll node, ll flow) {
        // node に flow だけ流し込もうとしたとき, 実際はどれだけ流れるか
        // 戻り値は flow 以下の値である
        if (node == sink) {
            return flow;
        }
        for (ll& i = iter[node]; i < graph[node].size(); i++) {
            // 2 回目以降に dfs が呼び出されたときは, 続きから探索する
            // iter[node] は i++ で書き換わる
            edge& edge = graph[node][i];
            if (edge.capacity > 0 && level[node] < level[edge.to]) {
                ll actual_flow = dfs(edge.to, min(flow, edge.capacity));
                if (actual_flow > 0) {
                    edge.capacity -= actual_flow;
                    graph[edge.to][edge.rev].capacity += actual_flow;
                    return actual_flow;
                }
            }
        }
        return 0;
    }

    ll exec(ll source_node, ll sink_node) {
        source = source_node;
        sink = sink_node;
        ll max_flow = 0;
        while (true) {
            bfs();
            if (level[sink] < 0) {
                return max_flow;
            }
            std::fill(iter.begin(), iter.end(), 0);
            ll flow;
            while ((flow = dfs(source, INF)) > 0) {
                max_flow += flow;
            }
        }
        return max_flow;
    }
};

int main() {
    Dinic max_flow = Dinic(5);
    max_flow.add_edge(0, 1, 10);
    max_flow.add_edge(0, 2, 2);
    max_flow.add_edge(1, 2, 6);
    max_flow.add_edge(1, 3, 6);
    max_flow.add_edge(2, 4, 5);
    max_flow.add_edge(3, 2, 3);
    max_flow.add_edge(3, 4, 8);
    cout << max_flow.exec(0, 4) << endl;
}