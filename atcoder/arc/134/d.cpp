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

#ifdef _DEBUG
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
#else
void debug_print() {}
template <class Head, class... Tail>
void debug_print(Head&& head, Tail&&... tail) {}
void debug_print_count() {}
template <typename T>
void print_v(const vector<T> vec) {}
template <typename T>
void print_vv(const vector<T> vec) {}
template <typename K, typename V>
void print_map(const map<K, V> dict) {}
template <typename T>
void print_set(const set<T> data) {}
template <typename T1, typename T2>
void print_pair(const pair<T1, T2> data) {}
template <typename T1, typename T2, typename T3>
void print_tuple(const tuple<T1, T2, T3> data) {}
template <typename T1, typename T2>
void print_vp(const vector<pair<T1, T2>> vec) {}
#endif

const ll mod = 998244353;  // 1000000007;
ll N, M, Q, i, j, k, l;
vector<ll> A, B;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    A.resize(2 * N);
    REP(i, N * 2) { cin >> A[i]; }

    map<ll, vector<ll>> former;
    REP(i, N) { former[A[i]].push_back(i); }

    // A1
    auto v = *former.begin();
    // debug_print(v.first);
    // print_v(v.second);
    ll init = v.first;
    ll tmp = init + 1;
    for (auto vv : v.second) {
        if (A[vv + N] < tmp) {
            tmp = A[vv + N];
        }
    }
    if (tmp <= init) {
        cout << init << " " << tmp << endl;
        return 0;
    }

    // a2
    vector<ll> answer = v.second;
    ll r_init = A[v.second[0] + N];
    // debug_print(r_init);
    // print_v(answer);
    for (auto v : former) {
        if (v.first == init) continue;
        if (v.first < r_init) {
            for (auto vv : v.second) {
                if (vv > answer[answer.size() - 1]) {
                    answer.push_back(vv);
                }
            }
        } else if (v.first == r_init) {
            bool should_add = false;
            for (auto ansv : answer) {
                if (ansv < r_init) {
                    break;
                } else if (ansv > r_init) {
                    should_add = true;
                    break;
                }
            }
            if (should_add) {
                for (auto vv : v.second) {
                    if (vv > answer[answer.size() - 1]) {
                        answer.push_back(vv);
                    }
                }
            }
        } else {
            break;
        }
    }
    for (auto v : answer) {
        cout << A[v] << " ";
    }
    for (auto v : answer) {
        cout << A[v + N] << " ";
    }
    cout << endl;
}