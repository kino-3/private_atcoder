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
ll L, R, i, j, k, l;

ll sigma(ll num) {
    if (num % 2 == 0) {
        return ((num / 2 % mod) * ((num + 1) % mod)) % mod;
    } else {
        return ((num % mod) * ((num + 1) / 2 % mod)) % mod;
    }
}

ll count(ll num) {
    ll ans = 0;
    ll pow = 1;
    FOR(i, 1, 18) {
        // i 桁
        pow *= 10;  // (i+1)桁
        if (num >= pow) {
            ans += (sigma(pow - 1) - sigma(pow / 10 - 1) + mod) % mod * i;
            ans %= mod;
        } else {
            ans += (sigma(num) - sigma(pow / 10 - 1) + mod) % mod * i;
            ans %= mod;
            break;
        }
    }
    if (num == 1000000000000000000) ans += 19 * (1000000000000000000 % mod);
    return ans % mod;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> L >> R;
    cout << (count(R) - count(L - 1) + mod) % mod << endl;
}