# Autotools

## Files and directories
+ include/
  - fuck.h
  - Makefile.am
+ lib/
  - fuck.c
  - Makefile.am
+ src/
  - hello.c
  - Makefile.am
+ Makefile.am

## Makefile.am

### Makefile.am
```sh
SUBDIRS = include lib src
```

### include/Makefile.am
```sh
include_HEADERS = fuck.h
```

### lib/Makefile.am
```sh
lib_LIBRARIES = libfuck.a
libfuck_a_SOURECES = libfuck.c
AM_CFLAGS = -I../include
```

### src/Makefile.am
```sh
bin_PROGRAMS = hello
hello_SOURCES = hello.c
LDADD = ../lib/libfuck.a
AM_CFLAGS = -I../include
```

## Workflow

### Get configure.ac
```sh
$ autoscan                        # Scan your project and get configure.scan.
$ mv configure.scan configure.ac
```

### Modify configure.ac
```sh
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_RANLIB
AM_PROC_AR
```

### autoreconf --install
```sh
$ autoheader                  # For config.h.in
$ aclocal                     # For m4
$ automake --add-missing      # For Makefile.in
$ auotconf                    # For configure
```

### install
```sh
$ ./configure                 # This will gernerate Makefile and config.h
$ make
$ make install
```

### uninstall
```sh
make uninstall
```

### clean
```sh
make clean      # .a .o and exetable files.
make distclean  # clean files that generate by ./configure
```

### tarball
```sh
make dist
```

## Learning Resources

- [Autotools Tutorial for Beginners](http://markuskimius.wikidot.com/programming:tut:autotools)
- [GNU Build System: Autotools 初探](http://wen00072-blog.logdown.com/tags/autotool#at-integrate)
