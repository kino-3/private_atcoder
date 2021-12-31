#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct edge {
    ll to;
    ll capacity;
    ll rev;  // graph[to][rev] が逆辺を表す
};

class FordFulkerson {
    // graph[i] の要素 e は, i から e.to へあと e.capacity
    // だけ流せるという情報をもつ。
    // また, graph[e.to][e.rev] は e の逆辺である。
    vector<vector<edge>> graph;
    const ll INF = numeric_limits<ll>::max();
    vector<bool> used;  // DFS で既に経由済みかを記録する
    ll source;          // 流入口
    ll sink;            // 流出口

   public:
    FordFulkerson(ll v) : graph(v), used(v), source(0), sink(v - 1) {}

    void add_edge(ll from, ll to, ll capacity) {
        graph[from].push_back({to, capacity, graph[to].size()});
        graph[to].push_back({from, 0, graph[from].size() - 1});  // 逆辺
    }

    ll dfs(ll node, ll flow) {
        // node に flow だけ流し込もうとしたとき, 実際はどれだけ流れるか
        // 戻り値は flow 以下の値である
        if (node == sink) {
            return flow;
        }
        used[node] = true;
        for (auto&& edge : graph[node]) {
            if (!used[edge.to] && edge.capacity > 0) {
                ll actual_flow = dfs(edge.to, min(flow, edge.capacity));
                if (actual_flow > 0) {
                    edge.capacity -= actual_flow;
                    graph[edge.to][edge.rev].capacity += actual_flow;
                    return actual_flow;
                }
            }
        }
        return 0;  // sink に到達できなかった
    }

    ll exec(ll source_node, ll sink_node) {
        source = source_node;
        sink = sink_node;
        ll max_flow = 0;
        while (true) {
            std::fill(used.begin(), used.end(), false);
            ll flow = dfs(source, INF);
            if (flow == 0) {
                return max_flow;
            }
            max_flow += flow;
        }
        return max_flow;
    }
};

int main() {
    FordFulkerson max_flow = FordFulkerson(5);
    max_flow.add_edge(0, 1, 10);
    max_flow.add_edge(0, 2, 2);
    max_flow.add_edge(1, 2, 6);
    max_flow.add_edge(1, 3, 6);
    max_flow.add_edge(2, 4, 5);
    max_flow.add_edge(3, 2, 3);
    max_flow.add_edge(3, 4, 8);
    cout << max_flow.exec(0, 4) << endl;
}