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
ll N, Q, i, j, k, l;
vector<ll> A;
vector<vector<bool>> bad_pair;
vector<bool> possible(8889);
vector<vector<bool>> cards(8889);
bool end_flag = false;

template <typename T>
vector<T> deep_copy_1d(const vector<T> vec) {
    vector<T> tmp(vec.size());
    for (const auto &item : vec) {
        tmp.push_back(item);
    }
    return vec;
}

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

void search(vector<bool> selected = vector<bool>(N, false), ll idx = 0) {
    if (end_flag) return;
    if (idx == N) {
        ll ans = 0;
        REP(i, N) {
            if (selected[i]) {
                ans += A[i];
            }
        }
        // cout << ans << endl;
        // print_v(selected);
        if (ans <= 8888 && possible[ans]) {
            vector<ll> a1, a2;
            REP(i, N) {
                if (selected[i]) a1.push_back(i + 1);
                if (cards[ans][i]) a2.push_back(i + 1);
            }
            cout << a1.size() << endl;
            REP(i, a1.size()) {
                cout << a1[i];
                if (i < a1.size() - 1) {
                    cout << " ";
                } else {
                    cout << endl;
                }
            }
            cout << a2.size() << endl;
            REP(i, a2.size()) {
                cout << a2[i];
                if (i < a2.size() - 1) {
                    cout << " ";
                } else {
                    cout << endl;
                }
            }
            end_flag = true;
        } else if (ans <= 8888) {
            possible[ans] = true;
            cards[ans] = deep_copy_1d(selected);
        }
    } else {
        // idx 番目を入れない
        selected[idx] = false;
        search(deep_copy_1d(selected), idx + 1);
        // i番目を入れる
        bool flg = true;
        REP(i, idx) {
            if (bad_pair[i][idx] && selected[i]) flg = false;
        }
        if (flg) {
            selected[idx] = true;
            search(deep_copy_1d(selected), idx + 1);
        }
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> Q;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
        bad_pair.push_back(vector<bool>(N, false));
    }
    REP(i, Q) {
        cin >> j >> k;
        bad_pair[j - 1][k - 1] = true;
        bad_pair[k - 1][j - 1] = true;
    }

    search();
}