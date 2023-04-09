#include "common/stdlib.h"
#include "common/string.h"

char* itoa(int value)
{
    int i, sign;

    /* Declare as static in order to return it */
    static char s[21];  // Biggest int, 10 digits long

    sign = value;
    if (value < 0)
        value = -value;
    
    i = 0;

    // digits are in reverse order
    do 
    {
        s[i] = value % 10 + '0';  // (int)'0'==48;
        i++;
        value/=10;
    } while (value > 0);

    if (sign < 0) {
		s[i] = '-';
		i++;
	}
	s[i] = '\0';

	strrev(s);

	return s;
}

int atoi(const char* str)
{
    int num = 0;

    while ((*str != '\0') && (*str >= '0' && *str <= '9')) {
		num = num * 10 + (*str - '0');
		str++;
	}

    return num;
}

void bzero(void * dest, int bytes) {
    memset(dest, 0, bytes);
}

void* memset(void* s, int c, size_t n)
{
    unsigned char* dst = s;

    while(n>0)
    {
        *dst = (unsigned char) c;
        dst++;
        n--;
    }
    return s;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    char* d = (char *) dest;
    const char *s = (const char*) src;

    while (n > 0) {
		*(d++) = *(s++);
		n--;
	}
	return dest;
}