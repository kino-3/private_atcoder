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
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
}

// 正の整数 n は素数か
// O(√n)
bool is_prime(ll n) {
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    if (n == 1) {
        return false;
    }
    return true;
}

const ll mod = 998244353;
const ll RANGE = 333334;
ll L, R, Q, i, j, k, l, g;
vector<ll> A;
vector<ll> spf(RANGE + 1, 0);  // spf[i]: i の最小の素因数
vector<ll> primes;             // RANGE 以下の素数のリスト

// RANGE 以下の n の素因数分解
// spf を用いる
map<ll, ll> get_prime_factor(ll n) {
    map<ll, ll> prime_factor;
    while (n > 1) {
        ll prime = spf[n];
        if (prime_factor.count(prime) > 0) {
            prime_factor[prime] += 1;
        } else {
            prime_factor[prime] = 1;
        }
        n /= prime;
    }
    return prime_factor;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> L >> R;

    // 線形篩 O(N)
    FOR(i, 2, RANGE + 1) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (const auto p : primes) {
            if (p > spf[i] || p * i > RANGE) break;
            spf[p * i] = p;
        }
    }

    ll ans = 0;
    FOR(g, 2, R / 3 + 2) {
        auto fact = get_prime_factor(g);
        bool flg = false;
        for(auto v: fact) {
            if (v.second > 1) {
                flg = true;
                break;
            }
        }
        if (flg) {
            ll sz = fact.size();
            ll count = R / g - max(1LL, (L - 1) / g);
            if (sz % 2 == 1) {
                ans -= count * 2;
            } else {
                ans += count * 2;
                // assert(ans >= 0);
            }
        } else {
            ll sz = fact.size();
            ll count = R / g - max(1LL, (L - 1) / g);
            if (sz % 2 == 1) {
                ans += count * (count - 1);
            } else {
                ans -= count * (count - 1);
                // assert(ans >= 0);
            }
        }
    }
    cout << ans << endl;
}