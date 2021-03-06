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
vector<ll> W, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j;
        W.push_back(j);
    }
    REP(i, N) {
        cin >> j;
        B.push_back(j);
    }
    unsigned int total_grundy = 0;

    ll white = 50;
    ll blue = 50;
    ll max_blue = blue + white * (white + 1) / 2;
    vector<vector<unsigned>> grundy(white + 1, vector<unsigned>(max_blue + 1));
    for (ll w = 0; w <= white; w++) {
        // b < 2
        if (w == 0) {
            grundy[0][0] = 0;
            grundy[0][1] = 0;
        } else {
            grundy[w][0] = grundy[w - 1][w] == 0 ? 1 : 0;
            grundy[w][1] = grundy[w - 1][w + 1] == 0 ? 1 : 0;
        }
        // b >= 2
        for (ll b = 2; b <= max_blue; b++) {
            set<unsigned> g;
            for (ll bb = (b + 1) / 2; bb < b; bb++) {
                g.insert(grundy[w][bb]);
            }
            if (w > 0) {
                g.insert(grundy[w - 1][w + b]);
            }
            ll c = 0;
            while (true) {
                if (g.count(c) == 0) {
                    break;
                }
                c++;
            }
            grundy[w][b] = unsigned(c);
        }
        max_blue -= (w + 1);
    }

    REP(i, N) {
        ll blue = B[i];
        ll white = W[i];
        total_grundy ^= grundy[white][blue];
    }
    if (total_grundy == 0) {
        cout << "Second" << endl;
    } else {
        cout << "First" << endl;
    }
}