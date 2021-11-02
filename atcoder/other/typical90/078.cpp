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
ll N, M, i, j, k, l;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    vector<vector<ll>> g(N, vector<ll>(0));
    REP(i, M) {
        cin >> j >> k;
        g[j - 1].push_back(k - 1);
        g[k - 1].push_back(j - 1);
    }
    ll ans = 0;
    REP(i, N) {
        ll tmp = 0;
        for (const auto v : g[i]) {
            if (v < i) tmp++;
        }
        if (tmp == 1) ans++;
    }
    cout << ans << endl;
}