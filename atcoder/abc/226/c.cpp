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

ll N, i, j, k, l, f;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    vector<ll> cost(N);
    vector<vector<ll>> tech(N, vector<ll>(0));
    vector<ll> possible(N, false);
    stack<ll> stk;
    stk.push(N - 1);
    REP(i, N) {
        cin >> j >> k;
        cost[i] = j;
        REP(f, k) {
            cin >> l;
            tech[i].push_back(l - 1);
        }
    }
    ll ans = 0;
    while (!stk.empty()) {
        auto cnt = stk.top();
        stk.pop();
        if (possible[cnt]) continue;
        ans += cost[cnt];
        possible[cnt] = true;
        for (const auto v : tech[cnt]) {
            stk.push(v);
        }
    }
    cout << ans << endl;
}