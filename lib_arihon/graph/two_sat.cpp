#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class StronglyConnectedComponents {
    int V;  // 頂点の個数
    vector<vector<ll>> graph;
    vector<vector<ll>> rev_graph;  // 逆辺
    vector<set<ll>> scc;  // 結果を(execの戻り値とは別形式で)保存するだけ

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
        scc[current_order].insert(v);
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
                scc.push_back({});
                rev_dfs(nodes[i], current_order, used, res);
                current_order++;
            }
        }
        return res;
    }

    vector<set<ll>> get_scc() { return scc; }
};

class TwoSAT {
    int V;                            // 頂点の個数
    StronglyConnectedComponents scc;  // 0~v-1 は true, v~2v-1 は false のノード
    vector<bool> solution;            // 存在する場合の解

   public:
    TwoSAT(int v) : V(v), scc(2 * v), solution(v) {}

    // 制約 a => b を加える
    void add_a_b(int a, int b) { scc.add_edge(a, b); }

    // 制約 ￢a => b を加える
    void add_na_b(int a, int b) { scc.add_edge(a + V, b); }

    // 制約 a => ￢b を加える
    void add_a_nb(int a, int b) { scc.add_edge(a, b + V); }

    // 制約 ￢a => ￢b を加える
    void add_na_nb(int a, int b) { scc.add_edge(a + V, b + V); }

    // 制約 a or b を加える
    void add_a_or_b(int a, int b) {
        add_na_b(a, b);
        add_na_b(b, a);
    }

    // 制約 a xor b を加える
    void add_a_xor_b(int a, int b) {
        add_a_nb(a, b);
        add_a_nb(b, a);
    }

    // 制約 a を加える
    void add_a(int a) {
        // ￢A=>A は ￢￢AorA すなわち A と同値
        add_na_b(a, a);
    }

    // 制約 not a を加える
    void add_na(int a) { add_a_nb(a, a); }

    // 充足可能か
    bool exec() {
        scc.exec();
        auto components = scc.get_scc();
        vector<bool> determined(V, false);
        fill(solution.begin(), solution.end(), false);
        for (const auto& component : components) {
            for (const auto& node : component) {
                if (node < V) {
                    if (component.count(node + V) > 0) {
                        // true と false が同じ強連結成分
                        return false;
                    }
                    if (!determined[node]) {
                        determined[node] = true;
                        solution[node] = false;
                    }
                } else {
                    if (!determined[node - V]) {
                        determined[node - V] = true;
                        solution[node - V] = true;
                    }
                }
            }
        }
        return true;
    }

    vector<bool> get_solution() { return solution; }
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
    TwoSAT twoSAT = TwoSAT(3);
    twoSAT.add_na_nb(0, 1);
    twoSAT.add_a_b(1, 0);
    twoSAT.add_a_or_b(1, 2);
    twoSAT.add_a_nb(2, 0);
    twoSAT.add_a_nb(0, 2);
    cout << twoSAT.exec() << endl;
    print_v(twoSAT.get_solution());
}