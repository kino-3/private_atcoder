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

ll N, i, j, x, y;
vector<ll> X, Y;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> x >> y;
        X.push_back(x);
        Y.push_back(y);
    }

    double ans = 0;
    REP(i, N) {
        // j-i-k
        vector<double> angle;
        REP(j, N) {
            if (i == j) continue;
            // i-j
            angle.push_back(atan2(Y[j] - Y[i], X[j] - X[i]));
        }
        sort(ALL(angle));
        ll left = 0;
        ll right = 1;
        while (right < angle.size()) {
            double arg = angle[right] - angle[left];
            ans = max(ans, M_PI - abs(M_PI - arg));
            if (arg > M_PI) {
                left += 1;
            } else {
                right += 1;
            }
        }
    }
    cout << std::setprecision(15) << ans / M_PI * 180 << endl;
}