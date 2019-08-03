# How to make a patch

```sh
# After modified source code..
git add -A
git commit -v
git format-patch -1 -o /tmp/
mutt -H /tmp/0001-change-Makefile.patch
```
