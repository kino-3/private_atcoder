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
    std::vector<ll> data;

    UnionFind(ll size) : data(size, -1) {}

    // 集合を併合する
    // 併合できたかを返す(すでに同じ木に属するなら併合不要なのでfalse)
    bool unite(ll x, ll y) {
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
    bool find(ll x, ll y) { return root(x) == root(y); }

    // 属する木の根を返す
    // (その過程で根まで辿ったノードを根に付ける)
    ll root(ll x) { return (data[x] < 0) ? x : data[x] = root(data[x]); }

    // 集合の要素数を返す
    ll size(ll x) { return -data[root(x)]; }
};

class UnionFind2D {
   public:
    ll R;
    ll C;
    UnionFind uf;

    UnionFind2D(ll row, ll column) : R(row), C(column), uf(R * C) {}

    ll convert_2d_to_1d(pair<ll, ll> x) { return x.first * C + x.second; }

    pair<ll, ll> convert_1d_to_2d(ll x) { return {x / C, x % C}; }

    // 集合を併合する
    // 併合できたかを返す(すでに同じ木に属するなら併合不要なのでfalse)
    bool unite(pair<ll, ll> x, pair<ll, ll> y) {
        return uf.unite(convert_2d_to_1d(x), convert_2d_to_1d(y));
    }

    // 同じ木に属するか
    bool find(pair<ll, ll> x, pair<ll, ll> y) {
        return uf.find(convert_2d_to_1d(x), convert_2d_to_1d(y));
    }

    // 属する木の根を返す
    // (その過程で根まで辿ったノードを根に付ける)
    pair<ll, ll> root(pair<ll, ll> x) {
        return convert_1d_to_2d(uf.root(convert_2d_to_1d(x)));
    }

    // 集合の要素数を返す
    ll size(pair<ll, ll> x) { return uf.size(convert_2d_to_1d(x)); }
};

const ll mod = 998244353;
ll N, M, i, j, k, l;
vector<vector<ll>> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // N 行 M 列の行列の受け取り
    cin >> N >> M;
    A.resize(N);
    REP(i, N) {
        REP(j, M) {
            cin >> k;
            A[i].push_back(k);
        }
    }

    UnionFind2D uf = UnionFind2D(N, M);
}