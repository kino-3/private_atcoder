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

ll n, N, i;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> n;
    vector<ll> v;
    while (n > 0) {
        v.push_back(n % 10);
        n /= 10;
    }
    N = v.size();
    ll ans = 0;
    REP(i, 1 << N) {
        // i = 0...2^N-1 (N 桁の辞書順)
        std::bitset<100> bs(i);
        ll j;
        vector<ll> left, right;
        // 上位桁からループ
        REP_R(j, N) {
            if (bs[j]) {
                left.push_back(v[j]);
            } else {
                right.push_back(v[j]);
            }
        }
        sort(ALL(left));
        reverse(ALL(left));
        sort(ALL(right));
        reverse(ALL(right));
        ll left_n = 0;
        ll right_n = 0;
        for (auto vv : left) {
            left_n *= 10;
            left_n += vv;
        }
        for (auto vv : right) {
            right_n *= 10;
            right_n += vv;
        }
        ans = max(ans, left_n * right_n);
    }
    cout << ans << endl;
}