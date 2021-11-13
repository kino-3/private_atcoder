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
ll N, i, j, k, l;
vector<ll> X, Y, idx;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    REP(i, N) {
        cin >> j >> k;
        X.push_back(j);
        Y.push_back(k);
        idx.push_back(i);
    }
    sort(idx.begin(), idx.end(), [](const ll& l, const ll& r) {
        return (X[l] - 1) * Y[r] - (X[r] - 1) * Y[l] > 0;
    });
    ll counter = 1;
    ll prev = 0;
    ll tmp = 1;
    while (tmp < N) {
        ll prev_idx = idx[prev];
        ll tmp_idx = idx[tmp];
        if (((Y[tmp_idx] - 1) * (X[prev_idx] - 1) - Y[prev_idx] * X[tmp_idx]) >=
            0) {
            prev = tmp;
            counter++;
        }
        tmp++;
    }
    cout << counter << endl;
}