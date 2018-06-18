#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void spacepr(const char *a, const char *b, size_t len_pr){
    size_t len, i;
    len = 0;

    for (i = 0; a + i != b; ++i){
        len = len * 10 + (a[i] - '0');
    }

    if (len < len_pr)
      return;

    len -= len_pr;

    for (i = 0; i < len; ++i){
        putchar(' ');
    }
}

void nullpr(const char *a, const char *b, size_t len_pr){
    size_t len, i;
    len = 0;

    for (i = 0; a + i != b; ++i){
        len = len * 10 + (a[i] - '0');
    }

    if (len < len_pr)
      return;

    len -= len_pr;

    for (i = 0; i < len; ++i){
        putchar('0');
    }
}

void cstrpr(const char *s){
    size_t i;

    for (i = 0; i < strlen(s); ++i){
        putchar(s[i]);
    }
}

size_t intlen(int n){
    if (!n){
        return 1;
    }

    int len;
    len = 0;

    while (n){
        ++len;
        n /= 10;
    }

    return len;
}

const char *itocstr(int n){
    int neg = (n < 0);

    if (neg){
        n = -n;
    }

    size_t nlen;
    nlen = intlen(n);
    nlen += neg;
    char *cstr = malloc(nlen + 1);

    if (neg){
        cstr[0] = '-';
    }

    cstr[nlen] = '\0';

    int i;
    for (i = nlen - 1; i >= 0 + neg; --i){
        cstr[i] = ((n % 10) + '0');
        n /= 10;
    }
    return cstr;
}

void my_printf(const char *mask, ...){

    va_list argptr;
    va_start(argptr, mask);

    size_t fpos = -1, i, flag = 0, pos_0 = -1;
    for (i = 0; i < strlen(mask); ++i){
        if (fpos == -1){
            if (mask[i] == '%'){
                fpos = i;
                if (*(++mask) == '0'){
                    flag = 1;
                } else{
                    --mask;
                    flag = 0;
                }
            } else {
                putchar(mask[i]);
            }
        } else {
            if (isdigit(mask[i])){
                continue;
            }
            if (mask[i] == '%'){
                putchar('%');
                fpos = -1;
                continue;
            }
            if (mask[i] == 's'){
                char *t = va_arg(argptr, char *);
                if (flag == 0){
                  spacepr(mask + fpos + 1, mask + i, strlen(t));
                } else {
                  nullpr(mask + pos_0 + 1, mask + i, strlen(t));
                }
                cstrpr(t);
                free(t);
                fpos = -1;
                continue;
            }
            if (mask[i] == 'd'){

              char *t = itocstr(va_arg(argptr, int));
              if (flag == 0){
                spacepr(mask + fpos + 1, mask + i, strlen(t));
              } else {
                nullpr(mask + pos_0 + 1, mask + i, strlen(t));
              }
              cstrpr(t);
              free(t);
              fpos = -1;
              continue;
            }

            fpos = -1;
            putchar(mask[i]);
        }
    }
    va_end(argptr);
}