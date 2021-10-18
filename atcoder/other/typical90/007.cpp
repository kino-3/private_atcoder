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

ll N, Q, i, j;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }
    cin >> Q;
    REP(i, Q) {
        cin >> j;
        B.push_back(j);
    }

    sort(ALL(A));
    vector<ll> mid;
    REP(i, N - 1) { mid.push_back((A[i] + A[i + 1]) / 2); }
    mid.push_back(1000000001);
    REP(i, Q) {
        ll idx = distance(mid.begin(), lower_bound(ALL(mid), B[i]));
        cout << abs(A[idx] - B[i]) << endl;
    }
}