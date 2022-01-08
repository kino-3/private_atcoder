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
ll N, M, i, j, k, l;
string S, T;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> S;
    map<char, ll> dict;
    REP(i, S.size()) {
        if (dict.count(S[i]) > 0) {
            dict[S[i]] ++;
        } else {
            dict[S[i]] = 1;
        }
    }
    // print_map(dict);

    // 最大は N_C_M
    N = S.size();
    M = S.size();
    vector<vector<ll>>comb = vector<vector<ll>>(N + 1, vector<ll>(M + 1, 0));
    FOR(i, 1LL, N + 1) {
        ll j_max = min(M, i);
        REP(j, j_max + 1) {
            // 考え方は格子の最短経路と同じ
            if (j == 0 || i == j) {
                comb[i][j] = 1;
            } else {
                comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
                comb[i][j] %= mod;
            }
        }
    }

    vector<ll> dp(S.size() + 1, 0);
    dp[0] = 1;
    for (auto v: dict) {
        ll cnt = v.second;
        vector<ll> old_dp = dp;
        FOR(i, 1, cnt + 1) {
            // i
            REP(j, S.size()) {
                if (j + i > S.size()) continue;
                dp[i + j] += old_dp[j] * comb[i + j][i];
                dp[i + j] %= mod;
                // debug_print(i, j, comb[i + j][i]);
            }
            // debug_print(i);
            // print_v(dp);
        }
    }

    // print_v(dp);

    ll ans = 0;
    FOR(i, 1, S.size() + 1) {
        ans += dp[i];
        ans %= mod;
    }
    cout << ans << endl;
}