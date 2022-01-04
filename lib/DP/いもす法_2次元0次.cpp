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

class Imos {
   public:
    ll H;
    ll W;
    vector<vector<ll>> field;

    Imos(ll h, ll w) : H(h), W(w), field(h + 1, vector<ll>(w + 1, 0)) {}

    // 左上(pos1), 右下(pos2) に一様加算(全て閉区間)
    void add(pair<ll, ll> pos1, pair<ll, ll> pos2, ll value) {
        field[pos1.first][pos1.second] += value;
        field[pos2.first + 1][pos1.second] -= value;
        field[pos1.first][pos2.second + 1] -= value;
        field[pos2.first + 1][pos2.second + 1] += value;
    }

    void exec() {
        FOR(i, 1, H + 1) {
            REP(j, W + 1) { field[i][j] += field[i - 1][j]; }
        }
        REP(i, H + 1) {
            FOR(j, 1, W + 1) { field[i][j] += field[i][j - 1]; }
        }
    }
};

const ll mod = 998244353;  // 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    Imos imos = Imos(5, 5);
    imos.add({0, 0}, {3, 3}, 5);
    imos.add({2, 3}, {4, 4}, 10);
    imos.exec();
    // print_vv(imos.field);
}