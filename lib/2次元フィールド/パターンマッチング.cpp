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


// angle: 90, 180, 270 で回転した全領域を返す
template <typename T>
vector<vector<T>> rotate_field(vector<vector<T>> field, ll angle) {
    if (angle == 90) {
        ll C = field.size();
        ll R = field[0].size();
        vector<vector<T>> res(R, vector<T>(C));
        for (ll r = 0; r < R; r++) {
            for (ll c = 0; c < C; c++) {
                res[r][c] = field[c][R - r - 1];
            }
        }
        return res;
    } else if (angle == 180) {
        ll R = field.size();
        ll C = field[0].size();
        vector<vector<T>> res(R, vector<T>(C));
        for (ll r = 0; r < R; r++) {
            for (ll c = 0; c < C; c++) {
                res[r][c] = field[R - r - 1][C - c - 1];
            }
        }
        return res;
    } else if (angle == 270) {
        ll C = field.size();
        ll R = field[0].size();
        vector<vector<T>> res(R, vector<T>(C));
        for (ll r = 0; r < R; r++) {
            for (ll c = 0; c < C; c++) {
                res[r][c] = field[C - c - 1][r];
            }
        }
        return res;
    }
    assert(false);
}

// bounding box を返す
// return [row1, row2), [col1, col2)
template <typename T>
pair<pair<ll, ll>, pair<ll, ll>> get_bbox(vector<vector<T>> field) {
    T outside = false;
    vector<ll> rows;
    vector<ll> cols;
    ll R = field.size();
    ll C = field[0].size();
    vector<vector<T>> res(R, vector<T>(C));
    for (ll r = 0; r < R; r++) {
        for (ll c = 0; c < C; c++) {
            if (field[r][c] != outside) {
                rows.push_back(r);
                break;
            }
        }
    }
    for (ll c = 0; c < C; c++) {
        for (ll r = 0; r < R; r++) {
            if (field[r][c] != outside) {
                cols.push_back(c);
                break;
            }
        }
    }
    sort(rows.begin(), rows.end());
    sort(cols.begin(), cols.end());
    return {{rows[0], rows[rows.size() - 1] + 1},
            {cols[0], cols[cols.size() - 1] + 1}};
}

// field を [row1, row2), [col1, col2) で切り取った長方形領域を返す。
template <typename T>
vector<vector<T>> clip(vector<vector<T>> field,
                       pair<pair<ll, ll>, pair<ll, ll>> box) {
    ll R = box.first.second - box.first.first;
    ll C = box.second.second - box.second.first;
    vector<vector<T>> res(R, vector<T>(C));
    for (ll r = 0; r < R; r++) {
        for (ll c = 0; c < C; c++) {
            res[r][c] = field[r + box.first.first][c + box.second.first];
        }
    }
    return res;
}

const ll mod = 998244353;
ll N, M, i, j, k, l;
string S;
vector<vector<bool>> A;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;

    A.resize(N);
    REP(i, N) {
        cin >> S;
        REP(j, M) { A[i].push_back(S[j] == '#'); }
    }
    // print_vv(A);
    // print_vv(rotate_field(A, 90));
    // print_vv(rotate_field(A, 180));
    // print_vv(rotate_field(A, 270));

    // print_vv(clip(A, get_bbox(A)));
}