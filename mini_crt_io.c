#include "mini_crt.h"
int read(int fd, void *buf, size_t size){
    int ret = 0;

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
    int ret = 0;

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

int open(const char *pathname, int flags, int mode){
    int fd;

    __asm__("mov $5, %%eax \n\t"
            "mov %1, %%eax \n\t"
            "mov %2, %%ebx \n\t"
            "mov %3, %%ecx \n\t"
            "int $0x80     \n\t"
            "mov %%eax, %0 \n\t"
            :"=m"(fd):"m"(pathname),"m"(flags),"m"(mode)
            );

    return fd;
}

int close(int fd){
    int ret = 0;

    __asm__("mov $6, %%eax \n\t"
            "mov %1, %%ebx \n\t"
            "int $0x80     \n\t"
            "mov %%eax, %0 \n\t"
            :"=m"(ret):"m"(fd));

    return ret;
}

int seek(int fd, int offset, int mode){
    int ret = 0;
  
    __asm__("mov $19, %%eax \n\t"
            "mov %1, %%ebx \n\t"
            "mov %2, %%ecx \n\t"
            "mov %3, %%edx \n\t"
            :"=m"(ret):"m"(fd), "m"(offset), "m"(mode));
  
    return ret;
}

int fopen(const char *pathname, const char *mode){
    int fd = -1;
    int flags = 0;
    int access = 0;

// from fcntl.h
#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
#define O_CREAT 0100
#define O_TRUNC 01000
#define O_APPEND 02000

    if(strcmp(mode,"w") == 0){
        access = access | O_WRONLY | O_CREAT | O_TRUNC;
    }
    if(strcmp(mode, "w+") == 0){
        access = access | O_RDWR | O_CREAT | O_TRUNC;
    }
    if(strcmp(mode, "r") == 0){
        access = access | O_RDONLY;
    }
    if(strcmp(mode, "r+") == 0){
        access = access | O_RDWR | O_CREAT;
    }

    fd = open(pathname, flags, access);
    return  fd;
}

int fclose(FILE *fp){
    return close((int)fp);
}
int fread(void *ptr, size_t size, size_t nmemb, FILE *stream){
    return read((int)stream, ptr, size*nmemb);
}
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream){
    return write((int)stream, ptr, size*nmemb);
}
int fseek(FILE *fp, int offset, int set){
    return seek((int)fp, offset, set);
}
