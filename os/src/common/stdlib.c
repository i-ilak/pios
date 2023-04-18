#include "common/stdlib.h"
#include "common/string.h"

#include <stdint.h>

// raspi model 1 does not have division instruction, so we need to define our own
__inline__ uint32_t div(uint32_t dividend, uint32_t divisor)
{
#if MODEL_0 || MODEL_1
    // Use long division, but in binary.  Copied from Stack overflow...
    uint32_t denom = divisor;
    uint32_t current = 1;
    uint32_t answer = 0;

    if(denom > dividend)
        return 0;

    if(denom == dividend)
        return 1;

    while(denom <= dividend)
    {
        denom <<= 1;
        current <<= 1;
    }

    denom >>= 1;
    current >>= 1;

    while(current != 0)
    {
        if(dividend >= denom)
        {
            dividend -= denom;
            answer |= current;
        }
        current >>= 1;
        denom >>= 1;
    }
    return answer;
#else
    return dividend / divisor;
#endif
}

__inline__ divmod_t divmod(uint32_t dividend, uint32_t divisor)
{
    divmod_t res;
#ifdef MODEL_1
    res.div = div(dividend, divisor);
    res.mod = dividend - res.div * divisor;
#else
    res.div = dividend / divisor;
    res.mod = dividend % divisor;
#endif
    return res;
}

void *memcpy(void *dest, const void *src, unsigned long bytes)
{
    char *d = dest;
    const char *s = src;
    while(bytes--)
    {
        *d++ = *s++;
    }
    return dest;
}

void bzero(void *dest, unsigned long bytes) { memset(dest, 0, bytes); }

void *memset(void *dest, int c, unsigned long bytes)
{
    uint8_t *d = dest;
    while(bytes--)
    {
        *d++ = c;
    }
    return dest;
}

char *itoa(int num, int base)
{
    static char intbuf[33];
    uint32_t j = 0, isneg = 0, i;
    divmod_t divmod_res;

    if(num == 0)
    {
        intbuf[0] = '0';
        intbuf[1] = '\0';
        return intbuf;
    }

    if(base == 10 && num < 0)
    {
        isneg = 1;
        num = -num;
    }
    else if(base == 2 && num < 0)
    {
        isneg = 1;
        // Convert absolute value to two's complement
        num = (~num) + 1;
    }

    i = (uint32_t)num;

    while(i != 0)
    {
        divmod_res = divmod(i, base);
        intbuf[j++] = (divmod_res.mod) < 10 ? '0' + (divmod_res.mod)
                                            : 'a' + (divmod_res.mod) - 10;
        i = divmod_res.div;
    }

    if(base == 16)
    {
        intbuf[j++] = 'x';
        intbuf[j++] = '0';
    }
    else if(base == 8)
    {
        intbuf[j++] = '0';
    }
    else if(base == 2)
    {
        intbuf[j++] = 'b';
        intbuf[j++] = '0';
    }

    if(isneg)
        intbuf[j++] = '-';

    intbuf[j] = '\0';
    j--;
    i = 0;
    while(i < j)
    {
        isneg = intbuf[i];
        intbuf[i] = intbuf[j];
        intbuf[j] = isneg;
        i++;
        j--;
    }

    return intbuf;
}

int atoi(const char *nptr)
{
    int result = 0;
    int position = 1;

    const char *p = nptr;
    while(*p)
    {
        ++p;
    }
    for(--p; p >= nptr; p--)
    {
        if(*p < 0x30 || *p > 0x39)
        {
            break;
        }
        else
        {
            result += (position) * (*p - 0x30);
            position *= 10;
        }
    }
    result = ((nptr[0] == '-') ? -result : result);
    return result;
}