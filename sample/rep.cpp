#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)

using namespace std;

int main() {
    REP(idx, 3) { cout << idx; }  // 012
    cout << endl;
    REP_R(idx, 3) { cout << idx; }  // 210
    cout << endl;
    FOR(idx, 4, 7) { cout << idx; }  // 456
    cout << endl;
    FOR_R(idx, 4, 7) { cout << idx; }  // 654
    cout << endl;
}