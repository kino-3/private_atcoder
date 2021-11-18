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
ll N, M, i, j, k, l;
vector<vector<ll>> A;
vector<ll> ranking, win;
string S;

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

    // N 行 M 列の行列の受け取り
    cin >> N >> M;
    REP(i, N * 2) {
        A.push_back(vector<ll>(0));
        cin >> S;
        REP(j, M) {
            if (S[j] == 'G') {
                A[i].push_back(0);
            } else if (S[j] == 'P') {
                A[i].push_back(1);
            } else {
                A[i].push_back(2);
            }
        }
        ranking.push_back(i);
        win.push_back(0);
    }

    REP(i, M) {
        REP(k, N) {
            ll man1 = ranking[2 * k];
            ll man2 = ranking[2 * k + 1];
            if ((A[man1][i] - A[man2][i] + 3) % 3 == 1) {
                win[man1]++;
            } else if ((A[man1][i] - A[man2][i] + 3) % 3 == 2) {
                win[man2]++;
            }
        }
        vector<pair<ll, ll>> win_idx;
        REP(j, 2 * N) { win_idx.push_back({-win[j], j}); }
        sort(ALL(win_idx));
        // REP(j, 2 * N) {
        //     cout << win_idx[j].first << ";" << win_idx[j].second << endl;
        // }
        REP(j, 2 * N) { ranking[j] = win_idx[j].second; }
        // print_v(ranking);
    }
    REP(i, 2 * N) { cout << ranking[i] + 1 << endl; }
}