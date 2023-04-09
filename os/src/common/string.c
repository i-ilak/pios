#include "common/string.h"

size_t strlen(const char* str)
{
    const char* char_ptr;

    for(char_ptr = str; *char_ptr; ++char_ptr);

    return (char_ptr-str);
}

int strcmp(const char* s1, const char* s2)
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
    int i, j;
    char tmp;

    for(i = 0, j=strlen(str)-1; i < j; i++, j--)
    {
        tmp = str[i];
        str[i] = str[j];
        str[j]= tmp;
    }
}