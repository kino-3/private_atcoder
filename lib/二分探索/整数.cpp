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


const ll mod = 998244353;
ll N, i, j, k, l;
vector<ll> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    REP(i, N) { cin >> A[i]; }

    // 二分探索は lb, ub の前提条件(条件を満たす or not)
    // と range error に注意する必要がある

    // 条件を満たす最大値を求める
    ll lb = 0;  // これは条件を満たす必要がある
    ll ub = N;  // これは条件を満たさない必要がある
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;  // mid は ub の初期値にはならない
        if (cond(mid)) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    cout << lb << endl;

    // 条件を満たす最小値を求める
    ll lb = -1;     // これは条件を満たさない必要がある
    ll ub = N - 1;  // これは条件を満たす必要がある
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;  // mid は lb の初期値にはならない
        if (cond(mid)) {
            ub = mid;
        } else {
            lb = mid;
        }
    }
    cout << ub << endl;

    // 条件を満たす値を求めるために範囲を狭めていく
    ll lb = 0;  // 左端
    ll ub = 10000;  // 右端
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;
        if (cond) { // mid は左端側?
            lb = mid;
        } else {
            ub = mid;
        }
    }
    // ub と lb の間(両端含む)
}