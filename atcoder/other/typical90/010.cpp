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

ll N, i, c, p, Q, l, r;
vector<ll> c1, c2, L, R;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    c1.push_back(0);
    c2.push_back(0);
    REP(i, N) {
        cin >> c >> p;
        if (c == 1) {
            c1.push_back(c1[i] + p);
            c2.push_back(c2[i]);
        } else {
            c1.push_back(c1[i]);
            c2.push_back(c2[i] + p);
        }
    }
    cin >> Q;
    REP(i, Q) {
        cin >> l >> r;
        L.push_back(l - 1);
        R.push_back(r);
    }
    REP(i, Q) {
        l = L[i];
        r = R[i];
        cout << c1[r] - c1[l] << " " << c2[r] - c2[l] << endl;
    }
}