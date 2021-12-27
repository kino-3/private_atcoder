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

void debug_print() {
    cout << endl;
}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {
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
    for (const auto v: dict) {
        cout << v.first << ":" << v.second << ", ";
    }
    cout << endl;
}
template <typename T>
void print_set(const set<T> data) {
    for (const auto v: data) {
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
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {
    for (auto &&item : vec) {
        print_pair(item);
    }
}

const ll mod = 998244353;
ll N, K, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N >> K;
    ll ans = 0;

    // 0 を含むもの
    vector<ll> number;
    ll tmp_N = N;
    while (tmp_N > 0) {
        number.push_back(tmp_N % 10);
        tmp_N /= 10;
    }
    // example 7654321
    ll keta = number.size();
    ll total = 1; // keta - 1 桁以下
    REP(i, keta - 1) total *= 10;
    total -= 1;
    ll tmp_9 = 1;
    REP(i, keta - 1) {
        tmp_9 *= 9;
        total -= tmp_9;
    }
    ans += total;




    // 0 を含まないもの
    vector<map<ll, ll>> prod;
    map<ll, ll> tmp;
    FOR(i, 1, 10) tmp[i] = 1;
    prod.push_back(tmp);
    REP(i, 17) {
        auto prev = prod[i];
        map<ll, ll> tmp;
        FOR(j, 1, 10) {
            for (auto v : prev) {
                ll p = v.first * j;
                if (tmp.count(p) > 0) {
                    tmp[p] += v.second;
                } else {
                    tmp[p] = v.second;
                }
            }
        }
        prod.push_back(tmp);
    }

    ll ans_low = 0;
    REP(i, keta - 1) {
        for (auto v: prod[i]) {
            if (v.first <= K) ans_low += v.second;
        }
    }
    ans += ans_low;

    REP_R(i, keta) {
        debug_print(number[i]);
    }
    cout << ans << endl;
}