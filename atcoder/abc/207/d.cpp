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
ll N, M, i, j, k, l;
vector<pair<ll, ll>> P, Q;

ll dist(pair<ll, ll> n1, pair<ll, ll> n2) {
    ll dx = n1.first - n2.first;
    ll dy = n1.second - n2.second;
    return dx * dx + dy * dy;
}

ll prod(pair<ll, ll> n0, pair<ll, ll> n1, pair<ll, ll> n2) {
    ll dx1 = n1.first - n0.first;
    ll dy1 = n1.second - n0.second;
    ll dx2 = n2.first - n0.first;
    ll dy2 = n2.second - n0.second;
    return dx1 * dy2 - dx2 * dy1;
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    P.resize(N);
    REP(i, N) { cin >> P[i].first >> P[i].second; }
    Q.resize(N);
    REP(i, N) { cin >> Q[i].first >> Q[i].second; }

    if (N == 1) {
        cout << "Yes" << endl;
        return 0;
    }

    ll d = dist(P[0], P[1]);

    REP(i, N) {
        REP(j, N) {
            if (dist(Q[i], Q[j]) != d) continue;
            bool possible_flg = true;
            FOR(k, 2, N) {
                // P[k] に一致する頂点があるか ?
                bool exist = false;
                ll dist_p0k = dist(P[0], P[k]);
                ll dist_p1k = dist(P[1], P[k]);
                ll prod_p = prod(P[0], P[1], P[k]);
                REP(l, N) {
                    if (dist(Q[i], Q[l]) != dist_p0k) continue;
                    if (dist(Q[j], Q[l]) != dist_p1k) continue;
                    if (prod(Q[i], Q[j], Q[l]) != prod_p) continue;
                    exist = true;
                    break;
                }
                if (!exist) {
                    possible_flg = false;
                    break;
                }
            }
            if (possible_flg) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
}