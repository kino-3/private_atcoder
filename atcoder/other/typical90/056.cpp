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

ll N, S, i, j, k;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> S;
    REP(i, N) {
        cin >> j >> k;
        A.push_back(j);
        B.push_back(k);
    }
    vector<string> dp(S + 1, "");
    vector<string> tmp_dp(S + 1, "");
    REP(i, S) { dp[i + 1] = "X"; }
    REP(i, N) {
        ll a = A[i];
        ll b = B[i];
        fill(ALL(tmp_dp), "X");
        REP(j, S - a + 1) {
            if (dp[j][0] != 'X') tmp_dp[j + a] = dp[j] + "A";
        }
        REP(j, S - b + 1) {
            if (dp[j][0] != 'X') tmp_dp[j + b] = dp[j] + "B";
        }
        copy(ALL(tmp_dp), dp.begin());
    }
    if (dp[S] == "X") {
        cout << "Impossible" << endl;
    } else {
        cout << dp[S] << endl;
    }
}