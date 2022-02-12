# ABC 199

## 重要メモ

## B

- ベクトルの最大値: `*max_element(ALL(vec))`

## D

- 連結成分ごとに DFS
  - 実装に苦戦した
- 別解法1 (二部グラフ)
  - red の頂点を決める (2^N)
  - 残りが 2 部グラフか ?
    - Yes -> 2^(連結成分の個数)
    - No  -> 0
- 別解法2
  - subset convolution (また出題されたらその時に考える)

## E

- bitDP で解いた(解法は https://kanpurin.hatenablog.com/entry/2021/04/29/190823 に同じ)

## F

- 各頂点の期待値を管理する
  - `y = Σ a_i * x_i` のとき, `E[y] = Σ a_i * E[x_i]` なので, 期待値で考える
  - 初期条件の期待値は値そのもの
