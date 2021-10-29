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

ll N, P, Q, i, j, k_0, k_1, k_2, k_3, k_4;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> P >> Q;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }
    ll ans = 0;
    REP(k_0, N) {
        FOR(k_1, k_0 + 1, N) {
            FOR(k_2, k_1 + 1, N) {
                FOR(k_3, k_2 + 1, N) {
                    FOR(k_4, k_3 + 1, N) {
                        ll tmp = A[k_0] % P;
                        tmp = (tmp * A[k_1]) % P;
                        tmp = (tmp * A[k_2]) % P;
                        tmp = (tmp * A[k_3]) % P;
                        tmp = (tmp * A[k_4]) % P;
                        if (tmp == Q) {
                            ans += 1;
                        }
                    }
                }
            }
        }
    }
    cout << ans << endl;
}