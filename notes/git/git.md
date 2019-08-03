# Git

## Install and check version
```sh
sudo add-apt-repository ppa:git-core/ppa -y
sudo apt-get update
sudo apt-get install git
git --version
```

## Basic config
```sh
git config --global user.name "yourname"
git config --global user.email "username@gmail.com"
git config --global list | grep -e user.name -e user.email
```

```sh
git init
git clone url

git add -A
git commit -v

git push origin master
git pull origin master
git fetch origin master
git merge origin/master

git branch              # Local
git branch -a           # All
git branch -r           # Remote
git branch new-branch

git checkout new-branch
git checkout -b new-branch

git status
git log

git format-patch
git am

git remote -v
git remote add
```

## Hooks

- pre-commit
- post-commit
- pre-applypatch
- post-applypatch

```sh
# In .git/hooks/ directory
ln -sf ../../scripts/pre-commit.hook pre-commit
```

## Links
- https://git-scm.com/doc
