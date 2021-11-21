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

const ll mod = 998244353;
ll N, i, j, k, l;
vector<ll> A, B;

// 破壊的に座標圧縮する
// vec の要素の種類数を返す
ll compress(vector<ll> &vec) {
    map<ll, ll> memo;                      // key: 変換前, value: 変換後
    for (const auto v : vec) memo[v] = 0;  // key 登録
    ll size = 0;
    for (auto &p : memo) p.second = size++;  // value 設定
    for (auto &v : vec) v = memo[v];         // value 設定
    return size;
}

// 0-indexed
class BIT {
   public:
    ll n;                                // 要素数
    vector<ll> node;                     // node[0] (=0) は使用しない
    BIT(ll n) : n(n), node(n + 1, 0) {}  // 配列は 0 で初期化する

    // [0, index] の index + 1 個の和
    ll sum(ll index) {
        index++;
        ll res = 0;
        while (index > 0) {
            res += node[index];  // 加算
            res %= mod;
            index -= index & (-index);
        }
        return res;
    }

    // index 番目に value を加える
    void add(ll index, ll value) {
        index++;
        while (index <= n) {
            node[index] += value;  // 加算
            node[index] %= mod;
            index += index & (-index);
        }
    }
};

// x^n % mod を返す
ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    ll n = compress(A);  // 座標圧縮

    // Σ_i,j 2^(j-i-1) (when i<j and A[i]<=A[j])
    // = Σ_j(2^j * (Σ_i 2^(-i-1)))
    BIT bit_d = BIT(n);
    ll ans = 0;
    REP(j, N) {
        ll pair_sum = bit_d.sum(A[j]);
        bit_d.add(A[j], mod_pow(2, mod - 2 - j, mod));
        ans += mod_pow(2, j, mod) * pair_sum;
        ans %= mod;
    }
    cout << ans << endl;
}