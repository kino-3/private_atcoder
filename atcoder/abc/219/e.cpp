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

bool check(vector<vector<bool>> A, vector<vector<bool>> B) {
    ll count = 0;
    REP(j, 4) {
        REP(k, 4) {
            if (A[j][k] && !B[j + 1][k + 1]) return false;
            if (B[j + 1][k + 1]) count++;
        }
    }
    UnionFind uf = UnionFind(36);
    REP(j, 6) {
        REP(k, 5) {
            if (B[j][k] == B[j][k + 1]) uf.unite(6 * j + k, 6 * j + k + 1);
            if (B[k][j] == B[k + 1][j]) uf.unite(6 * k + j, 6 * k + j + 6);
        }
    }
    if (uf.size(0) != 36 - count) return false;
    REP(j, 4) {
        REP(k, 4) {
            if (B[j + 1][k + 1]) {
                if (uf.size(6 * j + k + 7) == count) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    assert(false);
}

ll N = 16;
ll i, j, k;
vector<vector<bool>> A(4, vector<bool>(4));
vector<vector<bool>> B(6, vector<bool>(6));

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    REP(i, 4) {
        REP(j, 4) {
            cin >> k;
            A[i][j] = (k == 1);
        }
    }

    ll ans = 0;
    REP(i, 1 << N) {
        REP(j, 6) {
            REP(k, 6) { B[j][k] = false; }
        }
        // i = 0...2^N-1 (N 桁の辞書順)
        std::bitset<100> bs(i);
        // 上位桁からループ
        REP_R(j, N) { B[j / 4 + 1][j % 4 + 1] = bool(bs[j]); }
        if (check(A, B)) ans++;
    }
    cout << ans << endl;
}