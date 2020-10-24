//#include "mini_crt.h"
#define size_t unsigned int
int read(int fd, void *buf, size_t size){
    int ret;
    __asm__("mov $3, %%eax \n\t"
            "mov %1, %%ebx \n\t"
            "mov %2, %%ecx \n\t"
            "mov %3, %%edx \n\t"
            "int $0x80 \n\t"
            "mov %%eax, %0 \n\t"
            :"=m"(ret)
            :"m"(fd), "m"(buf), "m"(size));
    
    return ret;
}

int write(int fd, const void *buf, size_t size){
    int ret;
    __asm__("mov $4, %%eax \n\t"
            "mov %1, %%ebx \n\t"
            "mov %2, %%ecx \n\t"
            "mov %3, %%edx \n\t"
            "int $0x80 \n\t"
            "mov %%eax, %0 \n\t"
            :"=m"(ret)
            :"m"(fd), "m"(buf), "m"(size));
    return ret;
}

int main(){
    char buf[64] = {0};
    read(0, buf, 3);
    write(1, buf, 3);
}