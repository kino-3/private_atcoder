#include <bits/stdc++.h>
#define ALL(c) std::begin(c), std::end(c)
using namespace std;

template <typename T>
void print_v(const vector<T> vec) {
    cout << "[";
    for (auto &&item : vec) {
        cout << item << ",";
    }
    cout << "]" << endl;
}

int main() {
    // see: https://cpprefjp.github.io/reference/vector/vector.html
    vector<int> v = {1, 3, 5, 7, 9, 8, 6, 4, 2};
    cout << "size: " << v.size() << endl;       // 要素数
    cout << "is_empty: " << v.empty() << endl;  // 空か
    // capacity を変更する
    // 領域の再確保が発生すると全ての要素が新しい領域にコピーされ非常に高コスト
    cout << "capacity: " << v.capacity() << endl;
    v.reserve(20);
    cout << "capacity: " << v.capacity() << endl;

    // v.begin() は v の最初の要素を指す iterator
    // v.end() は v の最後の要素の次の要素を指す iterator
    // iterator は +n, -m で勧めることができる
    // std::next(iter, n), std::prev(iter, m) も同じ
    print_v(v);
    cout << "offset=2: " << v[2] << ", " << v.at(2) << ", " << *(v.begin() + 2)
         << endl;         // 要素アクセス
    *(v.end() - 1) = -1;  // 最後から1番目の要素を -1 にする
    *(v.end() - 2) = -2;  // 最後から2番目の要素を -2 にする
    print_v(v);
    // 末尾に追加
    v.push_back(99);
    print_v(v);
    // 末尾から削除
    v.pop_back();
    print_v(v);
    // v[2] の位置に挿入
    v.insert(v.begin() + 2, -5);
    print_v(v);
    // v[2] の位置を削除
    v.erase(v.begin() + 2);
    print_v(v);

    // 要素数と要素の値が全て等しいか
    cout << "eq: " << (v == v) << endl;

    // sort (std::sort($1,$2) は [$1,$2) の昇順ソート)
    std::sort(v.begin(), v.end());
    print_v(v);
    // 降順ソート
    // std::sort(v.rbegin(), v.rend()); でもよい
    std::sort(v.begin(), v.end(), greater<int>());
    print_v(v);
    // 範囲限定ソート
    std::sort(v.begin() + 2, v.end() - 3);
    print_v(v);
    // マクロsort
    sort(ALL(v));
    print_v(v);
    // lambda sort
    auto comp = [](int a, int b) { return std::abs(a) < std::abs(b); };
    std::sort(v.begin(), v.end(), comp);
    print_v(v);

    // 配列の各要素が条件を満たすか
    auto is_even = [](int a) { return a % 2 == 0; };
    cout << "all: " << std::all_of(v.begin(), v.end(), is_even) << endl;
    cout << "any: " << std::any_of(v.begin(), v.end(), is_even) << endl;
    cout << "none: " << std::none_of(v.begin(), v.end(), is_even) << endl;

    // min
    cout << std::min(2, -3) << endl;  // 引数は 2 つしかとれない
    cout << std::min({3, -4, 6, 8}) << endl;  // 配列はとれる
    cout << *(std::min_element(ALL(v)))
         << endl;  // min_elementは参照を返すことに注意
    // min, max を同時に出せるやつもいる
    auto minmax_pair = std::minmax({3, -4, 6, 8});
    cout << "min: " << minmax_pair.first << ", max: " << minmax_pair.second
         << endl;
    auto minmax_pair_iter = std::minmax_element(ALL(v));
    cout << "min: " << *(minmax_pair_iter.first)
         << ", max: " << *(minmax_pair_iter.second) << endl;

    // count 系
    v.push_back(1);
    sort(ALL(v));
    print_v(v);
    cout << "count 1: " << std::count(v.begin(), v.end(), 1) << endl;
    cout << "count even: " << std::count_if(v.begin(), v.end(), is_even)
         << endl;
    // find 系
    // found_iter は 最初に見つけた iter (*found_iter は当然 1)
    auto found_iter = std::find(v.begin(), v.end(), 1);
    cout << "first index: " << found_iter - v.begin() << endl;
    found_iter = std::find_if(ALL(v), is_even);
    cout << "first index: " << found_iter - v.begin() << endl;

    print_v(v);
    // reverse
    std::reverse(v.begin() + 2, v.end() - 1);
    print_v(v);
    // remove (以下の動作をする)
    // [v.begin(), result) には value 以外の要素が格納され
    // [result, v.end()) には value の要素が格納される
    auto result = std::remove(v.begin(), v.end(), 1);
    // そのため, value 1 を削除するには [result, v.end()) の erase が必要
    v.erase(result, v.end());
    print_v(v);
}