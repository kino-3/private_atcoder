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
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {
    cout << "(";
    cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
    cout << ")";
    // cout << endl;
}

const ll mod = 998244353;
ll K, i, j, k, l;
string S;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> S;
    cin >> K;
    vector<pair<ll, ll>> pos;
    pair<ll, ll> cnt = {0, 0};
    pos.push_back(cnt);
    REP(i, S.size()) {
        if (S[i] == 'L') cnt.first--;
        if (S[i] == 'R') cnt.first++;
        if (S[i] == 'U') cnt.second--;
        if (S[i] == 'D') cnt.second++;
        pos.push_back(cnt);
    }
    ll dx = cnt.first;
    ll dy = cnt.second;

    if (dx == 0 && dy == 0) {
        set<pair<ll, ll>> ans;
        for (const auto v : pos) {
            ans.insert(v);
        }
        cout << ans.size() << endl;
        return 0;
    }

    if (dx == 0) {
        swap(dx, dy);
        for (auto &v : pos) {
            swap(v.first, v.second);
        }
    }

    if (dx < 0) {
        dx *= -1;
        for (auto &v : pos) {
            v.first *= -1;
        }
    }

    map<pair<ll, ll>, vector<ll>> data;
    for (const auto v : pos) {
        ll shift = (v.first + (1000000 * dx)) / dx - 1000000;
        pair<ll, ll> key = {v.first - shift * dx, v.second - shift * dy};
        data[key].push_back(shift);
    }

    // for (auto v : data) {
    //     print_pair(v.first);
    //     print_v(v.second);
    // }
    ll ans = 0;
    for (auto v : data) {
        auto vec = v.second;
        sort(ALL(vec));
        REP(i, vec.size()-1){
            ans += min(K, vec[i+1]-vec[i]);
        }
        ans += K;
    }
    cout << ans << endl;
}