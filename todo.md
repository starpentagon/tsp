# コンテスト前日までに実施

## レポジトリの作成

* コンテスト用のレポジトリをGitHub上で作成
* Heuristic contest用レポジトリを複製する(https://blog.furu07yu.com/entry/github-clone-bare-repository)
```shell
$ git clone --bare https://github.com/starpentagon/heuristic_contest.git
$ cd heuristic_contest.git
$ git push --mirror https://github.com/starpentagon/XXX.git
$ cd ..
$ rm -rf heuristic_contest.git
$ git clone --bare https://github.com/starpentagon/XXX.git
```

* .profileのahcコマンドを修正
* Box上にフォルダを作成しスコア管理表を用意
* Windows updateの適用
* Visual Studio Codeの最新化
* dockerデーモンの起動
```shell
$ sudo service docker start
```
* dockerイメージをビルドする
* Jupyter notebookの起動確認

# 短期コンテスト
* テストケース生成/ダウンロード
*  
# デバッガ

```shell
$ gdb main /mnt/wslg/dumps/core.main
```