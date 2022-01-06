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
vector<vector<ll>> comb;  // comb[i][j] == i_C_j

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // 最大は N_C_M
    N = 60;
    M = 60;
    comb = vector<vector<ll>>(N + 1, vector<ll>(M + 1, 0));
    FOR(i, 1LL, N + 1) {
        ll j_max = min(M, i);
        REP(j, j_max + 1) {
            // 考え方は格子の最短経路と同じ
            if (j == 0 || i == j) {
                comb[i][j] = 1;
            } else {
                comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
            }
        }
    }
    // print_vv(comb);
}