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

template <typename T>
void debug_print(const T item) {
    cout << item << endl;
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}

ll mod = 1000000007;
ll N, i, j, k, l;
vector<ll> A, B;

vector<ll> list_primes(ll n) {
    // n 以下の素数を列挙する
    // 素数で割れるか考えるよりも, エラトステネスの篩の方が速かった
    // https://atcoder.jp/contests/typical90/tasks/typical90_ad
    if (n == 1) {
        return vector<ll>(0);
    }
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (ll idx = i * i; idx <= n; idx += i) {
                is_prime[idx] = false;
            }
        }
    }
    vector<ll> primes;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

map<ll, ll> get_prime_factor(ll n) {
    // n を素因数分解する
    vector<ll> primes = list_primes(static_cast<ll>(sqrt(n)) + 1);
    map<ll, ll> prime_factor;
    for (const auto& prime : primes) {
        while (true) {
            if (n % prime == 0) {
                if (prime_factor.count(prime) > 0) {
                    prime_factor[prime] += 1;
                } else {
                    prime_factor[prime] = 1;
                }
                n /= prime;
            } else {
                break;
            }
        }
    }
    if (n != 1) {
        prime_factor[n] = 1;  // √n より大きな素因数
    }
    return prime_factor;
}

// base^n ≡ 1 (mod modulo) となる最小の n を返す。
// 存在しなければ -1 を返す
ll carmichael(ll base, ll modulo) {
    if (__gcd(base, modulo) > 1) return -1;
    auto primes = get_prime_factor(modulo);
    if (primes.size() == 1) {
        ll pp = (primes.begin())->first;
        ll nn = (primes.begin())->second;
        if (pp == 2) {
            if (nn == 1) {
                return 1;
            } else if (nn == 2) {
                return 2;
            } else if (nn > 2) {
                ll pow = 1;
                REP(j, nn - 2) pow *= 2;
                return pow;
            }
        } else {
            ll pow = pp - 1;
            REP(j, nn - 1) pow *= pp;
            return pow;
        }
    }
    ll lcm = 1;
    for (auto it = primes.begin(); it != primes.end(); ++it) {
        ll pp = it->first;
        ll nn = it->second;
        ll pow = 1;
        REP(i, nn) pow *= pp;
        ll cc = carmichael(base, pow);
        lcm = lcm * cc / __gcd(cc, lcm);
    }
    return lcm;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }
    REP(i, N) {
        ll a = A[i];
        if (a % 2 == 0) a = a / 2;
        if (a == 1) {  // 1, 2
            cout << 1 << endl;
            continue;
        }
        cout << carmichael(10, a) << endl;
    }
}