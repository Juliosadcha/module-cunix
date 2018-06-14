#include <stdio.h>
#include <stdlib.h>
#include "test.h"
size_t intlen(int n){
    if (!n){
        return 1;
    }
    int len = 0;
    while (n){
        ++len;
        n /= 10;
    }
    return len;
}

char* my_itoa(int n){
    int neg = (n < 0);
    if (neg){
        n = -n;
    }
    size_t nlen = intlen(n);
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
