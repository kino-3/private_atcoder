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

ll N, Q, i, j, k, l, r, v;
vector<ll> A, L, R, V, E;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> Q;
    REP(i, N) {
        cin >> j;
        A.push_back(j);
    }
    REP(i, Q) {
        cin >> j >> k >> l;
        L.push_back(j);
        R.push_back(k);
        V.push_back(l);
    }

    ll ans = 0;
    REP(i, N - 1) {
        ll j = A[i + 1] - A[i];
        ans += abs(j);
        E.push_back(j);
    }
    REP(i, Q) {
        l = L[i];
        r = R[i];
        v = V[i];
        if (l > 1) {
            ans -= abs(E[l - 2]);
            E[l - 2] += v;
            ans += abs(E[l - 2]);
        }
        if (r < N) {
            ans -= abs(E[r - 1]);
            E[r - 1] -= v;
            ans += abs(E[r - 1]);
        }
        cout << ans << endl;
        // print_v(E);
    }
}