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

ll N, i, j, j_1, j2, j3, j4;
vector<vector<ll>> A(1001, vector<ll>(1001, 0));

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j_1 >> j2 >> j3 >> j4;
        A[j_1][j2] += 1;
        A[j_1][j4] -= 1;
        A[j3][j2] -= 1;
        A[j3][j4] += 1;
    }
    vector<ll> ans(N + 1);
    REP(i, 1000) {
        REP(j, 1000) {
            if (j > 0) A[i][j] += A[i][j - 1];
        }
    }
    REP(i, 1000) {
        REP(j, 1000) {
            if (i > 0) A[i][j] += A[i - 1][j];
        }
    }
    REP(i, 1000) {
        REP(j, 1000) { ans[A[i][j]] += 1; }
    }
    FOR(i, 1, N + 1) { cout << ans[i] << endl; }
}