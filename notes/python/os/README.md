# OS

## env
```py
os.environ['HOME']
os.getenv('HOME', None)  # Set dedault value
```

## user and group
```py
os.geteuid()
os.getegid()
getpass.getuser()
```

## access
```py
os.access('file', os.R_OK)
os.access('file', os.W_OK)
os.access('file', os.X_OK)

```

## path
```py
os.getcwd()
os.path.dirname(os.path.realpath(__FILE__))

os.chmod('file', 0o755)
os.chdir('path')
os.mkdir('dir')
open('filename', 'a').close()  # touch file
os.remove('file')              # remove a file
os.rmdir('dir')                # remove an empty directory
shutil.rmtree('dir')           # delete a directory and all its contents

os.path.join('a', 'b')
os.listdir('path')

for (dirpath, dirnames, filenames) in os.walk(mypath):
    print(filenames)
    # break

os.path.exists('file')
os.path.isfile('file')
os.path.isdir('file')
os.path.getsize('file')
os.path.islink('file')

```

## stat
```py
os.stat('file').st_uid
os.stat('file').st_gid
stat.S_ISDIR(os.stat('file').st_mode)
stat.S_ISREG(os.stat('file').st_mode)
stat.S_ISLNK(os.stat('file').st_mode)
os.stat('file') & stat.S_ISGID
os.stat('file') & stat.S_ISUID
os.stat('file') & stat.S_ISVTX
os.stat('file').st_mtime
os.stat('file').st_atime
os.stat('file').st_ctime
```

# Link
- [File test comparison table for shell, Perl, Ruby, and Python](http://blog.endpoint.com/2009/08/file-test-comparison-table-for-shell.html)
