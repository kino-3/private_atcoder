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

const ll mod = 998244353;
ll N, M, i, j, k, l;
vector<vector<ll>> A, dp, rev_dp;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // N 行 M 列の行列の受け取り
    cin >> N >> M;
    A.resize(N);
    REP(i, N) {
        REP(j, M) {
            cin >> k;
            A[i].push_back(k);
        }
    }
    // print_vv(A);

    // dp[i][j] = A[i][j] + dp[i][j - 1] + dp[i - 1][j] - dp[i][j]
    // でもよいが, これだと O(N^D 2^D) となる (各マスで2^D)
    // ref.
    // https://qiita.com/convexineq/items/afc84dfb9ee4ec4a67d5#2%E6%AC%A1%E5%85%83%E3%81%AE%E3%82%BC%E3%83%BC%E3%82%BF%E5%A4%89%E6%8F%9B
    dp = A;
    FOR(i, 1, N) {
        REP(j, M) { dp[i][j] += dp[i - 1][j]; }
    }
    REP(i, N) {
        FOR(j, 1, M) { dp[i][j] += dp[i][j - 1]; }
    }
    // print_vv(dp);

    // 逆変換
    rev_dp = dp;
    FOR_R(i, 1, N) {
        REP(j, M) { rev_dp[i][j] -= rev_dp[i - 1][j]; }
    }
    REP(i, N) {
        FOR_R(j, 1, M) { rev_dp[i][j] -= rev_dp[i][j - 1]; }
    }
    // print_vv(rev_dp);
}