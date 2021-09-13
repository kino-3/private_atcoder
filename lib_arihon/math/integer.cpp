#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

// 約数関連

ll gcd(ll a, ll b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

ll extgcd(ll a, ll b, ll& x, ll& y) {
    // ax + by = gcd(a,b) を満たす解を x, y に代入し,
    // gcd(a, b) を返す
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

// 素数

bool is_prime(ll n) {
    // 正の整数 n は素数か
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    if (n == 1) {
        return false;
    }
    return true;
}

vector<ll> list_primes(ll n) {
    // n 以下の素数を列挙する
    vector<ll> primes;
    if (n == 1) {
        return primes;
    }
    primes.push_back(2);
    for (ll i = 3; i <= n; i++) {
        for (const auto& prime : primes) {
            if (prime * prime > i) {
                primes.push_back(i);
                break;
            }
            if (i % prime == 0) {
                break;
            }
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

vector<ll> create_product(map<ll, ll> m) {
    // {3: 1, 5: 2} なら
    // [1*1, 3*1, 1*5, 3*5, 1*25, 3*25] を返す
    vector<ll> result;
    if (m.size() == 0) {
        result.push_back(1);
        return result;
    }
    auto itr = m.begin();
    ll prime = itr->first;
    ll count = itr->second;
    m.erase(itr);
    ll p = 1;
    for (int i = 0; i <= count; i++) {
        for (const auto& q : create_product(m)) {
            result.push_back(p * q);
        }
        p *= prime;
    }
    return result;
}

vector<ll> list_factor(ll n) {
    // n 以下の約数を列挙する
    vector<ll> list_factor = create_product(get_prime_factor(n));
    sort(list_factor.begin(), list_factor.end());
    return list_factor;
}

void print_m(map<ll, ll> m) {
    cout << "size: " << m.size() << endl;
    cout << "{";
    for (const auto& i : m) {
        cout << i.first << ":" << i.second << ",";
    }
    cout << "}" << endl;
}

// 剰余

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
    cout << gcd(30, 48) << endl;
    ll x, y;
    cout << extgcd(30, 48, x, y) << endl;
    cout << x << " " << y << endl;
    print_v(list_primes(1));
    print_v(list_primes(2));
    print_v(list_primes(50));
    print_m(get_prime_factor(1));
    print_m(get_prime_factor(2));
    print_m(get_prime_factor(1000));
    print_m(get_prime_factor(2021));
    print_v(list_factor(1));
    print_v(list_factor(2));
    print_v(list_factor(1000));
    print_v(list_factor(2021));
    cout << mod_pow(123, 456, 123456) << endl; // 17505
}