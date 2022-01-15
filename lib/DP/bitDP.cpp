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
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    // A.resize(N);
    // B.resize(N);
    // REP(i, N) {
    //     cin >> A[i];
    //     cin >> B[i];
    // }

    ll MAX = 1 << N;
    // dp[S]: S = 00001011 のとき 0, 1, 3 番目を使った(左寄せした)結果
    vector<ll> dp(MAX, 0);
    // TODO: 初期条件
    dp[0] = 1;
    FOR(i, 1, MAX) {
        // dp[i] を決めたい
        std::bitset<20> bs(i);
        REP(j, N) {
            // S\j を使っている状態から, j を追加する
            // (S\j を左寄せした直後に j を続ける場合)
            if (bs[j]) {
                ll flg = 1 << j;
                ll tmp = dp[i - flg];  // S\j の場合
                // TODO: tmp を反映する
            }
        }
        // dp[i] = ;
    }
    cout << dp[MAX - 1] << endl;
}