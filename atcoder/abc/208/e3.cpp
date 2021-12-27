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
ll N, K, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;

    vector<map<ll, ll>> prod;
    map<ll, ll> tmp;
    FOR(i, 0, 10) tmp[i] = 1;
    prod.push_back(tmp);
    REP(i, 17) {
        auto prev = prod[i];
        map<ll, ll> tmp = prod[i];
        FOR(j, 1, 10) {
            for (auto v : prev) {
                ll p = v.first * j;
                if (tmp.count(p) > 0) {
                    tmp[p] += v.second;
                } else {
                    tmp[p] = v.second;
                }
            }
        }
        prod.push_back(tmp);
    }
    // debug_print(prod[17][150094635296999121]);
    // j = 0;
    // for (auto v: prod[3]) {
    //     j += v.second;
    // }
    // debug_print(j);

    vector<ll> number;
    ll M = N;
    while (M > 0) {
        number.push_back(M % 10);
        M /= 10;
    }
    // print_v(number);

    if (N < 10) {
        cout << min(N, K) << endl;
        return 0;
    }

    ll pow = 1;
    vector<ll> pow10;
    REP(i, 18) {
        pow10.push_back(pow);
        pow *= 10;
    }

    // 1 - 999999
    ll ans = -1;
    ll keta = number.size();
    for (auto v : prod[keta - 2]) {
        if (v.first <= K) ans += v.second;
    }
    // debug_print(ans);
    REP_R(i, keta) {
        ll digit = number[i];
        ll upper_prod = 1;
        FOR(j, i + 1, keta) upper_prod *= number[j];
        // 76j0000 - 76j9999
        FOR(j, 1, digit) {
            ll tmp = j * upper_prod;
            if (i == 0) {
                // 765432j
                if (tmp <= K) ans += 1;
            } else if (i == 1) {
                // 76543j0 - 76543j9
                debug_print(tmp);
                REP(k, 10) {
                    if (tmp * k <= K) ans += 1;
                }
            } else {
                // 76j1000 - 76j9999
                auto tmp_prod = prod[i - 1];
                for (auto v: prod[i - 2]) {
                    tmp_prod[v.first] -= v.second;
                }
                for (auto v: tmp_prod) {
                    if (tmp * v.first <= K) ans += v.second;
                }
                // 76j0000 - 76j0999
                ans += pow10[i - 1];
            }
        }
        // 7600000 - 7609999
        if (digit > 0) {
            if (i != keta - 1) {
                ans += pow10[i];
            }
        }
    }
    cout << ans << endl;
}