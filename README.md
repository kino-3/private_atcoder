# private_atcoder

AtCoder

## 環境

MinGW で https://github.com/msys2/MINGW-packages/issues/3163 の問題が解決できないため, WSL を利用する

```bash
sudo apt update
sudo apt upgrade
sudo apt install build-essential
sudo apt install gdb
ulimit -c unlimited
g++ --version  # g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
```

```
$ gdb a.out # デバッガの起動
(gdb) r # デバッグモードでの実行
(gdb) bt # 関数呼び出し情報のトレース
(gdb) f 5 # bt の # 5 に移動
(gdb) q # デバッグモードの終了
```

- VSCode の Remote WSL で /mnt/c/.../private_atcoder を開く

### 旧環境

```txt
$ g++ --version
g++.exe (MinGW.org GCC-8.2.0-3) 8.2.0
```

## VSCode

- スニペット設定
  - ファイル > ユーザー設定 > ユーザースニペット > cpp.json > (ワークスペース名)の新しいスニペットファイル > `cpp.json`
- [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
  - format: Shift+Alt+F
- その他:

## 参考になりそうな記事

- [VSCode拡張機能](https://qiita.com/AokabiC/items/af685bfd205dda44ec45)
- [競技プログラミング(C++)](https://koturn.hatenablog.com/entry/2018/07/29/180000)
