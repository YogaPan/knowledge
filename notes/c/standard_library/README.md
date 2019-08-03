# Standard Library

## Input, Output and File
### Input
```C
#include <stdio.h>

int
scanf(const char *fmt, ...);

int
fscanf(FILE *stream, const char *fmt, ...);

char *
fgets(char *str, int size, FILE *stream);

int
getchar(void);

int
fgetc(FILE *stream);

```

### Output
```C
#include <stdio.h>

int
printf(const char *fmt, ...);

int
fprintf(FILE *stream, const char *fmt, ...);

int
puts(const char *str);

int
fputs(const char *str, FILE *stream);

int
putchar(int c);

int
fputc(int c, FILE *stream);
```

### File
```C
#include <stdio.h>

#define EOF -1
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

FILE *stdin, *stdout, *stderr;

/* mode options */
"w", "r", "a", "w+", "r+", "a+"
"wb", "rb", "ab", "wb+", "rb+", "ab+"

/* r+ doesn't delete the content of the file and doesn't create a new file if such file doesn't exist,
 * whereas w+ deletes the content of the file and creates it if it doesn't exist. */

FILE *
fopen(const char *filename, const char *mode);

FILE *
freopen(const char *filename, const char *mode, FILE *stream);

int
fclose(FILE *stream);

int
feof(FILE *stream);

int
fflush(FILE *stream);

void
rewind(FILE *stream);
int
fseek(FILE *stream, long offset, int whence);

int
fprintf(FILE *stream, const char *fmt, ...);

int
fscanf(FILE *stream, const char *fmt, ...);

int
fputs(const char *str, FILE *stream);

char *
fgets(char *str, int size, FILE *stream);

int
fputc(int c, FILE *stream);

int
fgetc(FILE *stream);

size_t
fwrite(const void *ptr, size_t size, size_t nitems, FILE *stream);

size_t
fread(const void *ptr, size_t size, size_t nitems, FILE *stream);

```

## Charactor
```C
#include <ctype.h>

int
isdigit(int c);

int
isalpha(int c);

int
isalnum(int c);

int
isxdigit(int c);

int
islower(int c);

int
isupper(int c);

int
isspace(int c);

int
iscntrl(int c);

int
ispunct(int c);

int
isprint(int c);

int
isgraph(int c);

```

## String
```C
#include <stdio.h>

int
sprintf(char *str, const char *fmt, ...);

int
snprintf(char *str, size_t size, const char *fmt, ...);

int
sscanf(const char *str, const char *fmt, ...);

```

```C
#include <string.h>

size_t
strlen(const char *str);

/*
 * The  strdup()  function  returns  a  pointer  to a new string which is a
 * duplicate of the string s.  Memory for the new string is obtained with 
 * malloc(3), and can be freed with free(3).
 */

char *
strdup(const char *s);

char *
strcpy(char *dst, const char *src);
char *
strncpy(char *dst, const char *src, size_t n);  /* Watch out for null terminator. */

char *
strcat(char *s1, const char *s2);
char *
strncat(char *s1, const char *s2, size_t n);

int
strcmp(const char *s1, const char *s2);
int
strncmp(const *s1, const char *s2, size_t n);

char *
strchr(const char *str, int c);
char *
strrchr(const char *str, int c);

char *
strstr(const char *big, const char *little);
char *
strnstr(const char *big, const char *little, size_t n);

/* Returns a pointer to the first occurrence in str1 of any of the characters that are part of str2,
 * or a null pointer if there are no matches. */
char *
strpbrk(const char *s1, const char *s2);

/* Returns the length of the initial portion of str1
 * which consists only of characters that are part of str2. */
size_t
strspn(const char *s1, const char *s2);
/* Example usage */
char strtext[] = "129th";
char cset[] = "1234567890";
int i = strspn (strtext, cset); /* i = 3 */

/* Scans str1 for the first occurrence of any of the characters that are part of str2,
 * returning the number of characters of str1 read before this first occurrence. */
size_t
strcspn(const char *s1, const char *s2);
/* Example usage */
char str[] = "fcba73";
char keys[] = "1234567890";
int i = strcspn (str, keys);  /* i = 4 */

char *
strtok(char *s1, const char *s1);
```
http://nonsenseggler.blogspot.tw/

## String and Number cast
```C
#include <stdlib.h>

int
atoi(const char *str);
double
atof(const char *str);
long
atol(const char *str);
long long
atol(const char *str);

double
strtod(const char *nptr, char **endptr);
float
strtof(const char *nptr, char **endptr);
long
strtol(const char *nptr, char **endptr, int base);
long long
strtoll(const char *nptr, char **endptr, int base);
unsigned long
strtoul(const char *nptr, char **endptr, int base);
unsigned long long
strtoll(const char *nptr, char **endptr, int base);

```

## Memory
```C
#include <stdlib.h>

void *
malloc(size_t size);

/* Same as malloc, but initialize zero. */
void *
calloc(size_t count, size_t size);

/* Realloc new size and return new address */
void *
realloc(void *ptr, size_t size);

void *
free(void *ptr);

```

```C
#include <string.h>

void *
memcpy(void *dst, const void *src, size_t n);

void *
memmove(void *dst, const void *src, size_t n);

int
memcmp(const void *s1, const void *s2, size_t);

void *
memchr(const void *str, int c, size_t);

void *
memset(void *b, int c, size_t n);

```

## Math
```C
#include <math.h>

#define M_PI 3.141593

double
sin(double x);
double
asin(double x);
double
sinh(double x);

double
cos(double x);
double
acos(double x);
double
cosh(double x);

double
tan(double x);
double
atan(double x);
double
tanh(double x);

double
exp(double x);

double
log(double x);
double
log10(double x);

double
pow(double x, double y);
double
sqrt(double x);

double
ceil(double x);
double
floor(double x);

double
fmod(double x);

double
fabs(double x);
```

```C
#include <stdlib.h>

int
abs(int x);
long
labs(long x);

int
rand(void);
void
srand(unsigned int seed);

/* Usage example */
#include <stdlib.h>
#include <time.h>

srand(time(NULL));
int r = rand() % 100; /* 0~99 */

```

## Time
```C
#include <time.h>
/* TODO */
```

## va_list
```C
#include <stdarg.h>

void
va_start(va_list ap, last);

type
va_arg(va_list, type);

void
va_copy(va_list dest, va_list src);

void
va_end(va_list ap);
```

## Learning resource
- [cplusplus.com](http://www.cplusplus.com/reference/)
