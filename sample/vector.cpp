#include <bits/stdc++.h>
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

    // sort (std::sort($1,$2) は [$1,$2) の昇順ソート)
    std::sort(v.begin(), v.end());
    print_v(v);
    // 降順ソート
    std::sort(v.begin(), v.end(), greater<int>());
    print_v(v);
    // 範囲限定ソート
    std::sort(v.begin() + 2, v.end() - 3);
    print_v(v);
}