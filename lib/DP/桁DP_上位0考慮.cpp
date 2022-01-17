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

    // ある自然数 S について, S 以下の自然数の「全ての桁の総積」の総和
    // 文字列で受け取る方が扱いやすい
    cin >> S;

    // dp[digit][less]: digit 桁まで決めた状態における暫定的な答
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
    vector<vector<vector<ll>>> dp(S.size() + 1,
                                  vector<vector<ll>>(2, vector<ll>(2)));

    // TODO: 初期条件
    dp[0][0][0] = 1;  // メインの遷移を考えてからのほうが考えやすい気がする
    dp[0][1][0] = 0;  // メインの遷移を考えてからのほうが考えやすい気がする
    dp[0][1][1] = 0;  // メインの遷移を考えてからのほうが考えやすい気がする
    REP(i, S.size()) {
        dp[i + 1][0][0] = 0;
        dp[i + 1][1][0] = 0;
        dp[i + 1][1][1] = 0;
        ll digit = S[i] - '0';

        dp[i + 1][0][0] += dp[i][0][0] * digit;  // 123XXX -> 1234XXX

        REP(j, S[i] - '0') {
            dp[i + 1][1][0] += dp[i][0][0] * j;  // 123XXX -> 123jXXX
        }

        REP(j, 10) {
            dp[i + 1][1][0] += dp[i][1][0] * j;  // @@@XXX -> @@@jXXX
        }

        if (i != 0) {  // i == 0 のときは上と初期条件で考える
            REP(j, 10) {
                dp[i + 1][1][0] += j;  // 000XXX -> 000jXX
            }

            0;  // 000XXX -> 0000XX
        }
    }
    cout << dp[S.size()][0][0] << endl;  // 123456 の結果
    cout << dp[S.size()][1][0] << endl;  // @@@@@@ (0 < @@@@@@ < 123456) の個数
    cout << dp[S.size()][1][1] << endl;  // 0 の個数
}