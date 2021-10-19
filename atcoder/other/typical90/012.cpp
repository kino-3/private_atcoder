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

class Grid {
    // H=3, W=4 のとき
    // 0, 1, 2, 3
    // 4, 5, 6, 7
    // 8, 9, 10, 11
    ll H, W;
    vector<vector<bool>> checked;
    UnionFind uf;

   public:
    Grid(ll H, ll W)
        : H(H), W(W), checked(H, vector<bool>(W, false)), uf(H * W) {}

    void check(ll h, ll w) {
        checked[h - 1][w - 1] = true;
        ll pos = (h - 1) * W + w - 1;
        // cout << h << ";" << w << ";" << pos << endl;
        if (h != 1 && checked[h - 2][w - 1]) {
            uf.unite(pos, pos - W);
        }
        if (h != H && checked[h][w - 1]) {
            uf.unite(pos, pos + W);
        }
        if (w != 1 && checked[h - 1][w - 2]) {
            uf.unite(pos, pos - 1);
        }
        if (w != W && checked[h - 1][w]) {
            uf.unite(pos, pos + 1);
        }
    }

    bool detect(ll h1, ll w1, ll h2, ll w2) {
        if (checked[h1 - 1][w1 - 1] && checked[h2 - 1][w2 - 1]) {
            ll pos1 = (h1 - 1) * W + w1 - 1;
            ll pos2 = (h2 - 1) * W + w2 - 1;
            return uf.find(pos1, pos2);
        }
        return false;
    }
};

ll H, W, Q, i, j, ra, ca, rb, cb;
vector<vector<ll>> query;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W >> Q;
    REP(i, Q) {
        cin >> j;
        if (j == 1) {
            cin >> ra >> ca;
            query.push_back({1, ra, ca});
        } else {
            cin >> ra >> ca >> rb >> cb;
            query.push_back({2, ra, ca, rb, cb});
        }
    }
    Grid grid = Grid(H, W);
    REP(i, Q) {
        if (query[i][0] == 1) {
            grid.check(query[i][1], query[i][2]);
        } else {
            if (grid.detect(query[i][1], query[i][2], query[i][3],
                            query[i][4])) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
}