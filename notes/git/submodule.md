# HW1: Git Submodule
## 狀況1：加入 Git submodule

```sh
$ git submodule add <repository-url> <directory>
```

repository 是專案的網址，directory 是想要讓這個 submodule 在你專案中要叫做什麼名稱。

新增完 submodule 後必須提交 commit 多出來的兩個檔案：
* .gitmodules
* submodule-name

### Gitlink
Gitlink 是連結 git repository 中的某一個 commit object ( 例如 70460b4b4aece5915caf5c68d12f56xxxx)，每一個 submodule 都會連結一個 Gitlink，當你 checkout 這個 submodule 時，只會 checkout commit object 當下的資料，而不會是 repository 最新的 commit 資料， 等同於我們可以鎖死 submodule 某一個時間點的資料。

### .gitmodules
當你在 Git 中加入了一個 submodule ，那麼你的 Project 根目錄會有一個檔案.gitmodules，裡面會記錄 submodule 的 git repository 路徑與對應的目錄。

```gitmodules
[submodule "test-submodules"]
  path = test-submodules
  url =  [https://github.com/YogaPan/test-submodules](https://github.com/YogaPan/test-submodules)

```



## 狀況2：更新 submodules

### User A
手動至每個子項目下 pull
```sh
$ cd module-1 && git pull origin master
$ cd ../module-2 && git pull origin master
```

或是利用 foreach
```shell
$ git submodule foreach --recursive git pull origin master
```

發現 gitlink 變成最新的，然後接著 commit 和 push

```shell
$ git commit -m '更新子專案版本'
$ git push origin master
```

### User B
```sh
$ git pull origin master
```

因為新的 Submodule Gitlink 和 submodule 現在的 commit sha 不合
會進入 dirty state，可以用 update 解決：

```sh
$ git submodule update
```



## 狀況3：當要 Clone 含有 Submodule 的 Git 專案時

```sh
$ git clone --recursive <project-url>
```

啊！不小心手殘了！打成：
```sh
$ git clone <project-url>
```

會發現 Submodule 的資料夾空空如也，怎麼辦呢？

Note: 如果 Clone 專案的同時沒有使用`--recursive` 這個參數的話，其他 submodules 的資料夾底下會是空的。

```sh
$ git submodule init
$ git submodule update --recursive
```

可以把這兩行指令合成一行:

```sh
$ git submodule update --init --recursive
```

`git submodule init`的功能是將.gitmodules 檔案裡面的資料，復製一份到.git/config 。打開來會發現多了下面這個設定：

```git
[submodule]
  active = .
[submodule “dot”]
  url = https://github.com/YogaPan/dotfiles
```

這樣才算真的有套用到 submodule，只有 .gitmodules 這個檔案是不夠的。



## 狀況4：移除 submodule

1. 移除目錄

`git rm —cached [目錄]`
`git rm [目錄]`

2. 修改.gitmodules，移除不需要的 module

`code .gitmodules`

3. 修改.git/config，移除 submodule URL

`code .git/config`

4. 執行 commit

`git add . && git commit -m “Remove sub module”`

5. 最後 syn module 資料

`$ git submodule sync`



## 狀況5：從現有專案獨立切割出來
TODO


## 參考資料
* [Git - 子模組 (Submodules)](https://git-scm.com/book/zh-tw/v1/Git-%E5%B7%A5%E5%85%B7-%E5%AD%90%E6%A8%A1%E7%B5%84-Submodules)
* [什麼是  Git Submodule](https://www.puritys.me/docs-blog/article-300-%E4%BB%80%E9%BA%BC%E6%98%AF-Git-Submodule.html)
* [Git Submodule 介紹與使用 | 小惡魔 - 電腦技術 - 工作筆記 - AppleBOY](https://blog.wu-boy.com/2011/09/introduction-to-git-submodule/)
* [Working with submodules - The GitHub Blog](https://github.blog/2016-02-01-working-with-submodules/)
