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
ll i, j, k, l;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    if (true) {
        // 条件を満たすアイテムの選び方の場合の数 (mod)
        // 計算量 O(NW)
        // 条件1. 各アイテムは最大 1 個 (使うか否か)
        // 条件2. アイテムの重さの総和が w (0 <= w <= W) となる各 w について
        ll N;               // アイテムの種類数
        ll W;               // アイテムの重さの上限
        vector<ll> weight;  // アイテムの重さ
        cin >> N >> W;
        weight.resize(N);
        REP(i, N) { cin >> weight[i]; }
        vector<ll> dp(W + 1, 0);  // 場合の数
        dp[0] = 1;                // アイテム無しの時
        REP(i, N) {               // i 番目の item まで
            ll w = weight[i];
            REP_R(j, W + 1) {
                if (j + w <= W) {
                    dp[j + w] += dp[j];
                    dp[j + w] %= mod;
                }
            }
        }
        // このとき, dp[w] が求める場合の数
        // print_v(dp);
    }
}