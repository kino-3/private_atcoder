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

ll N, i, d, c, s;
ll max_day = 5000;
vector<tuple<ll, ll, ll>> DCS;
vector<ll> D, C, S;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    vector<ll> dp(max_day + 1, 0);
    REP(i, N) {
        cin >> d >> c >> s;
        DCS.push_back({d, c, s});
    }
    sort(ALL(DCS));
    REP(i, N) {
        D.push_back(get<0>(DCS[i]));
        C.push_back(get<1>(DCS[i]));
        S.push_back(get<2>(DCS[i]));
    }

    REP(i, N) {
        // ここまでの仕事
        FOR_R(d, 1, max_day + 1) {
            if (C[i] <= d && d <= D[i]) {
                dp[d] = max(dp[d], dp[d - C[i]] + S[i]);
            }
        }
        FOR(d, 1, max_day + 1) { dp[d] = max(dp[d], dp[d - 1]); }
    }
    cout << dp[max_day] << endl;
}