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

ll T, L, X, Y, Q, i, j;
vector<ll> E;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> T >> L >> X >> Y >> Q;
    REP(i, Q) {
        cin >> j;
        E.push_back(j);
    }
    REP(i, Q) {
        double rad = 2 * M_PI * E[i] / T;
        double y = -sin(rad) * L * 0.5;
        double z = (1 - cos(rad)) * L * 0.5;
        double dist = sqrt(X * X + (y - Y) * (y - Y));
        rad = atan2(z, dist);
        cout << std::setprecision(15) << rad / M_PI * 180 << endl;
    }
}