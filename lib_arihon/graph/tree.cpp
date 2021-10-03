#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Tree {
    ll V;                      // 頂点の個数
    vector<vector<ll>> graph;  // 隣接リスト

   public:
    vector<ll> parent;        // 頂点の親ノード
    vector<ll> subtree_size;  // subtree_size
    vector<ll> centroids;     // 木の重心

    Tree(ll v) : V(v), graph(v), parent(v, -1), subtree_size(v, -1) {}

    void add_edge(ll n1, ll n2) {
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    // v の部分木(vを含む)のサイズ
    // 計算量 O(V)
    // (parent, subtree_size も更新する)
    // すなわち, (vと隣接する) parent_of_v を取り除いたときの
    // v を含む木の頂点数
    // 外部から呼び出すときは calc_subtree_size(root) とすること
    ll calc_subtree_size(ll v, ll parent_of_v = -1) {
        parent[v] = parent_of_v;
        ll size = 1;
        for (const auto& child : graph[v]) {
            if (child == parent_of_v) continue;  // 隣接リストなので
            size += calc_subtree_size(child, v);
        }
        subtree_size[size];
        return size;
    }

    // calc_subtree_size + 重心分解
    // 計算量 O(V)
    // (parent, subtree_size, centroids も更新する)
    // 外部から呼び出すときは find_centroid(root) とすること
    void find_centroid(ll v, ll parent_of_v = -1) {
        if (parent_of_v == -1) {  // 外部呼出し時に初期化
            centroids.clear();
            fill(subtree_size.begin(), subtree_size.end(), 1);
        }
        parent[v] = parent_of_v;
        bool is_centroid = true;
        for (const auto& child : graph[v]) {
            if (child == parent_of_v) continue;
            find_centroid(child, v);
            if (subtree_size[child] > V / 2) is_centroid = false;
            subtree_size[v] += subtree_size[child];
        }
        if (subtree_size[v] < V / 2) {
            // v を親としたときの parent_of_v のサイズが V / 2 より大きい
            is_centroid = false;
        }
        if (is_centroid) centroids.push_back(v);
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
    Tree tree = Tree(8);
    tree.add_edge(0, 1);
    tree.add_edge(0, 2);
    tree.add_edge(1, 3);
    tree.add_edge(1, 4);
    tree.add_edge(2, 5);
    tree.add_edge(4, 6);
    tree.add_edge(4, 7);
    tree.find_centroid(0);
    print_v(tree.centroids);
    print_v(tree.parent);
    print_v(tree.subtree_size);
}