#include "mini_crt.h"

#define va_list char*
#define va_start(ap, arg)       (ap=(va_list)&ap+sizeof(arg))
#define va_arg(ap, t)           (*(t*)((ap+=sizeof(t))-sizeof(t)))
#define va_end(ap)              (ap=(va_list)0)

int fputc(int c, FILE *stream){
    if(fwrite(&c, 1, 1, stream) != 1)
        return EOF;
    return 0;
}

int fputs(const char *str, FILE *stream){
    int len = strlen(str);
    if(fwrite(str, 1, len, stream) != len)
        return EOF;
    return len;
}

//遇到%设置翻译模式，根据翻译模式和当前字符来决定当前的行为
//如 %%则退出翻译模式，%d则翻译并输出之后退出翻译模式
int vfprintf(FILE *stream, const char *format, va_list arglist){
    int translating = 0;
    int ret = 0;
    const char *p = 0;
    for(p = format; *p != '\0'; ++p){
        switch(*p){
            case '%':
                if(!translating)
                    translating = 1;
                else{
                    if(fputc('%', stream) < 0){
                        return EOF;
                    }
                    ++ret;
                    translating = 0;
                }
                break;
            case 'd':
                if(translating){
                    char buf[16] = {0};
                    translating = 0;
                    itoa(va_arg(arglist, int), buf, 10);
                    if(fputs(buf, stream) < 0){
                        return EOF;
                    }
                    ret += strlen(buf);
                }else if(fputc('d', stream) < 0){
                    return EOF;
                }else{
                    ++ret;
                }
                break;
            case 's':
                if(translating){
                    const char *str = va_arg(arglist, const char*);
                    translating = 0;
                    if(fputs(str, stream) < 0){
                        return  EOF;
                    }
                    ret += strlen(str);
                }else if(fputc('s', stream) < 0){
                    return  EOF;
                }else{
                    ++ret;
                }
                break;
            default:
                if(translating)
                    translating = 0;
                if(fputc(*p, stream) < 0){
                    return  EOF;
                }else{
                    ++ret;
                }
                break;
        }
    }
    return ret;
}

int printf(const char *fmt, ...){
    va_list(arglist);
    va_start(arglist, fmt);
    return vfprintf(stdout, fmt, arglist);
}

int main(){
    printf("aaaaa\n");
}
