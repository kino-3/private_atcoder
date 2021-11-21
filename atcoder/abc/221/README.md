# ABC 221

## 重要メモ

- set の二分探索について
  - `std::lower_bound` の set に対する計算量は O(N)

    ```cpp
    int v;
    set<int> s;
    distance(s.begin(), lower_bound(s.begin(), s.end(), v));
    ```

  - `std::set::lower_bound` の計算量は O(log N) (こちらを使うべき)

    ```cpp
    int v;
    set<int> s;
    distance(s.begin(), s.lower_bound(v));
    ```

## E
