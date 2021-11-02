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

ll mod = 1000000007;
ll N, Q, i, j, k, l, m;
vector<ll> X, Y, Z;
vector<bitset<60>> W;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> Q;
    REP(i, Q) {
        cin >> j >> k >> l >> m;
        X.push_back(j - 1);
        Y.push_back(k - 1);
        Z.push_back(l - 1);
        W.push_back(bitset<60>(m));
    }
    ll ans = 1;
    REP(i, 60) {  // 対象桁
        ll tmp = 0;
        REP(j, 1 << N) {  // これが条件を満たしているか
            std::bitset<12> bs(j);
            bool flg = true;
            REP(k, Q) {
                if (W[k][i]) {
                    if (!bs[X[k]] && !bs[Y[k]] && !bs[Z[k]]) {
                        flg = false;
                        break;
                    }
                } else {
                    if (bs[X[k]] || bs[Y[k]] || bs[Z[k]]) {
                        flg = false;
                        break;
                    }
                }
            }
            if (flg) tmp++;
        }
        ans *= tmp;
        ans %= mod;
    }
    cout << ans << endl;
}