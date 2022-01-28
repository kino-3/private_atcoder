# ABC 196

## 重要メモ

- C: 文字列と数字の相互変換
  - 数字 -> 文字列: to_string(123)
  - 文字列 -> 数値(long long): stoll("123")
- F: 部分文字列一致度最大を FFT で解く
  - Σ_j f(a_i+j, b_j) の形なので, b を逆順に並べると畳み込みの形になる

## D

- bit 全探索で解いた
- bit DP でも解ける

## E

- 最終的に定値関数になる場合のバグ解消の発見and解消に時間がかかった
- std::clamp 関数がある
  - https://cpprefjp.github.io/reference/algorithm/clamp.html
- clamp 関数に f1, f2, f3 を合成した後の clamp 関数(のパラメータ)を考えるとよい
- クエリを昇順に並び替えて実験することでも解ける
  - 圧縮することで計算量を落とせる
    - https://blog.hamayanhamayan.com/entry/2021/03/21/124642
