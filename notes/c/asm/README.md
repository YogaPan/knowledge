# ASM

## int 0x80

syscall | Param1 | Param2 | Param3 | Param4 | Param5
--------|--------|--------|--------|--------|-------
eax     | ebx    | ecx    | edx    | esi    | edi

| return |
|--------|
| eax    |

## syscall

syscall | Param1 | Param2 | Param3 | Param4 | Param5
--------|--------|--------|--------|--------|-------
rax     | rdi    | rsi    | r10    | r8     | r9

| return |
|--------|
| rax    |

## Hello Example

### Function Prototypes
```C
ssize_t
write(int fd, const void *buf, size_t count);

void
_exit(int status);
```

### arch/x86/include/asm/unistd_64.h
```C
#define __NR_write 1
#define __NR_exit 60
```

### Use C
```C
include <unistd.h>

int main(void)
{
        write(1, "Hello World\n", 12);
        _exit(0);
}
```

### Use ASM
```asm
.date
msg: .ascii "Hello World\n"

.text
.global _start

_start:
    movq    $1,   %rax  ; use the write syscall
    movq    $1,   %rdi  ; write to stdout
    movq    $msg, %rsi  ; use string "Hello World"
    movq    $12,  %rdx  ; write 12 characters
    syscall             ; make syscall

    movq    $60,  %rax  ; use the _exit syscall
    movq    $0,   %rdi  ; error code 0
    syscall             ; make syscall
```

## Link
- [X86 Assembly/Interfacing with Linux](https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux)
- [Using Inline Assembly in C/C++](http://www.codeproject.com/Articles/15971/Using-Inline-Assembly-in-C-C)
