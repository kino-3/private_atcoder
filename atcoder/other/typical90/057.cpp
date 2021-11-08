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

// x^n % mod を返す
ll mod_pow(ll x, ll n, ll mod = 998244353) {
    ll res = 1;
    while (n > 0) {
        if (n & 1) {
            res = res * x % mod;
        }
        x = x * x % mod;
        n >>= 1;
    }
    return res;
}

ll N, M, i, j, k, l;

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

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> M;
    // matrix[i][j]について i: ボタン, j: パネル
    vector<vector<bool>> matrix(N, vector<bool>(M, false));
    vector<ll> target(M, false);
    REP(i, N) {
        cin >> k;
        REP(j, k) {
            cin >> l;
            matrix[i][l - 1] = true;
        }
    }
    REP(i, M) {
        cin >> j;
        target[i] = (j == 1);
    }
    // print_v(target);
    // print_vv(matrix);

    // mod 2 の掃き出し
    ll idx = 0;
    REP(i, M) {
        FOR(j, idx, N) {
            if (matrix[j][i]) {
                swap(matrix[j], matrix[idx]);
                break;
            }
        }
        REP(j, N) {
            if (j == idx) continue;
            if (matrix[j][i]) {
                REP(k, M) { matrix[j][k] = !(matrix[j][k] == matrix[idx][k]); }
            }
        }
        idx++;
        // print_vv(matrix);
        if (idx == N) {
            break;
        }
    }
    // idx 行目以降は 全部 0
    vector<ll> tmp(M, false);
    ll tmp_idx = 0;
    REP(i, M) {
        if (tmp[i] != target[i]) {
            while (tmp_idx < idx) {
                if (matrix[tmp_idx][i]) {
                    REP(j, M) { tmp[j] = !(tmp[j] == matrix[tmp_idx][j]); }
                    break;
                } else {
                    tmp_idx++;
                }
            }
            if (tmp_idx == idx) {
                cout << 0 << endl;
                return 0;
            }
        }
    }
    cout << mod_pow(2, N - idx) << endl;
}