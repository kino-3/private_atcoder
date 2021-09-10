#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// copy from union_find_tree.cpp
class UnionFind {
   public:
    // 根ノードなら -(データ数)
    // それ以外なら親ノード
    // が格納される
    std::vector<int> data;

    UnionFind(int size) : data(size, -1) {}

    // 集合を併合する
    // 併合できたかを返す(すでに同じ木に属するなら併合不要なのでfalse)
    bool unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (data[y] < data[x]) std::swap(x, y);
            // 要素数の大きな方(x)へyを合併する
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }

    // 同じ木に属するか
    bool find(int x, int y) { return root(x) == root(y); }

    // 属する木の根を返す
    // (その過程で根まで辿ったノードを根に付ける)
    int root(int x) { return (data[x] < 0) ? x : data[x] = root(data[x]); }

    // 集合の要素数を返す
    int size(int x) { return -data[root(x)]; }
};

struct edge {
    int from;
    int to;
    ll cost;
};

// TODO: 動作未検証
// O(E logV)
class Kruskal {
    int V;  // 頂点の個数
    int E;  // 辺の個数
    vector<edge> edges;
    vector<pair<int, int>> links;

    const ll INF = numeric_limits<ll>::max();

   private:
    bool comp(const edge& e1, const edge& e2) { return e1.cost < e2.cost; }

   public:
    Kruskal(int v, int e) : V(v), E(e) {}

    void add_edge(int from, int to, ll cost) {
        edges.push_back({from, to, cost});
    }

    int exec() {
        int total_cost = 0;
        sort(edges.begin(), edges.end(), comp);  // コストの小さい順にソート
        UnionFind union_find = UnionFind(V);
        for (const auto& edge : edges) {
            if (!union_find.find(edge.from, edge.to)) {
                union_find.unite(edge.from, edge.to);
                total_cost += edge.cost;
                links.push_back({edge.from, edge.to});
            }
        }
        return total_cost;
    }
};

int main() {}