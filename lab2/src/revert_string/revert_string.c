#include "revert_string.h"


void RevertString(char *str)
{
    char  c;
    char* s0 = str - 1;
    char* s1 = str;
    while (*s1) ++s1;


    while (s1-- > ++s0)
    {
        c = *s0;
        *s0 = *s1;
        *s1 =  c;
    }
}