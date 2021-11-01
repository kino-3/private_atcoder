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

ll N, K, i;
ll L = 1000000007;

ll mod_pow(ll x, ll n, ll mod) {
    // x^n % mod を返す
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    if (N == 1) {
        cout << K % L << endl;
    } else if (N == 2) {
        ll ans = K % L;
        ans *= (K - 1);
        cout << ans % L << endl;
    } else {
        ll ans = K % L;
        ans *= (K - 1);
        ans %= L;
        ans *= mod_pow(K - 2, N - 2, L);
        cout << ans % L << endl;
    }
}