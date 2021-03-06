# ABC 236

## 重要メモ

- E: 平均値, 中央値の最大化 -> 答で二分探索の判定問題に帰着

## B

- 別解1: 総和から数値を引く
- 別解2: XOR をとる (A XOR A = 0 なので)

## D

- `15*13*11*......` まではすぐに分かったが, DFS に時間がかかった。
- 別解: 条件付き辞書順全列挙でも解くことができる。

## E

- 平均値の最大値 -> 答で二分探索により, 合計値の最大値に帰着
  - x[i] の平均値を K 以上にできるか
  - x[i] - K の平均値を 0 以上にできるか
  - x[i] - K の合計値を 0 以上にできるか
  - x[i] - K の合計値の最大値が 0 以上か
- 中央値の最大値 -> 答で二分探索により, 合計値の最大値に帰着
  - x[i] の中央値を K 以上にできるか
  - x[i] - K が 0 以上のものの個数が 0 未満のものの個数より多い
  - y[i] = (x[i] - K >= 0 ? 1 : -1) としたとき, y[i] の総和が正
  - y[i] の合計値の最大値が 0 より大きいか

## F

- 昇順に並べて, それが現時点で作れなければ追加する(Kruskal法のイメージ)
  - 条件を満たし, 上記方法ではない集合 S では, 小さい方から見た時に, x を追加すべき時に y を追加している(x < y)
    - S = a[0], ..., a[i], y, ...
      - x は a[0], ..., a[i] では作れないが, x は S の要素から作れる
      - x = (p XOR q XOR r XOR ... XOR z) として, 右辺には x 以上の値 z が含まれる
        - z = (x XOR p XOR q XOR r XOR ...)
      - S のうち z を x に置き換えたものを S' とすると, cost(S') < cost(S) かつ S' は条件を満たす
- 購入する数は N 個
  - 既に作ることのできる数を a[i] (i=0,1,...) とすると
    - x XOR a[i] ≠ a[j] (all i, j)
      - x XOR a[i] = a[j] とすると x = a[i] XOR a[j] となり矛盾
    - x XOR a[i] ≠ x XOR a[j] (all i, j)
      - x XOR a[i] = x XOR a[i] とすると a[i] = a[j] となり矛盾
  - よって、作ることのできる数は必ず倍になる(最初は値0の1個)
