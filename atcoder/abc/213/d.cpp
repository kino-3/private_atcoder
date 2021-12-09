// #include <bits/stdc++.h>
// #define REP(var, n) for (decltype(n) var = 0; var < (n); var++)
// #define REP_R(var, n) \
//     for (auto var = (n)-1; var != static_cast<decltype(var)>(-1); var--)
// #define FOR(var, a, b) for (auto var = (a); var < (b); var++)
// #define FOR_R(var, a, b) for (auto var = (b - 1); var > (a - 1); var--)
// #define ALL(c) std::begin(c), std::end(c)

// using namespace std;
// using ll = long long;

// // REP(idx, 3) { cout << idx; }  // 012
// // REP_R(idx, 3) { cout << idx; }  // 210
// // FOR(idx, 4, 7) { cout << idx; }  // 456
// // FOR_R(idx, 4, 7) { cout << idx; }  // 654
// // sort(ALL(v));

// void debug_print() {
//     cout << endl;
// }
// template <class Head, class... Tail>
// void debug_print(Head&& head, Tail&&... tail) {
//     std::cout << head << ", ";
//     debug_print(std::forward<Tail>(tail)...);
// }
// ll DEBUG_PRINT_COUNT = 0;
// void debug_print_count() {
//     cout << "debug: " << DEBUG_PRINT_COUNT << endl;
//     DEBUG_PRINT_COUNT++;
//     assert(DEBUG_PRINT_COUNT < 10);
// }
// template <typename T>
// void print_v(const vector<T> vec) {
//     cout << "[";
//     for (auto &&item : vec) {
//         cout << item << ",";
//     }
//     cout << "]" << endl;
// }
// template <typename T>
// void print_vv(const vector<T> vec) {
//     for (auto &&item : vec) {
//         print_v(item);
//     }
// }
// template <typename K, typename V>
// void print_map(const map<K, V> dict) {
//     for (const auto v: dict) {
//         cout << v.first << ":" << v.second << ", ";
//     }
//     cout << endl;
// }
// template <typename T>
// void print_set(const set<T> data) {
//     for (const auto v: data) {
//         cout << v << ", ";
//     }
//     cout << endl;
// }
// template <typename T1, typename T2>
// void print_pair(const pair<T1, T2> data) {
//     cout << "(" << data.first << "," << data.second << ")";
//     // cout << endl;
// }
// template <typename T1, typename T2, typename T3>
// void print_tuple(const tuple<T1, T2, T3> data) {
//     cout << "(";
//     cout << get<0>(data) << "," << get<1>(data) << "," << get<2>(data);
//     cout << ")";
//     // cout << endl;
// }

// class Tree {
//    public:
//     ll V;                         // 頂点の個数
//     vector<vector<ll>> graph;     // 隣接リスト
//     vector<ll> parent;            // 親ノード
//     vector<vector<ll>> children;  // 子ノード
//     vector<ll> size;   // 自身を root とする部分木の大きさ
//     vector<ll> depth;  // 深さ

//     Tree(ll v) : V(v), graph(v), parent(v), children(v), size(v), depth(v) {}

//     void add_edge(ll n1, ll n2) {
//         graph[n1].push_back(n2);
//         graph[n2].push_back(n1);
//     }

//     // 頂点 v で吊ったときの木探索
//     ll exec(ll v, ll parent_of_v = -1) {
//         if (parent_of_v == -1) {
//             depth[v] = 0;
//         }
//         parent[v] = parent_of_v;
//         ll s = 1;
//         for (const auto &child : graph[v]) {
//             if (child == parent_of_v) continue;
//             depth[child] = depth[v] + 1;
//             s += exec(child, v);
//             children[v].push_back(child);
//         }
//         size[v] = s;
//         return s;
//     }
// };

// // input
// // N
// // a_1   b_1
// // a_2   b_2
// //  :
// // a_N-1 a_N-1

// ll N, i, j, k;

// int main() {
//     std::cin.tie(nullptr);
//     std::ios::sync_with_stdio(false);

//     cin >> N;
//     Tree tree = Tree(N);
//     REP(i, N - 1) {
//         cin >> j >> k;
//         tree.add_edge(j - 1, k - 1);
//     }
//     tree.exec(0);

//     REP(i, N) {
//         // i -> i + 1
//         cout << i + 1 << " ";
//         ll begin = i;
//         ll end = (i + 1) % N;
//         vector<ll> root1;
//         vector<ll> root2;
//         ll tmp = begin;
//         if (tree.depth[begin] > tree.depth[end]) {
//             while (tree.depth[begin] > tree.depth[end]) {
//                 begin = tree.parent[begin];
//                 root1.push_back(begin);
//             }
//         } else if (tree.depth[begin] < tree.depth[end]) {
//             while (tree.depth[begin] < tree.depth[end]) {
//                 end = tree.parent[end];
//                 root2.push_back(end);
//             }
//         }
//         while (begin != end) {
//             // debug_print(begin, end);
//             begin = tree.parent[begin];
//             end = tree.parent[end];
//             root1.push_back(begin);
//             root2.push_back(end);
//         }
//         // print_v(root1);
//         // print_v(root2);
//         if (root1.size() == 0) {
//             reverse(ALL(root2));
//             FOR(j, 1, root2.size()) { cout << root2[j] + 1 << " "; }
//         } else if (root2.size() == 0) {
//             REP(j, root1.size() - 1) { cout << root1[j] + 1 << " "; }
//         } else {
//             for (auto r : root1) {
//                 if (r != begin) cout << r + 1 << " ";
//             }
//             cout << begin + 1 << " ";
//             reverse(ALL(root2));
//             for (auto r : root2) {
//                 if (r != begin) cout << r + 1 << " ";
//             }
//         }
//     }
//     cout << 1 << endl;
// }