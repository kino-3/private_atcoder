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


// B 進数表記である n を 10 進数表記にする
ll base_B_to_10(ll n, ll B) {
    ll res = 0;
    ll pow = 1;
    while (n > 0) {
        res += (n % 10) * pow;
        n /= 10;
        pow *= B;
    }
    return res;
}

// B 進数表記である n を 10 進数表記にする
ll base_B_to_10(string n, ll B) {
    ll res = 0;
    ll pow = 1;
    REP_R(i, n.size()) {
        res += (n[i] - '0') * pow;
        pow *= B;
    }
    return res;
}

// 10 進数表記である n を B 進数表記にする
ll base_10_to_B(ll n, ll B) {
    ll res = 0;
    ll pow = 1;
    while (n > 0) {
        res += (n % B) * pow;
        n /= B;
        pow *= 10;
    }
    return res;
}

// 10 進数表記である n を B 進数表記にする
string base_10_to_B_str(ll n, ll B) {
    string res = "";
    while (n > 0) {
        res.push_back(n % B + '0');
        n /= B;
    }
    reverse(ALL(res));
    return res;
}

const ll mod = 998244353;
ll N, i;
string S;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // cin >> N;
    // cout << N << endl;

    assert(base_B_to_10(123456, 7) == 22875);
    assert(base_B_to_10("123456", 7) == 22875);
    assert(base_10_to_B(22875, 7) == 123456);
    assert(base_10_to_B_str(22875, 7) == "123456");
}