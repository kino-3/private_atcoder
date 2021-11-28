# ABC 218

## 重要メモ

- set_intersection: 2 つの vector などの積集合をとる
  - 和集合は set_union
  - 計算量は O(N)
    - 事前ソートは必須

```cpp
vector<int> vec1;
vector<int> vec2;
sort(vec1.begin(), vec1.end()); // ソートする必要がある
sort(vec2.begin(), vec2.end());
vector<int> res; // 結果を格納するものを用意する必要がある
set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), back_inserter(res));
```

## C

- 結構手間取った。(ライブラリ化済み)
- `vector<vector<ll>>` も `==` で値の比較ができるようである
- `'#'` がある座標を set として扱う方法もある。

## D

- set_intersection で sort が必要と知らなかった
- 右上と左下で 2重for を回す方が実装が楽

## F

- 単始点単終点最短経路は O(N+M)
