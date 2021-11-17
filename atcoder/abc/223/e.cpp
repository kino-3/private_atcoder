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

template <typename T>
void debug_print(const T item) {
    cout << item << endl;
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
}

ll mod = 1000000007;
ll X, Y, A, B, C;

bool check(ll i, ll j, ll k) {
    ll ix = (i - 1) / X + 1;
    ll jx = (j - 1) / X + 1;
    ll kx = (k - 1) / X + 1;
    ll iy = (i - 1) / Y + 1;
    ll jy = (j - 1) / Y + 1;
    ll ky = (k - 1) / Y + 1;
    if (ix + jx + kx <= Y) return true;
    if (iy + jy + ky <= X) return true;
    if (X - iy > 0) {
        ll jx2 = (j - 1) / (X - iy) + 1;
        ll kx2 = (k - 1) / (X - iy) + 1;
        if (jx2 + kx2 <= Y) return true;
    }
    if (Y - ix > 0) {
        ll jy2 = (j - 1) / (Y - ix) + 1;
        ll ky2 = (k - 1) / (Y - ix) + 1;
        if (jy2 + ky2 <= X) return true;
    }

    return false;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> X >> Y >> A >> B >> C;
    bool ans = false;

    ans = ans || check(A, B, C);
    // debug_print(ans);
    ans = ans || check(A, C, B);
    // debug_print(ans);
    ans = ans || check(B, A, C);
    // debug_print(ans);
    ans = ans || check(B, C, A);
    // debug_print(ans);
    ans = ans || check(C, B, A);
    // debug_print(ans);
    ans = ans || check(C, A, B);

    if (ans) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}