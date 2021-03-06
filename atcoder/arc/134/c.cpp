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

#ifdef _DEBUG
void debug_print() {
    cout << endl;
}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {
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
    for (const auto v: dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v: data) {
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
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
}
#else
void debug_print() {}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {}
void debug_print_count() {}
template <typename T>
void print_v(const vector<T> vec) {}
template <typename T>
void print_vv(const vector<T> vec) {}
template <typename K, typename V>
void print_map(const map<K, V> dict) {}
template <typename T>
void print_set(const set<T> data) {}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {}
#endif

const ll mod = 998244353;  // 1000000007;
ll N, K, Q, i, j, k, l;
vector<ll> A, B;

// ax + by = gcd(a,b) ?????????????????? x, y ????????????, gcd(a, b) ?????????
ll extgcd(ll a, ll b, ll& x, ll& y) {
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

// mod ??????????????? a ?????????
ll mod_inverse(ll a, ll mod) {
    ll x, y;
    ll gcd = extgcd(a, mod, x, y);
    if (gcd == 1)
        return (mod + x) % mod;
    else
        return -1;
}

// ?????? mod ??????????????? i ????????? res[i] (i<=n)
// ????????? O(n)
vector<ll> mod_inverse_list(ll n, ll mod) {
    vector<ll> res(n + 1);
    res[0] = 0;
    res[1] = 1;
    for (ll i = 2; i <= n; i++) {
        // mod = i*(mod/i) + mod%i
        // 0 ??? i*(mod/i) + mod%i
        // i*(mod/i) ??? -mod%i
        // mod%i < i ??????, res[mod%i] ????????????,
        // i*(mod/i)*res[mod%i] ??? -1
        // (-1)*(-1) ??? 1 ??????
        // i*(mod/i)*res[mod%i]*(-1) ??? 1
        // ?????????,
        // res[i] ??? (mod/i)*res[mod%i]*(-1)
        // (mod/i)*res[mod%i] > 0 ?????????,
        res[i] = mod - ((mod / i) * res[mod % i]) % mod;
    }
    return res;
}

// x^n % mod ?????????
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

// ???????????????
// ????????????: https://atcoder.jp/contests/typical90/tasks/typical90_o
class Combination {
    ll mod;
    vector<ll> factorial;

   public:
    // n ??? n_C_k ??? n ????????????
    Combination(ll _mod = 998244353) {
        mod = _mod;
        factorial.push_back(1);
        factorial.push_back(1);
        for (ll i = 2; i <= 210; i++) {
            factorial.push_back(factorial[i - 1] * i % mod);
        }
    }

    // n_C_k ?????????
    ll comb(ll n, ll k) {
        assert(k >= 0);
        assert(n - k >= 0);
        ll res = 1;
        REP(i, k) {
            res *= (n - i);
            res %= mod;
        }
        return res * mod_inverse(factorial[k], mod) % mod;
    }
};

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    A.resize(N);
    REP(i, N) {
        cin >> A[i];
    }
    ll sum = 0;
    FOR(i, 1, N) {
        sum += A[i];
    }
    A[0] -= sum;
    A[0] -= K;
    // print_v(A);

    if (A[0] < 0) {
        cout << 0 << endl;
        return 0;
    }

    // A[i]+K-1 C K-1 ??????
    ll ans = 1;
    Combination comb = Combination();
    for (auto v: A) {
        ans *= comb.comb(v + K - 1, K - 1);
        ans %= mod;
    }
    cout << ans << endl;
}