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

const ll mod = 998244353;  // 1000000007;
ll N, M, i, j, k, l;
string S, T;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // ある自然数 S について, S 以下の自然数の個数
    // 文字列で受け取る方が扱いやすい
    cin >> S;

    // dp[digit][less]: digit 桁まで決めた状態における暫定的な答
    // (less: 確定部分に S 未満を含むか)
    // S = 123456 のとき
    // dp[2][0] は 12XXXX を考える
    // dp[4][1] は @@@@XX を考える (@@@@ < 1234)
    // 遷移は配る DP のイメージで
    // 1.1. dp[4][0] <- dp[3][0] // 123XXX -> 1234XXX (4)
    // 1.2. dp[4][1] <- dp[3][0] // 123XXX -> 123@XXX (@ < 4)
    // 2.   dp[4][1] <- dp[3][1] // @@@XXX -> @@@#XXX (# < 10)
    vector<vector<ll>> dp(S.size() + 1, vector<ll>(2));

    // TODO: 初期条件
    dp[0][0] = 1; // メインの遷移を考えてからのほうが考えやすい気がする
    dp[0][1] = 0; // 大体の問題で 0 だと思う
    REP(i, S.size()) {
        dp[i + 1][0] = 0;
        dp[i + 1][1] = 0;

        dp[i + 1][0] += dp[i][0];  // 123XXX -> 1234XXX

        REP(j, S[i] - '0') {
            dp[i + 1][1] += dp[i][0];  // 123XXX -> 123jXXX
        }

        REP(j, 10) {
            dp[i + 1][1] += dp[i][1];  // @@@XXX -> @@@jXXX
        }
    }
    cout << dp[S.size()][0] << endl; // 123456 の個数
    cout << dp[S.size()][1] << endl; // @@@@@@ (0 <= @@@@@@ < 123456) の個数
}