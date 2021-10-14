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
void print_v(const vector<T> vec) {
    cout << "size: " << vec.size() << endl;
    cout << "[";
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

ll N, B, K;
vector<int> c_list;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> B >> K;
    int i, j;
    REP(i, K) {
        cin >> j;
        c_list.push_back(j);
    }

    // ll amari = 1;
    // ll cycle = 1;
    // vector<ll> amari_list(B, 0);  // 10 ^ n % B で取りうる各余りの回数
    // while (true) {
    //     amari = amari * 10 % B;
    //     if (amari == 1 || amari == 0) {
    //         break;
    //     }
    //     cycle += 1;
    // }
    // if (amari == 0) {
    //     // 1000...000 は B で割り切れる
    //     amari = 1;
    //     if (cycle < N) {
    //         amari_list[0] = N - cycle;
    //     }
    //     for (int i = 0; i < min(cycle, N); i++) {
    //         amari_list[amari] += 1;
    //         amari = amari * 10 % B;
    //     }
    // } else if (amari == 1) {
    //     amari = 1;
    //     for (int i = 0; i < cycle; i++) {
    //         amari_list[amari] += N / cycle;
    //         amari = amari * 10 % B;
    //     }
    //     amari = 1;
    //     for (int i = 0; i < N % cycle; i++) {
    //         amari_list[amari] += 1;
    //         amari = amari * 10 % B;
    //     }
    // } else {
    //     amari = 1;
    //     for (int i = 0; i < N; i++) {
    //         amari_list[amari] += N / cycle;
    //         amari = amari * 10 % B;
    //     }
    // }

    // vector<ll> amari_list_c(B, 0);  // (c * 10 ^ n) % B で取りうる各余りの回数

    // for (const auto& c : c_list) {
    //     for (int i = 0; i < B; i++) {
    //         amari_list_c[(i * c) % B] += amari_list[i];
    //     }
    // }

    // vector<vector<ll>> trans(B, vector<ll>(B, 0));
    // ll before;
    // REP(before, B) {
    //     REP(amari, B) {
    //         ll after = before * amari % B;
    //         trans[after][before] += amari_list_c[amari];
    //     }
    // }
}