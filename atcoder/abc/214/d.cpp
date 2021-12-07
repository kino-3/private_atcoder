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

void debug_print() { cout << endl; }
template <class Head, class... Tail>
void debug_print(Head &&head, Tail &&...tail) {
    std::cout << head << ", ";
    debug_print(std::forward<Tail>(tail)...);
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
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

const ll mod = 998244353;
ll N, i, j, k, l;
vector<pair<ll, pair<ll, ll>>> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N - 1) {
        cin >> j >> k >> l;
        A.push_back({l, {j - 1, k - 1}});
    }
    sort(ALL(A));

    ll ans = 0;
    UnionFind uf = UnionFind(N);
    for (auto v : A) {
        ll x = v.second.first;
        ll y = v.second.second;
        ans += v.first * uf.size(x) * uf.size(y);
        // debug_print(x, y, ans);
        uf.unite(x, y);
    }
    cout << ans << endl;
}