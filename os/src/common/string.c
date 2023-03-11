#include "common/string.h"

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

uint32_t strlen(char* str)
{
    const char* char_ptr;

    for(char_ptr = str; *char_ptr; ++char_ptr);

    return (char_ptr-str);
}

int32_t strcmp(const char* s1, const char* s2)
{
    while((*s1 != '\0') && (*s1 == *s2))
    {
        s1++;
        s2++;
    }

    /* Return the ASCII difference after convert. char* to unsigned char* */
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char* strcpy(char* dest, const char* src)
{
    if(dest == NULL)
        return NULL;

    char *tmp = dest;

	while (*src != '\0') {
		*(tmp++) = *(src++);
	}

	*tmp = '\0';

	return dest;
}

char* strcat(char* dest, const char* src)
{
    char* tmp = dest;

    while(*tmp != '\0')
        tmp++;

    while(*src != '\0')
        *(tmp++) = *(src++);

    *tmp = '\0';

    return dest;
}

void strrev(char* str)
{
    int32_t i, j;
    char tmp;

    for(i = 0, j=strlen(str); i < j; i++, j--)
    {
        tmp = str[i];
        str[i] = str[j];
        str[j]= tmp;
    }
}