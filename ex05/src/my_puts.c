#include <stdio.h>
#include "test.h"

int my_puts(const char* s)
{
    int cnt;
    cnt = 0;
    while(s[cnt])
    {
        if (putchar(s[cnt]) == EOF)
            return EOF;
        cnt++;
    }

    if (putchar('\n') == EOF)
        return EOF;

    return 1;
}
