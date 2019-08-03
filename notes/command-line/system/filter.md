# Basic filter

## echo and cat
```sh
echo "abc"
echo -n "No new line"
cat message.txt
```

## redirect and pipe
```sh
echo "abc" > abc.txt

# Append to file
echo "456" >> abc.txt

# Don't show stdout and stderr
echo "213" > /dev/null 2>&1

# show result and write to file
echo "abc" | tee abc.txt
```

## head, tail, cut, sort
```sh
head -n 3
tail -c47

cut -d" " -f 3
cut -d: -f-3,4-5,7,9-
```

## sort
```sh

# Sort a file in ascending order
sort filename

# Sort a file in descending order
sort -r filename

# Sort passwd file by the 3rd field
sort -t: -k 3n /etc/passwd

# Sort from word
sort -t: -k 5.7,5.8 file

t=delimeter
k=key
r=reverse
n=numeric
u=unique
m=merge
o=output

```

## uniq
```sh
# Display each line once
uniq file

# Display only unique lines:
uniq -u file

# Display only duplicate lines
uniq -d file

# Display number of occurences of each line along with that line
uniq -c file
```

# diff and patch
```sh
# Compare files
diff file1 file2

# Like git
diff -u file1 file2

# Compare files, showing differences side by side
diff -y file1 file2

# Compare directories recursively
diff -r directory1 directory2

# Generate patch
diff -Naur dir1 dir2> patch.txt

# Apply a patch
patch < patchfile.diff

# Apply a patch to current directory
patch -p1 < patchfile.diff
```


## grep
```sh

# Search for an exact string:
grep something file_path
cat file_path | grep something

# Search without case-sensitivity:
grep -i something file_path

# Use ERE(extended regular expression)
grep -E regex file_path

# Invert match for excluding specific strings:
grep -v something

# This can use multiple times.
grep -e something -e somthing file_path

# Recrusive search this directory.
grep -R something

# Just show filename.
grep -Rl something

# Just count how many times.
grep -Rc something
```

## sed

```sh
# Replace the first occurrence of a string in a file, and print the result
sed 's/find/replace/' filename

# Replace all occurrences of a string in a file, overwriting the file
sed -i 's/find/replace/g' filename

# Replace all occurrences of an extended regular expression in a file
sed -r 's/regex/replace/g' filename

# Apply multiple find-replace expressions to a file
sed -e 's/find/replace/' -e 's/find/replace/' filename

# Append after line
sed '/3/a 4' filename

# Insert before line.
sed '/3/i 2' filename

# Change
sed '/yogapan/c handsome-boy' filename

# Just like `head -n 3`
sed '3q' filename

# line 3 to end substitude
sed '3,$ s/abc/zxc/g' filename
```

## awk
```sh
awk -v start="$start" end="$end" '{ if ($1 >= start && $1 <= end) print }' test.txt
```

## Find
```sh
find / -name filename -print 2>/dev/null
```
