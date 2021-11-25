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

ll N, K, i, j;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    ll comb = (1 << K) - 1;
    ll end_comb = 1 << N;
    while (comb < end_comb) {
        // (N 桁の辞書順)
        std::bitset<100> bs(comb);
        // 上位桁からループ
        REP_R(j, N) {
            if (bs[j]) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
        cout << " ";
        // 下位桁からループ
        REP(j, N) {
            if (bs[j]) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
        cout << endl;
        // 後処理
        ll x = comb & -comb;
        ll y = comb + x;
        comb = ((comb & ~y) / x >> 1) | y;
    }
}