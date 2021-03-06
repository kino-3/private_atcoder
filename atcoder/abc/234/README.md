# ABC 234

## 重要メモ

- D: unordered_map, unordered_set は平均 O(1)
- D: pb_ds に set の拡張のようなもの (tree) がある
- F: atcoder::convolution で畳み込みができる
  - convolution_ll はオーバーフローの可能性があるので使わないほうが良い
  - convolution は指定した mod をとった結果を返してくれる(はず)

## D

- 尺取のような方法で解いた
- priority_queue でもとける(サイズを K にして, 最小を監視)
- unordered_map の存在を思い出した。
- pb_ds の tree を使っても解ける
  - Binary Trie でも解ける, がビット演算が絡まなければ pb_ds で事足りる気がする。

## E

- 桁数に応じた場合分けをした
  - 999...999 が条件を満たすため, 答の桁数と元の数の桁数は等しい
  - 公差の絶対値が 2 以上になりうるのは高々 5 桁のとき -> 線形探索すればよい
  - 公差の絶対値が 1 以下の数の k 桁の数は全列挙可能
- 解答: そもそも 10^18 未満の答の候補の個数は十分に少ないため, 答の候補を全列挙して, 単純に比較しても間に合う。
  - こちらの方が実装が楽

## F

- O(N^2) の DP
  - 組み合わせも O(N^2) の DP
- 別解 2 つはおそらく同じ
  - S が p を A 個, q を B 個, r を C 個からなる場合
    - p を a 個, q を b 個, r を c 個選んだ場合は (a+b+c)!/(a!b!c!) 通り
      - これを 0 <= a <= A, 0 <= b <= B, 0 <= c <= C の (A+1)(B+1)(C+1) 個足し合わせる
    - (Σ 1/a! x^a)(Σ 1/b! x^b)(Σ 1/c! x^c) を展開した時の係数を考える
      - {1/0!, 1/1!, ..., 1/a!}, {1/0!, 1/1!, ..., 1/b!}, {1/0!, 1/1!, ..., 1/c!} の畳み込みで a+b+c = k である 1/(a!b!c!) の和が分かる
      - あとは, これに k! を掛けて和をとればよい。
      - 畳み込みは atcoder::convolution が使える

## H

- 以下の手順で解いた
  - x 座標で点をソートする
  - 左側から, x 座標が x ~ x + K の点を {y, x} の pair の set で管理する
  - y - K から y + K の間の領域の点だけを距離計算する
    - 鳩ノ巣原理から間に合うと思われる 
- 公式解答のように, 領域を K * K の格子に切断して, 同じor隣接する格子に属する点の距離だけを調べる方法の方がシンプル
