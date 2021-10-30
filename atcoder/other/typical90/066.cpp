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
vector<ll> L, R;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j >> k;
        L.push_back(j);
        R.push_back(k);
    }
    double ans = 0;
    REP(i, N - 1) {
        FOR(j, i + 1, N) {
            double size = (R[i] - L[i] + 1) * (R[j] - L[j] + 1);
            if (R[i] < L[j]) {
                ans += 0.0;
                // cout << i << j << ","
                //      << "1: 0" << endl;
            } else if (L[i] > R[j]) {
                ans += 1.0;
                // cout << i << j << ","
                //      << "2: 1" << endl;
            } else if (R[i] <= R[j] && L[i] <= L[j]) {
                ans += double((R[i] - L[j] + 1) * (R[i] - L[j]) / 2) / size;
                // cout << i << j << ","
                //      << "3: " << double((R[i] - L[j] + 1) * (R[i] - L[j]) /
                //      2)
                //      << endl;
            } else if (R[j] <= R[i] && L[j] <= L[i]) {
                ans += 1 -
                       double((R[j] - L[i] + 1) * (R[j] - L[i] + 2) / 2) / size;
                // cout << i << j << ","
                //      << "4: "
                //      << size - double((R[j] - L[i] + 1) * (R[j] - L[i] + 2) /
                //      2)
                //      << endl;
            } else if (R[j] <= R[i] && L[i] <= L[j]) {
                double count = (R[i] - R[j]) * (R[j] - L[j] + 1);
                count += (R[j] - L[j] + 1) * (R[j] - L[j]) / 2;
                ans += count / size;
                // cout << i << j << ","
                //      << "5: " << count << endl;
            } else {
                double count = (L[i] - L[j]) * (R[i] - L[i] + 1);
                count += (R[i] - L[i] + 1) * (R[i] - L[i]) / 2;
                ans += count / size;
                // cout << i << j << ","
                //      << "6: " << count << endl;
            }
        }
    }
    cout << setprecision(15) << ans << endl;
}