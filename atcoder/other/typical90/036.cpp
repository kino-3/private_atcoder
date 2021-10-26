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

ll N, Q, i, j, k;
ll INF = 1000000000000;
vector<ll> X, Y, query;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> Q;
    REP(i, N) {
        cin >> j >> k;
        X.push_back(j);
        Y.push_back(k);
    }
    REP(i, Q) {
        cin >> j;
        query.push_back(j);
    }
    // x+y, x-y, -x+y, -x-y の最大値
    vector<ll> max_data(4, -INF);
    REP(i, N) {
        ll x = X[i];
        ll y = Y[i];
        max_data[0] = max(max_data[0], x + y);
        max_data[1] = max(max_data[1], x - y);
        max_data[2] = max(max_data[2], - x + y);
        max_data[3] = max(max_data[3], - x - y);
    }
    REP(i, Q) {
        ll x = X[query[i]-1];
        ll y = Y[query[i]-1];
        ll ans = -INF;
        ans = max(ans, max_data[0] - x - y);
        ans = max(ans, max_data[1] - x + y);
        ans = max(ans, max_data[2] + x - y);
        ans = max(ans, max_data[3] + x + y);
        cout << ans << endl;
    }
}