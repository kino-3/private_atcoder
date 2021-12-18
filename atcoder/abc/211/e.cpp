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

void debug_print() { cout << endl; }
template <class Head, class... Tail>
void debug_print(Head &&head, Tail &&...tail) {
    std::cout << head << ", ";
    debug_print(std::forward<Tail>(tail)...);
}
ll DEBUG_PRINT_COUNT = 0;
void debug_print_count() {
    cout << "debug: " << DEBUG_PRINT_COUNT << endl;
    DEBUG_PRINT_COUNT++;
    assert(DEBUG_PRINT_COUNT < 10);
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
template <typename K, typename V>
void print_map(const map<K, V> dict) {
    for (const auto v : dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v : data) {
        cout << v << ", ";
    }
    cout << endl;
}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {
    cout << "(" << data.first << "," << data.second << ")";
    // cout << endl;
}
template <typename T>
void print_sp(const set<T> data) {
    for (const auto v : data) {
        print_pair(v);
    }
    cout << endl;
}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {
    cout << "(";
    cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
    cout << ")";
    // cout << endl;
}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
}

const ll mod = 998244353;
ll N, K, i, j, k, l;
string S;
vector<vector<bool>> A;
vector<pair<ll, ll>> direction = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool is_field(pair<ll, ll> pos) {
    if (pos.first < 0) return false;
    if (pos.first >= N) return false;
    if (pos.second < 0) return false;
    if (pos.second >= N) return false;
    return A[pos.first][pos.second];
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;

    A.resize(N);

    REP(i, N) {
        cin >> S;
        REP(j, N) { A[i].push_back(S[j] == '.'); }
    }

    // K マスのつながり
    set<set<pair<ll, ll>>> data;
    set<pair<ll, ll>> tmp;
    tmp.insert({0, 0});
    data.insert(tmp);
    pair<ll, ll> base = {0, 0};
    REP(i, K - 1) {
        set<set<pair<ll, ll>>> new_data;
        for (auto v : data) {
            for (auto vv : v) {
                for (auto d : direction) {
                    pair<ll, ll> cnt = {d.first + vv.first,
                                        d.second + vv.second};
                    if (base < cnt) continue;
                    if (v.count(cnt) == 0) {
                        auto newv = v;
                        newv.insert(cnt);
                        new_data.insert(newv);
                    }
                }
            }
        }
        data = new_data;
    }
    // debug_print(data.size());
    // for (auto v : data) {
    //     print_sp(v);
    // }

    ll ans = 0;
    REP(i, N) {
        REP(j, N) {
            for (auto v : data) {
                bool flg = true;
                for (auto vv: v) {
                    pair<ll, ll> cnt = {i + vv.first, j + vv.second};
                    if (!is_field(cnt)) flg = false;
                }
                if (flg) ans ++;
            }
        }
    }
    cout << ans << endl;
}