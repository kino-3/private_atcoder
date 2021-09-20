#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct edge {
    ll to;
    ll capacity;
    ll cost;
    ll rev;  // graph[to][rev] が逆辺を表す
};

class MinCostFlow {
    ll V;  // 頂点の個数
    vector<vector<edge>> graph;
    vector<ll> dist;       // dist[v]: v までの最短距離
    vector<ll> prev_edge;  // 最短経路における直前の edge
    vector<ll> prev_node;  // 最短経路における直前の node
    const ll INF = numeric_limits<ll>::max();

   public:
    MinCostFlow(int v) : V(v), graph(v), dist(v), prev_edge(v), prev_node(v) {}

    void add_edge(ll from, ll to, ll capacity, ll cost) {
        graph[from].push_back({to, capacity, cost, graph[to].size()});
        graph[to].push_back({from, 0, -cost, graph[from].size() - 1});
    }

    // source から sink に flow を流すときの最小費用を返す
    ll exec(ll source, ll sink, ll flow) {
        ll total_cost = 0;
        while (flow > 0) {
            // ベルマンフォード法で残余グラフから最短距離を求める
            fill(dist.begin(), dist.end(), INF);
            dist[source] = 0;
            bool updated = true;
            while (updated) {
                updated = false;
                for (ll v = 0; v < V; v++) {
                    if (dist[v] == INF) {
                        continue;
                    }
                    for (ll i = 0; i < graph[v].size(); i++) {
                        edge& e = graph[v][i];
                        if (e.capacity > 0 && dist[e.to] > dist[v] + e.cost) {
                            dist[e.to] = dist[v] + e.cost;
                            prev_node[e.to] = v;
                            prev_edge[e.to] = i;
                            updated = true;
                        }
                    }
                }
            }

            if (dist[sink] == INF) {
                return -1;  // flow を流すことは出来ない
            }

            // 最短距離に目一杯流す
            ll actual_flow = flow;
            for (ll v = sink; v != source; v = prev_node[v]) {  // 逆向きに辿る
                actual_flow = min(actual_flow,
                                  graph[prev_node[v]][prev_edge[v]].capacity);
            }
            flow -= actual_flow;  // 残り流さないといけない流量
            total_cost += actual_flow * dist[sink];

            // 残余グラフの更新
            for (ll v = sink; v != source; v = prev_node[v]) {  // 逆向きに辿る
                edge& e = graph[prev_node[v]][prev_edge[v]];
                e.capacity -= actual_flow;
                graph[v][e.rev].capacity += actual_flow;
            }
        }
        return total_cost;
    }
};

int main() {
    MinCostFlow min_cost_flow = MinCostFlow(5);
    min_cost_flow.add_edge(0, 1, 10, 2);
    min_cost_flow.add_edge(0, 2, 2, 4);
    min_cost_flow.add_edge(1, 2, 6, 6);
    min_cost_flow.add_edge(1, 3, 6, 2);
    min_cost_flow.add_edge(2, 4, 5, 2);
    min_cost_flow.add_edge(3, 2, 3, 3);
    min_cost_flow.add_edge(3, 4, 8, 6);
    cout << min_cost_flow.exec(0, 4, 9) << endl;
    cout << min_cost_flow.exec(0, 4, 12) << endl;
}