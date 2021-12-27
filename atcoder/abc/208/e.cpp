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

const ll mod = 998244353;
ll N, K, i, j, k, l;
string S, T;

map<ll, ll> prod_high(ll num) {
    // 1 - num
    assert(num > 0);
    ll ii;
    map<ll, ll> res;
    FOR(ii, 1, num + 1) {
        ll n = ii;
        ll tmp = 1;
        while (n > 0) {
            tmp *= (n % 10);
            n /= 10;
        }
        if (res.count(tmp) > 0) {
            res[tmp]++;
        } else {
            res[tmp] = 1;
        }
    }
    return res;
}

map<ll, ll> prod_low(ll num) {
    // 000000 - 000num
    map<ll, ll> res;
    if (num < 100000) {  // num = 000000 - 099999
        res[0] = num + 1;
        return res;
    }
    res[0] = 100000;
    FOR(ii, 100000, num + 1) {
        ll n = ii;
        ll tmp = 1;
        while (n > 0) {
            tmp *= (n % 10);
            n /= 10;
        }
        if (res.count(tmp) > 0) {
            res[tmp]++;
        } else {
            res[tmp] = 1;
        }
    }
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;

    // map<ll, ll> prod_low;  // 000000 - 999999
    // prod_low[0] = 100000;
    // FOR(i, 100000, 1000000) {
    //     ll n = i;
    //     ll tmp = 1;
    //     while (n > 0) {
    //         tmp *= (n % 10);
    //         n /= 10;
    //     }
    //     if (prod_low.count(tmp) > 0) {
    //         prod_low[tmp]++;
    //     } else {
    //         prod_low[tmp] = 1;
    //     }
    // }
    // debug_print(prod_low.size());
    // print_map(prod_high(27));
    // print_map(prod_low(12345));
    // print_map(prod_low(111113));

    ll MILLION = 1000000;
    if (N <= MILLION) {
        ll ans = 0;
        for (auto v : prod_high(N)) {
            if (v.first <= K) ans += v.second;
        }
        cout << ans << endl;
    } else if (N < MILLION * MILLION) {
        // 123456789
        ll ans = 0;
        ll low = N % MILLION;   // 456789
        ll high = N / MILLION;  // 123
        // 1 - 999999
        for (auto v : prod_high(MILLION - 1)) {
            if (v.first <= K) ans += v.second;
        }
        // 1000000 - 122999999
        if (high > 1) {
            for (auto v : prod_high(high - 1)) {
                for (auto vv : prod_low(MILLION - 1)) {
                    if (v.first * vv.first <= K) ans += v.second * vv.second;
                }
            }
        }
        // 123000000 - 123456789
        ll prod_h = 1;
        while (high > 0) {
            prod_h *= (high % 10);
            high /= 10;
        }
        for (auto v : prod_low(low)) {
            if (v.first * prod_h <= K) ans += v.second;
        }
        cout << ans << endl;
    } else {
        // 123456789
        ll ans = 0;
        ll low = N % MILLION;               // 789
        ll middle = N / MILLION % MILLION;  // 456
        ll high = N / MILLION / MILLION;    // 123
        auto prod_high_full = prod_high(MILLION - 1);
        auto prod_low_full = prod_low(MILLION - 1);
        // 1 - 999
        for (auto v : prod_high_full) {
            if (v.first <= K) ans += v.second;
        }
        // 1000 - 999999
        for (auto v : prod_low_full) {
            for (auto vv : prod_high_full) {
                if (v.first * vv.first <= K) ans += v.second * vv.second;
            }
        }
        // 1000000 - 122999999
        if (high > 1) {
            for (auto v : prod_low_full) {
                for (auto vv : prod_low_full) {
                    for (auto vvv : prod_high(high - 1)) {
                        if (v.first * vv.first * vvv.first <= K)
                            ans += v.second * vv.second * vvv.second;
                    }
                }
            }
        }
        // 123000000 - 123455999
        ll prod_h = 1;
        while (high > 0) {
            prod_h *= (high % 10);
            high /= 10;
        }
        for (auto v : prod_low_full) {
            for (auto vv : prod_low(middle - 1)) {
                if (v.first * vv.first * prod_h <= K)
                    ans += v.second * vv.second;
            }
        }
        cout << ans << endl;
        // 123456000 - 123456789
        ll prod_m = prod_h;
        while (middle > 0) {
            prod_m *= (middle % 10);
            middle /= 10;
        }
        for (auto v : prod_low(low - 1)) {
            if (v.first * prod_m <= K) ans += v.second;
        }
        cout << ans << endl;
    }
}