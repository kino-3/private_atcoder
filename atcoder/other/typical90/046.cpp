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

ll N, i, j, k, l;
multiset<ll> A, B, C;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j;
        A.insert(j % 46);
    }
    REP(i, N) {
        cin >> j;
        B.insert(j % 46);
    }
    REP(i, N) {
        cin >> j;
        C.insert(j % 46);
    }
    ll ans = 0;
    REP(i, 46) {
        REP(j, 46) {
            REP(k, 46) {
                if ((i + j + k) % 46 == 0) {
                    ans += A.count(i) * B.count(j) * C.count(k);
                }
            }
        }
    }
    cout << ans << endl;
}
