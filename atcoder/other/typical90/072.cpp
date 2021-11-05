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
ll H, W, i, j, k, l, ei, ej;
string str;
vector<vector<bool>> field;
vector<vector<bool>> checked;
ll ans = -1;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

template <typename T>
void print_vv(const vector<T> vec) {
    for (auto &&item : vec) {
        print_v(item);
    }
}

void dfs(ll i, ll j, ll count = -1) {
    if (count < 0) {
        checked = vector<vector<bool>>(H, vector<bool>(W, false));
        checked[i][j] = true;
        count = 1;
    }
    // print_vv(checked);
    ll ii, jj;
    ii = i - 1;
    jj = j;
    if (ii == ei && jj == ej) ans = max(ans, count);
    if (ii >= 0 && !checked[ii][jj] && field[ii][jj]) {
        checked[ii][jj] = true;
        count++;
        dfs(ii, jj, count);
    }
    ii = i + 1;
    jj = j;
    if (ii == ei && jj == ej) ans = max(ans, count);
    if (ii < H && !checked[ii][jj] && field[ii][jj]) {
        checked[ii][jj] = true;
        count++;
        dfs(ii, jj, count);
    }
    ii = i;
    jj = j - 1;
    if (ii == ei && jj == ej) ans = max(ans, count);
    if (jj >= 0 && !checked[ii][jj] && field[ii][jj]) {
        checked[ii][jj] = true;
        count++;
        dfs(ii, jj, count);
    }
    ii = i;
    jj = j + 1;
    if (ii == ei && jj == ej) ans = max(ans, count);
    if (jj < W && !checked[ii][jj] && field[ii][jj]) {
        checked[ii][jj] = true;
        count++;
        dfs(ii, jj, count);
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> H >> W;
    REP(i, H) {
        cin >> str;
        field.push_back(vector<bool>(W, true));
        REP(j, W) {
            if (str[j] == '#') {
                field[i][j] = false;
            }
        }
    }
    REP(i, H) {
        REP(j, W) {
            if (!field[i][j]) continue;
            ei = i;
            ej = j;
            dfs(i, j);
        }
    }
    cout << (ans < 4 ? -1 : ans) << endl;
}