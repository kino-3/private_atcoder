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
ll N, i, j, k, l;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, 2 * N) {
        cin >> j;
        A.push_back(j);
    }
    ll ans = 0;
    REP(i, N) {
        ll diff = 100000000000;
        ll idx = -1;
        REP(j, 2 * (N - i) - 1) {
            if (diff > abs(A[j] - A[j + 1])) {
                diff = abs(A[j] - A[j + 1]);
                idx = j;
            }
        }
        ans += diff;
        A.erase(A.begin() + idx);
        A.erase(A.begin() + idx);
    }
    cout << ans << endl;
}