#include "common/string.h"

uint32_t strlen(char* str)
{
    const char* char_ptr;

    for(char_ptr = str; *char_ptr; ++char_ptr);

    return (char_ptr-str);
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