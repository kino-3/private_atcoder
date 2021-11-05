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
vector<vector<ll>> memo;

ll dfs(ll left, ll right) {
    if (memo[left][right] >= 0) {
        return memo[left][right];
    }
    if (right - left == 1) {
        memo[left][right] = abs(A[left] - A[right]);
        return memo[left][right];
    }
    ll ans = abs(A[left] - A[right]) + dfs(left + 1, right - 1);
    // cout << ans << endl;
    // cout << left << " " << right << endl;
    ll mid = left + 1;
    while (mid < right) {
        ans = min(ans, dfs(left, mid) + dfs(mid+1, right));
        mid += 2;
    }
    memo[left][right] = ans;
    return ans;
};

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, 2 * N) {
        cin >> j;
        A.push_back(j);
        memo.push_back(vector<ll>(2 * N, -1));
    }
    ll ans = 0;
    cout << dfs(0, 2 * N - 1) << endl;
}