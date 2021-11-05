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

// n の約数を列挙する (上3個の関数が必要)
// 動作確認: https://atcoder.jp/contests/typical90/tasks/typical90_cg
vector<ll> list_factor(ll n) {
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

int main() {
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
}