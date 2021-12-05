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

const ll mod = 998244353;
ll N, M, i, j, k, l;
string S, T;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> S;

    vector<map<char, ll>> dp(N); // dp[i][c]: 最後に i 番目にでて, c には出ない

    REP(i, N) {
        ll ans = 1;  // i 番目のみ
        REP(j, i) {
            if (S[i] == S[j]) {
                ans += dp[j];
                ans %= mod;
            }
        }
        dp[i] = ans;
    }

    ll ans = 0;
    REP(i, N) {
        ans += dp[i];
        ans %= mod;
    }
    cout << ans << endl;

    // vector<ll> dp(N);

    // REP(i, N) {
    //     ll ans = 1;  // i 番目のみ
    //     REP(j, i) {
    //         if (S[i] == S[j]) {
    //             ans += dp[j];
    //             ans %= mod;
    //         }
    //     }
    //     dp[i] = ans;
    // }

    // ll ans = 0;
    // REP(i, N) {
    //     ans += dp[i];
    //     ans %= mod;
    // }
    // cout << ans << endl;

    // map<char, vector<ll>> dict;
    // ll idx = 0;
    // REP(i, N) {
    //     if (S[i] != S[idx]) {
    //         dict[S[idx]].push_back(i - idx);
    //         idx = i;
    //     }
    // }
    // dict[S[idx]].push_back(N - idx);

    // ll ans = 1;
    // for (auto v : dict) {
    //     auto vec = v.second;
    //     ll tmp = 1;
    //     for (auto vv : vec) {
    //         tmp += (mod_pow(2, vv, mod) - 1);
    //         tmp %= mod;
    //     }
    //     debug_print(v.first, tmp);
    //     ans *= tmp;
    //     ans %= mod;
    // }
    // ans = (ans + mod - 1) % mod;
    // cout << ans << endl;
}