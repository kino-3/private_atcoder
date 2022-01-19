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

    // dp[digit][less][zero]: digit 桁まで決めた状態における暫定的な答
    // (例: S=123456 のとき dp[4] は 1234 の問題の答)
    // (less: 確定部分に S 未満を含むか)
    // (zero: 確定部分が 0 以外を含むか)
    // S = 123456 のとき
    // dp[2][0][0] は 12XXXX を考える
    // dp[2][0][1] はあり得ない
    // dp[4][1][0] は @@@@XX を考える (0 < @@@@ < 1234)
    // dp[4][1][1] は 0000XX を考える
    // 遷移は配る DP のイメージで
    // 1. dp[4][0][0] <- dp[3][0][0] // 123XXX -> 1234XXX (4)
    // 1. dp[4][1][0] <- dp[3][0][0] // 123XXX -> 123@XXX (@ < 4)
    // 2. dp[4][1][0] <- dp[3][1][0] // @@@XXX -> @@@#XXX (# < 10 and 0 < @@@)
    // 3. dp[4][1][0] <- dp[3][1][1] // 000XXX -> 000#XXX (0 < # < 10)
    // 3. dp[4][1][1] <- dp[3][1][1] // 000XXX -> 0000XXX (0)
    // それ以外はあり得ない
    vector<vector<vector<vector<ll>>>> dp(
        S.size() + 1, vector<vector<vector<ll>>>(
                          2, vector<vector<ll>>(2, vector<ll>(1 << 10, -1))));

    // TODO: 初期条件
    dp[0][0][0][sup] = 0;
    dp[0][1][0][sup];
    dp[0][1][1][sup];
    REP(i, S.size()) {
        ll digit = S[i] - '0';

        // ll sub = sup;
        // do {  // 辞書と逆順にループ
        //     std::bitset<100> bs(sub);
        //     sub = (sub - 1) & sup;  // see. 蟻本 p.144
        // } while (sub != sup);

        // 123XXX -> 1234XXX
        // dp[i + 1][0][0] += dp[i][0][0] * digit;
        sub = sup;
        do {  // 辞書と逆順にループ
            std::bitset<100> bs(sub);
            if (dp[i][0][0][sub] >= 0) {
                ll to = sub;
                if (dp[i + 1][0][0][to] < 0) dp[i + 1][0][0][to] = 0;
                if (bs[digit]) to -= 1 << digit;
                dp[i + 1][0][0][to] += dp[i][0][0][sub] * 10 + digit;
                dp[i + 1][0][0][to] %= mod;
            }
            sub = (sub - 1) & sup;  // see. 蟻本 p.144
        } while (sub != sup);

        // 123XXX -> 123jXXX
        sub = sup;
        do {  // 辞書と逆順にループ
            std::bitset<100> bs(sub);
            REP(j, S[i] - '0') {
                if (dp[i][0][0][sub] < 0) continue;
                ll to = sub;
                if (dp[i + 1][1][0][to] < 0) dp[i + 1][1][0][to] = 0;
                if (bs[j]) to -= 1 << j;
                if (i == 0 && j == 0) continue;
                dp[i + 1][1][0][to] += dp[i][0][0][sub] * 10 + j;
                dp[i + 1][1][0][to] %= mod;
            }
            sub = (sub - 1) & sup;  // see. 蟻本 p.144
        } while (sub != sup);

        // @@@XXX -> @@@jXXX
        sub = sup;
        do {  // 辞書と逆順にループ
            std::bitset<100> bs(sub);
            REP(j, 10) {
                if (dp[i][1][0][sub] < 0) continue;
                ll to = sub;
                if (dp[i + 1][1][0][to] < 0) dp[i + 1][1][0][to] = 0;
                if (bs[j]) to -= 1 << j;
                if (i == 0) continue;
                dp[i + 1][1][0][to] += dp[i][1][0][sub] * 10 + j;
                dp[i + 1][1][0][to] %= mod;
            }
            sub = (sub - 1) & sup;  // see. 蟻本 p.144
        } while (sub != sup);

        if (i != 0) {  // i == 0 のときは上と初期条件で考える
            // 000XXX -> 000jXX (0 < j < 10)
            sub = sup;
            do {  // 辞書と逆順にループ
                std::bitset<100> bs(sub);
                FOR(j, 1, 10) {
                    ll to = sub;
                    if (dp[i + 1][1][0][to] < 0) dp[i + 1][1][0][to] = 0;
                    if (bs[j]) to -= 1 << j;
                    dp[i + 1][1][0][to] += j;
                    dp[i + 1][1][0][to] %= mod;
                }
                sub = (sub - 1) & sup;  // see. 蟻本 p.144
            } while (sub != sup);

            0;  // 000XXX -> 0000XX
        } else {
            0;  // 0XXXXX
        }

        debug_print_count();
        print_v(dp[i + 1][0][0]);
        print_v(dp[i + 1][1][0]);
    }
    ll ans = max(0LL, dp[S.size()][0][0][0]) + max(0LL, dp[S.size()][1][0][0]);
    cout << ans % mod << endl;
}