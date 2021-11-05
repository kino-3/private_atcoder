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

// ax + by = gcd(a,b) を満たす解を x, y に代入し, gcd(a, b) を返す
ll extgcd(ll a, ll b, ll& x, ll& y) {
    int d = a;
    if (b != 0) {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    } else {
        x = 1;
        y = 0;
    }
    return d;
}

// mod を法とする a の逆元
ll mod_inverse(ll a, ll mod) {
    ll x, y;
    ll gcd = extgcd(a, mod, x, y);
    if (gcd == 1)
        return (mod + x) % mod;
    else
        return -1;
}

// 素数 mod を法とする i の逆元 res[i] (i<=n)
// 計算量 O(n)
vector<ll> mod_inverse_list(ll n, ll mod) {
    vector<ll> res(n + 1);
    res[0] = 0;
    res[1] = 1;
    for (ll i = 2; i <= n; i++) {
        // mod = i*(mod/i) + mod%i
        // 0 ≡ i*(mod/i) + mod%i
        // i*(mod/i) ≡ -mod%i
        // mod%i < i より, res[mod%i] は既知で,
        // i*(mod/i)*res[mod%i] ≡ -1
        // (-1)*(-1) ≡ 1 より
        // i*(mod/i)*res[mod%i]*(-1) ≡ 1
        // よって,
        // res[i] ≡ (mod/i)*res[mod%i]*(-1)
        // (mod/i)*res[mod%i] > 0 なので,
        res[i] = mod - ((mod / i) * res[mod % i]) % mod;
    }
    return res;
}

// x^n % mod を返す
ll mod_pow(ll x, ll n, ll mod) {
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

// 剰余
class Combination {
    ll mod;
    vector<ll> factorial;

   public:
    // n は n_C_k の n の最大値
    Combination(ll n, ll _mod = 1000000007) {
        mod = _mod;
        factorial.push_back(1);
        factorial.push_back(1);
        for (ll i = 2; i <= n; i++) {
            factorial.push_back(factorial[i - 1] * i % mod);
        }
    }

    // n_C_k を返す
    ll comb(ll n, ll k) {
        ll res = factorial[n] * mod_inverse(factorial[k], mod) % mod;
        return res * mod_inverse(factorial[n - k], mod) % mod;
    }
};

ll mod = 1000000007;
ll N, i, k;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    Combination cb = Combination(N, mod);
    FOR(k, 1, N + 1) {
        ll ans = 0;
        ll x = 1;
        while (k * (x - 1) + 1 <= N) {
            ll n = x + N - (k * (x - 1) + 1);
            ans += cb.comb(n, x);
            ans %= mod;
            x++;
        }
        cout << ans << endl;
    }
}