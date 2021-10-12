#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
#define ALL(c) std::begin(c), std::end(c)

using namespace std;
using ull = unsigned long long;

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));
int N;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;

    ull i;
    REP(i, 1 << N) {
        // 0 が (
        std::bitset<20> bs(i);
        int j;
        int left = 0;
        bool flg = true;
        REP_R(j, N) {
            if (bs[j]) {
                left -= 1;
                if (left < 0) {
                    flg = false;
                    continue;
                }
            } else {
                left += 1;
            }
        }
        if (!flg || left > 0) continue;
        REP_R(j, N) {
            if (bs[j]) {
                cout << ")";
            } else {
                cout << "(";
            }
        }
        cout << endl;
    }
}