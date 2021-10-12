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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    ll N, L, K;
    vector<ll> A;
    A.push_back(0);
    cin >> N >> L;
    cin >> K;
    ll idx;
    REP(idx, N) {
        ll a;
        cin >> a;
        A.push_back(a);
    }

    //
    A.push_back(L);
    vector<ll> div;
    REP(idx, N+1) { div.push_back(A[idx + 1] - A[idx]); }
    ll maxL = L / (K + 1) + 1;

    ll ub = maxL;
    ll lb = 1;
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;
        ll tmp = 0;
        ll cut = 0;
        for (const auto &a : div) {
            tmp += a;
            if (tmp >= mid) {
                tmp = 0;
                cut += 1;
                if (cut > K) {  // 末尾でも切る
                    break;
                }
            }
        }
        if (cut > K) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    cout << lb << endl;
}