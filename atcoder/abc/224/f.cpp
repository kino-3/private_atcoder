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

ll mod = 998244353;
ll i;
string S;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> S;
    ll ans = S[S.size() - 1] - '0';
    ll base = 11;
    ll base_pow = 90;
    REP_R(i, S.size() - 1) {
        ll tmp = S[i] - '0';
        ans = (ans * 2 + tmp * base) % mod;
        // 後処理
        base *= 2;
        base += base_pow;
        base %= mod;
        base_pow *= 10;
        base_pow %= mod;
    }
    cout << ans << endl;
}