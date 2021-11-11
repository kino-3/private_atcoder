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
ll T, i, j, k, l;
vector<vector<ll>> A, B;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

void task(ll i, ll w, ll p) {
    // w + 1 の重さの荷物を p + 1 の人に持たせる
    if (w < p) {
        ll count = min(A[i][w], B[i][p]);
        A[i][w] -= count;
        B[i][p] -= count;
        B[i][p - w - 1] += count;
    }
    if (w == p) {
        ll count = min(A[i][w], B[i][w]);
        A[i][w] -= count;
        B[i][w] -= count;
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> T;
    REP(i, T) {
        A.push_back(vector<ll>(0));
        B.push_back(vector<ll>(0));
        REP(j, 5) {
            cin >> k;
            A[i].push_back(k);
        }
        REP(j, 5) {
            cin >> k;
            B[i].push_back(k);
        }
    }
    REP(i, T) {
        task(i, 4, 4);
        task(i, 3, 3);
        task(i, 3, 4);
        task(i, 2, 2);
        task(i, 2, 4);  // point はここの
        task(i, 2, 3);  // 2 つの順番
        task(i, 1, 4);
        task(i, 1, 3);
        task(i, 1, 2);
        task(i, 1, 1);
        task(i, 0, 4);
        task(i, 0, 3);
        task(i, 0, 2);
        task(i, 0, 1);
        task(i, 0, 0);
        bool poss = true;
        REP(j, 5) {
            if (A[i][j] > 0) poss = false;
        }
        if (poss) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}