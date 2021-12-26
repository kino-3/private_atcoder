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
ll N, M, D, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> D;
    A.resize(N);
    REP(i, N) {
        cin >> A[i];
        if (A[i] > 0) A[i]--;
    }

    set<ll> fixed;
    REP(i, N) {
        if (A[i] != -1) {
            fixed.insert(A[i]);
        }
    }
    set<ll> unfixed;
    string base;
    string zero;
    REP(i, N) {
        if (fixed.count(i) == 0) {
            unfixed.insert(i);
            base += "1";
        } else {
            base += "0";
        }
        zero += "0";
    }

    // debug_print(base);
    map<string, ll> dp;
    dp[base] = 1;

    // print_v(A);
    REP(i, N) {
        map<string, ll> new_dp;
        if (A[i] != -1) {
            for (auto v : dp) {
                if (i - D - 1 < 0 || v.first[i - D - 1] == '0') {
                    new_dp[v.first] = v.second;
                }
            }
        } else {
            for (auto v : dp) {
                if (i - D - 1 < 0 || v.first[i - D - 1] == '0') {
                    ll low = max(0LL, i - D);
                    ll high = min(N - 1, i + D);
                    for (ll j = low; j <= high; j++) {
                        if (v.first[j] == '1') {
                            string cnt = v.first;
                            cnt[j] = '0';
                            if (new_dp.count(cnt) > 0) {
                                new_dp[cnt] += v.second;
                                new_dp[cnt] %= mod;
                            } else {
                                new_dp[cnt] = v.second;
                            }
                        }
                    }
                }
            }
        }
        dp = new_dp;
        // print_map(dp);
    }
    if (dp.count(zero) == 0) {
        cout << 0 << endl;
    } else {
        cout << dp[zero] % mod << endl;
    }
}