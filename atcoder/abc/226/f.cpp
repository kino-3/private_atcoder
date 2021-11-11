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
const ll MAX = 50;
ll N, K, i;

// 長さ n を任意個数に分割した時の全ての数の最小公倍数としてありうる一覧
set<ll> compute_lcm(ll n) {
    ll i, j;
    vector<set<ll>> lcm(n);  // lcm[i] は i + 1 の場合
    REP(i, n) {              // i + 1 の場合
        lcm[i].insert(i + 1);
        REP(j, i) {  // j + 1 と i - j (j = 0,...,i-1)
            for (auto it = lcm[j].begin(), e = lcm[j].end(); it != e; ++it) {
                lcm[i].insert((i - j) * (*it) / __gcd(i - j, *it));
            }
        }
    }
    return lcm[n - 1];
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    cout << compute_lcm(N).size() << endl;
}