#include <bits/stdc++.h>
#define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
#define REP_R(var, n) \
    for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
#define FOR(var, a, b) for (auto var = (a); var < (b); var++)
#define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
#define ALL(c) std::begin(c), std::end(c)

using namespace std;
using ll = long long;
// using state = tuple<ll, ll, ll, ll, ll, ll, ll, ll, ll>;

// REP(idx, 3) { cout << idx; }  // 012
// REP_R(idx, 3) { cout << idx; }  // 210
// FOR(idx, 4, 7) { cout << idx; }  // 456
// FOR_R(idx, 4, 7) { cout << idx; }  // 654
// sort(ALL(v));

ll mod = 1000000007;
ll N, i, j, k, l;
vector<vector<ll>> G(9, vector<ll>(0));
bool checked[9][9][9][9][9][9][9][9];  // 各コマの位置

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

    cin >> N;
    REP(i, N) {
        cin >> j >> k;
        G[j - 1].push_back(k - 1);
        G[k - 1].push_back(j - 1);
    }

    vector<ll> v;  // こま idx の場所
    REP(i, 8) {
        cin >> j;
        v.push_back(j - 1);
    }

    checked[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]][v[6]][v[7]] = true;
    queue<pair<ll, vector<ll>>> que;  // 手数, それぞれのコマの位置
    que.push({0, v});
    while (!que.empty()) {
        auto v = que.front();
        que.pop();
        bool complete = true;
        REP(i, 8) {
            if (v.second[i] != i) {
                complete = false;
            }
        }
        if (complete) {
            cout << v.first << endl;
            return 0;
        }
        // v からいけるところ
        vector<ll> masu = v.second;
        vector<ll> koma(9, -1);
        REP(i, 8) { koma[masu[i]] = i; }
        ll void_masu;
        REP(i, 9) {
            if (koma[i] == -1) void_masu = i;
        }

        for (const auto new_masu : G[void_masu]) {
            ll new_koma = koma[new_masu];
            vector<ll> nv = deep_copy_1d(v.second);
            nv[new_koma] = void_masu;
            if (!checked[nv[0]][nv[1]][nv[2]][nv[3]][nv[4]][nv[5]][nv[6]]
                        [nv[7]]) {
                que.push({v.first + 1, nv});
                checked[nv[0]][nv[1]][nv[2]][nv[3]][nv[4]][nv[5]][nv[6]]
                       [nv[7]] = true;
            }
        }
    }
    cout << -1 << endl;
}