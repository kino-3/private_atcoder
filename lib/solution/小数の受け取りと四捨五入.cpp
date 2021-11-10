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

ll N, i;
string S;
double d;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    // 方法1: 文字列として受け取り
    cin >> S;
    ll under_dot;     // 小数点以下の桁数
    ll gauss = 0;     // 整数部分
    bool flg = true;  // 整数部分を調べている
    REP(i, S.size()) {
        if (S[i] == '.') {  // 小数点
            under_dot = S.size() - i + 1;
            flg = false;
        } else if (flg) {  // 整数部分
            gauss *= 10;
            gauss += S[i] - '0';
        } else {  // 小数部分
            if (S[i] - '0' < 5) {
                cout << gauss << endl;
            } else {
                cout << gauss + 1 << endl;
            }
            break;
        }
    }

    // 方法2: 浮動小数として受け取り
    cin >> d;
    double eps = 0.0000005;
    cout << ll(d + 0.5 + eps) << endl;
}