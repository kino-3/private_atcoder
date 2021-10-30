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

ll N, K, i, j;

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

    cin >> N >> K;
    ll pow;
    REP(i, K) {
        ll tmp_N = 0;
        pow = 1;
        while (N > 0) {
            tmp_N += pow * (N % 10);
            N /= 10;
            pow *= 8;
        }
        N = tmp_N;
        vector<int> tmp;
        while (N > 0) {
            tmp.push_back(N % 9 != 8 ? N % 9 : 5);
            N /= 9;
        }
        // print_v(tmp);
        pow = 1;
        REP(j, tmp.size()) {
            N += tmp[j] * pow;
            pow *= 10;
        }
    }
    cout << N << endl;
}