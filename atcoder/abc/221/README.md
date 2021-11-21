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

- E: `2^(-i) (mod prime)` は `2^(prime-1) ≡ 1 (mod prime)` を利用して, `2^(-i) ≡ 2^(prime-1-i)  (mod prime)` とする。

## E

- 転倒数関連であることは分かったが, どうすればよいか分からなかった。PASS
- `2^(j-i-1) = 2^j * 2^(-i-1)` と変数分離することがポイント
