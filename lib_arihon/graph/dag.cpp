#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class DAG {
    int V;  // 頂点の個数
    vector<vector<ll>> edges;
    void _topological_sort_dfs(ll v, vector<bool>& used, vector<ll>& res) {
        used[v] = true;
        for (const auto& to : edges[v]) {
            if (!used[to]) {
                _topological_sort_dfs(to, used, res);
            }
        }
        res.push_back(v);  // 帰りがけ順
    }

   public:
    DAG(int v) : V(v), edges(v) {}

    void add_edge(ll from, ll to) { edges[from].push_back(to); }

    // O(V + E)
    vector<ll> topological_sort_bfs() {
        vector<ll> res;
        vector<ll> indegree(V, 0);
        for (const auto& edge : edges) {
            for (const auto& to : edge) {
                indegree[to]++;
            }
        }
        queue<ll> que;  // 入次数 0 の頂点を入れる
        for (ll v = 0; v < V; v++) {
            if (indegree[v] == 0) {
                que.push(v);
            }
        }
        while (!que.empty()) {
            ll node = que.front();
            que.pop();
            res.push_back(node);
            for (const auto& to : edges[node]) {
                indegree[to]--;
                if (indegree[to] == 0) {
                    que.push(to);
                }
            }
        }
        return res;
    }

    vector<ll> topological_sort_dfs() {
        vector<ll> res;
        vector<bool> used(V, false);
        for (ll v = 0; v < V; v++) {
            if (!used[v]) _topological_sort_dfs(v, used, res);
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

int main() {
    DAG dag = DAG(7);
    dag.add_edge(0, 6);
    dag.add_edge(0, 4);
    dag.add_edge(1, 0);
    dag.add_edge(1, 2);
    dag.add_edge(2, 4);
    dag.add_edge(3, 1);
    dag.add_edge(3, 5);
    dag.add_edge(5, 1);
    print_v(dag.topological_sort_bfs());
    print_v(dag.topological_sort_dfs());
}