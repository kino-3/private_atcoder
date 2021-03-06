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
vector<vector<ll>> AA;
vector<ll> A;
ll ans;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    cin >> N;
    AA.resize(2 * N, vector<ll>(2 * N, 0));
    REP(i, 2 * N - 1) {
        REP(j, 2 * N - 1 - i) {
            cin >> k;
            AA[i][i + j + 1] = k;
            AA[i + j + 1][i] = k;
        }
    }

    ll ans = 0;

    // 2*N ??????????????? N ?????????????????????
    ll L = 2 * N;
    A.resize(L);
    REP(i, L) A[i] = i;  // ????????????
    // ??????: ???????????? left < right ?????? left ?????????
    // 02/15/37/46 ?????????
    // - right ????????? 6, 76 ?????????
    // - 576 ?????????????????????
    // - 5 ??????37/46?????????5????????????????????????????????????6?????????
    // 02/16/XX/XX ??? XX/XX ???????????? 34/57 ?????????
    while (true) {
        ll tmp_ans = 0;
        REP(i, N) { tmp_ans ^= AA[A[i * 2]][A[i * 2 + 1]]; }
        ans = max(ans, tmp_ans);

        // next
        ll tmp = A[L - 1];
        ll flg = -1;
        for (ll i = L - 1; i > 0; i -= 2) {
            if (tmp > A[i]) {  // ????????????(i?????????)????????????
                flg = i;
                break;
            }
            tmp = A[i];
        }
        if (flg < 0) break;  // ???????????????
        // 02/15/37/46 ????????? A[flg] ??? 5
        sort(next(A.begin(), flg + 1), A.end());  // 02/15/37/46 -> 02/15/34/67
        ll idx = distance(
            A.begin(), lower_bound(next(A.begin(), flg + 1), A.end(), A[flg]));
        swap(A[idx], A[flg]);  // 02/15/37/46 -> 02/16/34/57
    }

    cout << ans << endl;
}