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

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

class BIT {
    ll n;             // 要素数
    vector<ll> node;  // node[0] (=0) は使用しない

   public:
    BIT(ll n) : n(n), node(n + 1, 0) {}  // 配列は 0 で初期化する

    ll sum(ll index) {
        // [1,index] の index 個の和
        index++;
        ll res = 0;
        while (index > 0) {
            res += node[index];
            // i  = ****1000 のとき
            // -i = ####1000 なので (####は****のビット反転)
            // (これは,-iが####0111に1を加えたものであるため)
            // i&-i = 00001000 となる(iの一番下の1だけとりだしたもの)
            index -= index & (-index);  // 一番下の1を0に変える
        }
        return res;
    }

    ll sum(ll left, ll right) {
        // [left, right] の 和
        return sum(right) - sum(left - 1);
    }

    void add(ll index, ll value) {
        index++;
        // index 番目に value を加える
        while (index <= n) {
            node[index] += value;
            index += index & (-index);
        }
    }
};

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

ll N, Q, i, j, k, l, m;
vector<ll> T, X, Y, V;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    cin >> Q;
    REP(i, Q) {
        cin >> j >> k >> l >> m;
        T.push_back(j);
        X.push_back(k - 1);
        Y.push_back(l - 1);
        V.push_back(m);
    }

    BIT bit = BIT(N - 1);
    UnionFind uf = UnionFind(N);

    REP(i, Q) {
        ll x = X[i];
        ll y = Y[i];
        ll v = V[i];
        if (T[i] == 0) {
            if (x % 2 == 0) {
                bit.add(x, v - bit.sum(x, x));
            } else {
                bit.add(x, -v - bit.sum(x, x));
            }
            uf.unite(x, x + 1);
        } else {
            if (uf.find(x, y)) {
                ll ans = v;
                if (x % 2 == 0) {
                    ans -= bit.sum(x, y - 1);
                } else {
                    ans += bit.sum(x, y - 1);
                }
                if ((y - x) % 2 == 0) {
                    cout << ans << endl;
                } else {
                    cout << -ans << endl;
                }
            } else {
                cout << "Ambiguous" << endl;
            }
        }
    }
}