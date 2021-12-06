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
    for (auto&& item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}
template <typename T>
void print_vv(const vector<T> vec) {
    for (auto&& item : vec) {
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
ll N, M, Q, i, j, k, l;
vector<pair<ll, ll>> pos;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    pos.resize(N);
    REP(i, N) { cin >> pos[i].first >> pos[i].second; }

    sort(ALL(pos));

    // 条件を満たす最大値を求める
    ll lb = 0;           // これは条件を満たす必要がある
    ll ub = 1000000000;  // これは条件を満たさない必要がある
    while (ub - lb > 1) {
        ll mid = (ub + lb) / 2;  // mid は ub の初期値にはならない
        bool possible = false;

        ll lower = pos[0].second;
        ll upper = pos[0].second;
        ll left_idx = 0;
        ll right_idx = 0;
        REP(left_idx, N - 1) {
            ll mid = (ub + lb) / 2;  // mid は ub の初期値にはならない
            lower = min(lower, pos[left_idx].second);
            upper = max(upper, pos[left_idx].second);
            bool end_flg = false;
            if (pos[right_idx].first >= mid + pos[left_idx + 1].first) continue;
            while (pos[right_idx].first < mid + pos[left_idx].first) {
                right_idx++;
                if (!(right_idx < N)) {
                    end_flg = true;
                    break;
                }
            }
            if (end_flg) break;
            while (pos[right_idx].first < mid + pos[left_idx + 1].first) {
                if (pos[right_idx].second <= lower - mid ||
                    pos[right_idx].second >= upper + mid) {
                    possible = true;
                    end_flg = true;
                    break;
                }
                right_idx++;
                if (!(right_idx < N)) {
                    end_flg = true;
                    break;
                }
            }
            if (end_flg) break;
        }

        if (possible) {
            lb = mid;
        } else {
            ub = mid;
        }
    }
    cout << lb << endl;
}