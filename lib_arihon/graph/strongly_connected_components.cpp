#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class StronglyConnectedComponents {
    int V;  // 頂点の個数
    vector<vector<ll>> graph;
    vector<vector<ll>> rev_graph;  // 逆辺
    vector<vector<ll>> scc;  // 結果を(execの戻り値とは別形式で)保存するだけ

    void dfs(ll v, vector<bool>& used, vector<ll>& nodes) {
        used[v] = true;
        for (const auto& to : graph[v]) {
            if (!used[to]) {
                dfs(to, used, nodes);
            }
        }
        nodes.push_back(v);  // 帰りがけ順
    }

    void rev_dfs(ll v, ll current_order, vector<bool>& used, vector<ll>& res) {
        used[v] = true;
        res[v] = current_order;
        scc[current_order].push_back(v);
        for (const auto& to : rev_graph[v]) {
            if (!used[to]) {
                rev_dfs(to, current_order, used, res);
            }
        }
    }

   public:
    StronglyConnectedComponents(int v) : V(v), graph(v), rev_graph(v) {}

    void add_edge(ll from, ll to) {
        graph[from].push_back(to);
        rev_graph[to].push_back(from);
    }

    // O(V + E)
    vector<ll> exec() {
        vector<bool> used(V, false);
        vector<ll> nodes;
        for (ll v = 0; v < V; v++) {
            if (!used[v]) dfs(v, used, nodes);
        }
        fill(used.begin(), used.end(), false);
        ll current_order = 0;
        vector<ll> res(V);
        scc.clear();
        for (ll i = V - 1; i >= 0; i--) {
            if (!used[nodes[i]]) {
                scc.push_back(vector<ll>(0));
                rev_dfs(nodes[i], current_order, used, res);
                current_order++;
            }
        }
        return res;
    }

    vector<vector<ll>> get_scc() { return scc; }
};

template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

int main() {
    StronglyConnectedComponents scc = StronglyConnectedComponents(12);
    scc.add_edge(0, 6);
    scc.add_edge(6, 7);
    scc.add_edge(6, 1);
    scc.add_edge(1, 7);
    scc.add_edge(7, 2);
    scc.add_edge(2, 1);
    scc.add_edge(2, 8);
    scc.add_edge(8, 3);
    scc.add_edge(3, 9);
    scc.add_edge(9, 8);
    scc.add_edge(3, 4);
    scc.add_edge(3, 10);
    scc.add_edge(10, 4);
    scc.add_edge(10, 11);
    scc.add_edge(5, 4);
    scc.add_edge(4, 5);
    print_v(scc.exec());
    vector<vector<ll>> result = scc.get_scc();
    for (int i = 0; i < result.size(); i++) {
        print_v(result[i]);
    }
}