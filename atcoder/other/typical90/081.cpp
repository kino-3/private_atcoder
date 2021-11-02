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

ll L = 5000;
ll N, K, i, j, k, l;

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
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        print_v(item);
    }
    cout << "]" << endl;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    vector<vector<ll>> count(L + 1, vector<ll>(L + 1, 0));
    vector<vector<ll>> sum(L + 1, vector<ll>(L + 1, 0));
    REP(i, N) {
        cin >> j >> k;
        count[j][k]++;
    }
    REP(i, L) {
        REP(j, L) {
            sum[i + 1][j + 1] =
                count[i + 1][j + 1] + sum[i + 1][j] + sum[i][j + 1] - sum[i][j];
        }
    }
    // print_vv(sum);
    ll ans = 0;
    REP(i, L - K) {
        REP(j, L - K) {
            ll tmp = sum[i + K + 1][j + K + 1] - sum[i][j + K + 1] -
                     sum[i + K + 1][j] + sum[i][j];
            ans = max(ans, tmp);
        }
    }
    cout << ans << endl;
}