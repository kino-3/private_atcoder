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
ll K, i, j, k, l;
string S, T;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // ?????????????????????????????????????????????
    cin >> S;
    cin >> K;

    // dp[digit][less][zero]: digit ???????????????????????????????????????????????????
    // (???: S=123456 ????????? dp[4] ??? 1234 ???????????????)
    // (less: ??????????????? S ??????????????????)
    // (zero: ??????????????? 0 ??????????????????)
    // S = 123456 ?????????
    // dp[2][0][0] ??? 12XXXX ????????????
    // dp[2][0][1] ??????????????????
    // dp[4][1][0] ??? @@@@XX ???????????? (0 < @@@@ < 1234)
    // dp[4][1][1] ??? 0000XX ????????????
    // ??????????????? DP ??????????????????
    // 1. dp[4][0][0] <- dp[3][0][0] // 123XXX -> 1234XXX (4)
    // 1. dp[4][1][0] <- dp[3][0][0] // 123XXX -> 123@XXX (@ < 4)
    // 2. dp[4][1][0] <- dp[3][1][0] // @@@XXX -> @@@#XXX (# < 10 and 0 < @@@)
    // 3. dp[4][1][0] <- dp[3][1][1] // 000XXX -> 000#XXX (0 < # < 10)
    // 3. dp[4][1][1] <- dp[3][1][1] // 000XXX -> 0000XXX (0)
    // ??????????????????????????????
    vector<vector<vector<map<ll, ll>>>> dp(
        S.size() + 1, vector<vector<map<ll, ll>>>(2, vector<map<ll, ll>>(2)));

    // TODO: ????????????
    map<ll, ll> tmp;
    tmp[1] = 1;
    dp[0][0][0] = tmp;  // ???????????????????????????????????????????????????????????????????????????
    REP(i, S.size()) {
        ll digit = S[i] - '0';

        for (auto v : dp[i][0][0]) {
            // 123XXX -> 1234XXX
            dp[i + 1][0][0][min(v.first * digit, K + 1)] = v.second;
        }

        REP(j, S[i] - '0') {
            if (i == 0 && j == 0) continue;
            for (auto v : dp[i][0][0]) {
                // 123XXX -> 123jXXX
                if (dp[i + 1][1][0].count(min(v.first * j, K + 1)) > 0) {
                    dp[i + 1][1][0][min(v.first * j, K + 1)] += v.second;
                } else {
                    dp[i + 1][1][0][min(v.first * j, K + 1)] = v.second;
                }
            }
        }

        REP(j, 10) {
            if (i == 0) continue;
            for (auto v : dp[i][1][0]) {
                // @@@XXX -> @@@jXXX
                if (dp[i + 1][1][0].count(min(v.first * j, K + 1)) > 0) {
                    dp[i + 1][1][0][min(v.first * j, K + 1)] += v.second;
                } else {
                    dp[i + 1][1][0][min(v.first * j, K + 1)] = v.second;
                }
            }
        }

        if (i != 0) {  // i == 0 ??????????????????????????????????????????
            FOR(j, 1LL, 10LL) {
                // 000XXX -> 000jXX
                if (dp[i + 1][1][0].count(min(j, K + 1)) > 0) {
                    dp[i + 1][1][0][min(j, K + 1)] += 1;
                } else {
                    dp[i + 1][1][0][min(j, K + 1)] = 1;
                }
            }
        }
        // debug_print(i);
        // print_map(dp[i + 1][0][0]);
        // print_map(dp[i + 1][1][0]);
        // print_map(dp[i + 1][1][1]);
    }
    ll ans = 0;
    for (auto v : dp[S.size()][1][0]) {
        if (v.first <= K) {
            ans += v.second;
        }
    }
    for (auto v : dp[S.size()][0][0]) {
        if (v.first <= K) {
            ans += v.second;
        }
    }
    cout << ans << endl;
}