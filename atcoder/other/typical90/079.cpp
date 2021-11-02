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
ll H, W, i, j, k, l;
vector<vector<ll>> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W;
    REP(i, H) {
        A.push_back(vector<ll>(0));
        REP(j, W) {
            cin >> k;
            A[i].push_back(k);
        }
    }
    REP(i, H) {
        B.push_back(vector<ll>(0));
        REP(j, W) {
            cin >> k;
            B[i].push_back(k);
        }
    }
    ll count = 0;
    REP(i, H - 1) {
        REP(j, W - 1) {
            k = B[i][j] - A[i][j];
            A[i][j] += k;
            A[i + 1][j] += k;
            A[i][j + 1] += k;
            A[i + 1][j + 1] += k;
            count += abs(k);
        }
    }
    bool flg = true;
    REP(i, H) {
        REP(j, W) {
            if (A[i][j] != B[i][j]) flg = false;
        }
    }
    if (flg) {
        cout << "Yes" << endl;
        cout << count << endl;
    } else {
        cout << "No" << endl;
    }
}