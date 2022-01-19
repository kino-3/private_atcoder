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
    assert(DEBUG_PRINT_COUNT < 10000);
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
ll N, M, Q, i, j, k, l, sub;
string S;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // 文字列で受け取る方が扱いやすい
    cin >> S;
    cin >> M;
    A.resize(M);
    REP(i, M) { cin >> A[i]; }

    // まだ使っていないもの
    ll sup = 0;
    for (auto v : A) {
        sup += (1 << v);
    }
    debug_print(sup);

    // dp[digit][less]: digit 桁まで決めた状態における暫定的な答
    // (例: S=123456 のとき dp[4] は 1234 の問題の答)
    // (less: 確定部分に S 未満を含むか)
    // S = 123456 のとき
    // dp[2][0] は 12XXXX を考える
    // dp[4][1] は @@@@XX を考える (0 < @@@@ < 1234)
    // 遷移は配る DP のイメージで
    // 1. dp[4][0] <- dp[3][0] // 123XXX -> 1234XXX (4)
    // 1. dp[4][1] <- dp[3][0] // 123XXX -> 123@XXX (@ < 4)
    // 2. dp[4][1] <- dp[3][1] // @@@XXX -> @@@#XXX (# < 10) (※ 0 < @@@)
    // 3. dp[4][1] <- new      // 000XXX -> 000#XXX (0 < # < 10)

    // dp[][][S] の S は使用したか ?
    vector<vector<vector<ll>>> dp(S.size() + 1,
                                  vector<vector<ll>>(2, vector<ll>(1024, 0)));
    vector<vector<vector<ll>>> count(S.size() + 1,
                                     vector<vector<ll>>(2, vector<ll>(1024, 0)));

    // 1 桁目
    ll digit = S[0] - '0';
    dp[1][0][1 << digit] = digit;
    count[1][0][1 << digit] = 1;
    FOR(j, 1, digit) {
        dp[1][1][1 << j] = j;
        count[1][1][1 << j] = 1;
    }  // 1 桁目が 1 の場合は loop は 0 回

    // 2 桁目以降
    FOR(i, 1, S.size()) {
        ll digit = S[i] - '0';
        ll flg = 1 << digit;
        REP(j, 1024) {
            // 123XXX -> 1234XXX
            count[i + 1][0][j | flg] += count[i][0][j];
            count[i + 1][0][j | flg] %= mod;
            dp[i + 1][0][j | flg] += dp[i][0][j] * 10 + count[i][0][j] * digit;
            dp[i + 1][0][j | flg] %= mod;

            // 123XXX -> 123jXXX
            REP(k, digit) {
                ll flg2 = 1 << k;
                count[i + 1][1][j | flg2] += count[i][0][j];
                count[i + 1][1][j | flg2] %= mod;
                dp[i + 1][1][j | flg2] += dp[i][0][j] * 10 + count[i][0][j] * k;
                dp[i + 1][1][j | flg2] %= mod;
            }

            // @@@XXX -> @@@jXXX (@@@ ≠ 0)
            REP(k, 10) {
                ll flg2 = 1 << k;
                count[i + 1][1][j | flg2] += count[i][1][j];
                count[i + 1][1][j | flg2] %= mod;
                dp[i + 1][1][j | flg2] += dp[i][1][j] * 10 + count[i][1][j] * k;
                dp[i + 1][1][j | flg2] %= mod;
            }
        }
        // 000XXX -> 000#XXX (0 < # < 10)
        FOR(k, 1, 10) {
            ll flg2 = 1 << k;
            count[i + 1][1][flg2] += 1;
            count[i + 1][1][flg2] %= mod;
            dp[i + 1][1][flg2] += k;
            dp[i + 1][1][flg2] %= mod;
        }
        // print_v(dp[i + 1][1]);
    }
    ll ans = 0;
    REP(i, 1024) {
        if (~(~sup|i) == 0) {
            ans += dp[S.size()][0][i];
            ans += dp[S.size()][1][i];
            ans %= mod;
            // debug_print(i);
        }
    }
    cout << ans << endl;
}