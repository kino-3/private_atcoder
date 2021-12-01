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

const ll mod = 998244353;
ll N, M, i, j, k, l;
vector<vector<bool>> good;

map<pair<ll, ll>, ll> seq;
map<pair<ll, ll>, ll> nck;

// ax + by = gcd(a,b) を満たす解を x, y に代入し, gcd(a, b) を返す
ll extgcd(ll a, ll b, ll &x, ll &y) {
    int d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1;
        y = 0;
    }
    return d;
}

// mod を法とする a の逆元
ll mod_inverse(ll a, ll mod) {
    ll x, y;
    ll gcd = extgcd(a, mod, x, y);
    if (gcd == 1)
        return (mod + x) % mod;
    else
        return -1;
}

class Combination {
    ll mod;
    vector<ll> factorial;

   public:
    // n は n_C_k の n の最大値
    Combination(ll n, ll _mod = 998244353) {
        mod = _mod;
        factorial.push_back(1);
        factorial.push_back(1);
        for (ll i = 2; i <= n; i++) {
            factorial.push_back(factorial[i - 1] * i % mod);
        }
    }

    // n_C_k を返す
    ll comb(ll n, ll k) {
        ll res = factorial[n] * mod_inverse(factorial[k], mod) % mod;
        return res * mod_inverse(factorial[n - k], mod) % mod;
    }
};

auto comb = Combination(500);

ll find_seq(ll l, ll r) {
    if (l == r) return 1;
    if ((r - l) % 2 > 0) return 0;
    if (seq.count({l, r}) > 0) return seq[{l, r}];
    if (r - l == 2) {
        return (good[l][l + 1] ? 1 : 0);
    }
    ll res = 0;
    ll idx;
    FOR(idx, l + 1, r) {
        if ((idx - l) % 2 == 0) continue;
        ll n = (r - l) / 2;
        ll k = (idx - l + 1) / 2;
        if (good[l][idx]) {
            if (nck.count({n, k}) == 0) {
                nck[{n, k}] = comb.comb(n, k);
            }
            ll tmp = find_seq(l + 1, idx) * find_seq(idx + 1, r);
            tmp %= mod;
            res += tmp * nck[{n, k}];
            res %= mod;
        }
    }
    seq[{l, r}] = res;
    // debug_print(l, r, res);
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    good.resize(N * 2, vector<bool>(N * 2, false));
    REP(i, M) {
        cin >> j >> k;
        good[j - 1][k - 1] = true;
        good[k - 1][j - 1] = true;
    }
    cout << find_seq(0, N * 2) << endl;
}