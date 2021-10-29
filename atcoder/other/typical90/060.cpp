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

ll N, i, j, k;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }
    // 長さ i の増加列の末尾の値
    vector<ll> dpl;
    vector<ll> dp;
    dp.push_back(A[0]);
    dpl.push_back(1);
    FOR(i, 1, N) {
        ll idx = distance(dp.begin(), lower_bound(ALL(dp), A[i]));
        if (idx == dp.size()) {
            dp.push_back(A[i]);
        } else {
            A[idx] = A[i];
        }
        dpl.push_back(idx + 1);
    }
    //
    reverse(ALL(A));
    dp.clear();
    vector<ll> dpr;
    dp.push_back(A[0]);
    dpr.push_back(1);
    FOR(i, 1, N) {
        ll idx = distance(dp.begin(), lower_bound(ALL(dp), A[i]));
        if (idx == dp.size()) {
            dp.push_back(A[i]);
        } else {
            A[idx] = A[i];
        }
        dpr.push_back(idx + 1);
    }
    reverse(ALL(dpr));

    ll ans = 1;
    REP(i, N) {
        // i が頂点
        // cout << i << ": " << dpl[i] << "," << dpr[i] << endl;
        ans = max(ans, dpl[i] + dpr[i] - 1);
    }
    cout << ans << endl;
}