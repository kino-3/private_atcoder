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

ll K, i, j;
ll mod = 1000000007;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> K;
    if (K % 9 != 0) {
        cout << 0 << endl;
    } else {
        vector<ll> dp(9, 0);  // 先頭が i+1
        vector<ll> pre_dp(9, 0);
        dp[0] = 1;
        REP(i, K - 1) {
            copy(ALL(dp), pre_dp.begin());
            FOR(j, 1, 9) {
                dp[j] = pre_dp[j - 1];
                dp[0] += pre_dp[j];
            }
            dp[0] %= mod;
        }
        ll ans = 0;
        REP(i, 9) { ans += dp[i]; }
        cout << ans % mod << endl;
    }
}