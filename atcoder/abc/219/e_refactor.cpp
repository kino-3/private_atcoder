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
void debug_print(const T item) {
    cout << item << endl;
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 100);
}
template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto &&item : vec) {
        print_v(item);
    }
}
template <typename K, typename V>
void print_map(const map<K, V> dict) {
    for (const auto v : dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v : data) {
        cout << v << ", ";
    }
    cout << endl;
}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {
    cout << "(" << data.first << "," << data.second << ")";
    // cout << endl;
}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {
    cout << "(";
    cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
    cout << ")";
    // cout << endl;
}

const ll mod = 998244353;
ll N, M, i, j, k, l;
string S;
vector<vector<bool>> A;

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

template <typename T>
vector<vector<T>> expand(vector<vector<T>> field) {
    T fill_value = false;  // TODO
    ll R = field.size();
    ll C = field[0].size();
    vector<vector<T>> res(R + 2, vector<T>(C + 2, fill_value));
    for (ll i = 0; i < field.size(); i++) {
        copy(field[i].begin(), field[i].end(), res[i + 1].begin() + 1);
    }
    return res;
}

bool check(vector<vector<bool>> A, vector<vector<bool>> B) {
    ll count = 0;
    REP(j, 4) {
        REP(k, 4) {
            if (A[j][k] && !B[j + 1][k + 1]) return false;
            if (B[j + 1][k + 1]) count++;
        }
    }
    UnionFind2D uf = UnionFind2D(6, 6);
    REP(j, 6) {
        REP(k, 5) {
            if (B[j][k] == B[j][k + 1]) uf.unite({j, k}, {j, k + 1});
            if (B[k][j] == B[k + 1][j]) uf.unite({k, j}, {k + 1, j});
        }
    }
    if (uf.size({0, 0}) != 36 - count) return false;
    REP(j, 4) {
        REP(k, 4) {
            if (B[j + 1][k + 1]) {
                if (uf.size({j + 1, k + 1}) == count) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    assert(false);
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    N = M = 4;
    A.resize(N);
    REP(i, N) {
        REP(j, M) {
            cin >> k;
            A[i].push_back(k == 1);
        }
    }

    ll ans = 0;
    REP(i, 1LL << 16) {
        // i = 0...2^N-1 (N 桁の辞書順)
        std::bitset<100> bs(i);
        // 上位桁からループ
        vector<vector<bool>> B(4, vector<bool>(4));
        REP_R(j, 16) { B[j / 4][j % 4] = bool(bs[j]); }
        B = expand(B);
        if (check(A, B)) ans++;
    }
    cout << ans << endl;
}