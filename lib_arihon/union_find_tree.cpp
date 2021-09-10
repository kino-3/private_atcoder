#include <bits/stdc++.h>
using namespace std;

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

int main() {
    UnionFind uf = UnionFind(4);
    cout << uf.unite(0, 1) << endl;
    cout << uf.unite(0, 1) << endl;
    cout << uf.size(0) << endl;
    cout << uf.find(0, 2) << endl;
    uf.unite(2, 3);
    uf.unite(0, 2);
    cout << uf.size(3) << endl;
}