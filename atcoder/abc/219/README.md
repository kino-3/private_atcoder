# ABC 219

## 重要メモ

- E: 領域の単連結判定は「連結判定」+「外部拡張&外部の連結判定」
- F: {x,y} の場合分け

```cpp
if ({x, y} == {0, 0}) {
    // 例外処理
} else {
    if (x == 0) swap(x, y);
    // これで, x != 0 が保証される
    if (x < 0) x = -x;
    // これで, x > 0 が保証される
}
```

## C

- char は `0-9`, `a-z`, `A-Z` の順番が(おそらく)保証されている。
  - ref. <https://en.cppreference.com/w/cpp/language/ascii>

## E

- 連結判定は BFS (UnionFind で解いた)
- 単連結判定は「連結判定」+「外部拡張&外部の連結判定」

## F

- 同解法
