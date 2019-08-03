# Macro

## Basic
```C
#define BUF_SIZE 128

char buffer[BUF_SIZE];
```

## Lodash
```C
__func__
__DATE__
__LINE__
__FILE__
```

## Macro Function
```C
#define add(x, y) ((x) + (y))

#define swap(x, y) \
({ \
        typeof(x) __tmp = (x); \
        (x) = (y); \
        (y) = __tmp; \
})

#define sub(x, y) \
(int)({ \
        typeof(x) __tmp; \
        __tmp = (x) - (y); \
        __tmp; \
})


#define
```

```sh
$ cpp file.c
$ gcc -e file.c
$ gcc -M file.c
```

# LINK
- [GNU: The C Preprocessor 導讀](http://wen00072-blog.logdown.com/posts/146624-talk-about-c-macros)
