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

ll N, sup;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    cin >> sup;  // これをビット表記したときの全探索
    ll sub = sup;
    do {  // 辞書と逆順にループ
        std::bitset<100> bs(sub);
        ll j;
        // 上位桁からループ
        REP_R(j, N) {
            if (bs[j]) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
        cout << endl;
        sub = (sub - 1) & sup;  // see. 蟻本 p.144
    } while (sub != sup);

    do {  // 辞書順にループ
        std::bitset<100> bs(sup - sub); // 違いはここだけ
        ll j;
        // 上位桁からループ
        REP_R(j, N) {
            if (bs[j]) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
        cout << endl;
        sub = (sub - 1) & sup;  // see. 蟻本 p.144
    } while (sub != sup);
}