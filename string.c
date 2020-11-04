#include <stdio.h>
char *itoa(int n, char *o_str, int base){
    char digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *str = o_str, *head = o_str;

    if(!str || base < 2 || base > 36)
        return NULL;
    if(base != 10 && n < 0)
        return NULL;
    if(n == 0){
        *str++ = '\0';
        *str = 0;
        return str;
    }
    if(base == 10 && n < 0){
        *str++ = '-';
        n *= -1;
    }
    while(n){
        *str++ = digit[n % base];
        n /= base;
    }
    *str = 0;
    if(*o_str == '-'){
        ++head;
    }
    for(--str; head < str; ++head, --str){
        char tmp = *head;
        *head = *str;
        *str = tmp;
    }
    return o_str;
}

int strlen(const char *str){
    int len = 0;
    while(*str != '\0'){
        str++;
        len++;
    }
    return len;
}

int strcmp(char *o_str1, char *o_str2){
    char *str1 = o_str1, *str2 = o_str2;
    while(*str1!='\0' && *str2!='\0' && *str1 == *str2){
        ++str1;
        ++str2;
    }
    return *str1-*str2;
}

char *strcat(char *o_dst, char *o_src){
    char *dst = o_dst, *src = o_src;

    while(*dst!='\0'){
        ++dst;
    }
    while(*src != '\0'){
        *dst = *src;
        ++dst;
        ++src;
    }

    *dst = '\0';
    return o_dst;
}
