#include <Lib/String.h>
#include <Core/Common.h>

char* PICO_NewString(const char* str)
{
    if (str == NULL || PICO_StrLen(str) == 0) { return PICO_Alloc(1); }
    char* out = PICO_Alloc(PICO_StrLen(str) + 1);
    PICO_StrConcat(out, str);
    return out;
}

size_t PICO_StrLen(const char* str)
{
    if (str == NULL) { return 0; }
    size_t l = 0;
    while (str[l] != 0) { l++; }
    return l;
}

char* PICO_StrConcat(char* str, const char* append)
{
    if (str == NULL) { return NULL; }
    if (append == NULL)  { return str; }
    size_t src_len = PICO_StrLen(append);
    size_t dest_len = PICO_StrLen(str);
    for (size_t i = 0; i < src_len; i++) { str[dest_len + i] = append[i]; }
    str[PICO_StrLen(str)] = 0;
    return str;
}

char* PICO_StrAppend(char* str, char c)
{
     if (str == NULL) { return NULL; }
    size_t len = PICO_StrLen(str);
    str[len] = (char)c;
    str[len + 1] = 0;
    return str;
}

int PICO_StrCompare(const char* str1, const char* str2)
{
    if (str1 == NULL && str1 != str2) { return 1; }
    while (*str1)
    {
        if (*str1 != *str2) { break; }
        str1++; str2++;
    }
    return *(char*)str1 - *(char*)str2;
}

bool PICO_StrEquals(const char* str1, const char* str2) { return PICO_StrCompare(str1, str2) == 0; }

char* PICO_StrCopy(char* dest, const char* src)
{
    if (dest == NULL) { return NULL; }
    if (src == NULL) { return NULL; }

    int i = 0;
    while (src[i] != 0) { dest[i] = src[i]; i++; }
    return dest;
}

char* PICO_StrRChr(const char* str, char c)
{
    char *rtnval = 0;
    do { if (*str == c) { rtnval = (char*)str; } } while (*str++);
    return (rtnval);
}

char** PICO_StrSplit(const char* str, char delim, size_t* count)
{
    if (str == NULL) { return NULL; }
    if (PICO_StrLen(str) == 0) { return NULL; }

    int len = PICO_StrLen(str);
    uint32_t num_delimeters = 0;

    for(int i = 0; i < len - 1; i++) { if(str[i] == delim) { num_delimeters++; } }

    uint32_t arr_size = sizeof(char*) * (num_delimeters + 1);
    char** str_array = (char**)PICO_Alloc(arr_size);
    int str_offset = 0;

    int start = 0;
    int end = 0;
    while(end < len)
    {
        while(str[end] != delim && end < len) { end++; }

        char* substr = (char*)PICO_Alloc(end - start + 1);
        PICO_MemCopy(substr, str + start, end - start);
        start = end + 1;
        end++;
        str_array[str_offset] = substr;
        str_offset++;
    }
    *count = str_offset;
    return str_array;
}