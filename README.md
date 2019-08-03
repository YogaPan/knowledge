# Knowledge

個人筆記、知識整理、程式碼範例、CheatSheet
TODO: add icon to this project

## Quick Start

Clone
`$ git clone --recursive <repository>`

Update
`$ git submodule foreach git pull`

## 命名規範：

資料夾名城：空白用 dash 代替
Example: command-line/

檔案名稱：用 underscore 代替
Example: merge_request.md

## 運行腳本確定文章格式

`$ ./scripts/format.sh`

## 目錄結構分成以下幾種

### Notes

文章、 程式範例
**TODO**: Add link

### Blog

Submodule，會對外發布的文章
TBD: 尋找發布的方法
看能不能連動 Medium

### Side Project

裡面的專案是 Submodule，方便一次查看。
TODO: add link

### Dotfiles

Submodule，個人設定、初始化腳本
TODO: add link

### Scripts

1. format: 確認文章質量
2. report: 計算文章數量

## Commit Convention

使用 Angular Commit Style Convention
