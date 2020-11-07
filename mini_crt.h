#ifndef __MINI_CRT_H__
#define __MINI_CRT_H__

#ifdef __cplusplus
extern "C"{
#endif

#define NULL 0
#define EOF -1

#define stdin ((FILE*)0)
#define stdout ((FILE*)1)
#define stderr ((FILE*)2)

typedef unsigned int size_t;
typedef int FILE;

int mini_crt_heap_init();
int mini_crt_io_init();
void exit(int);
void *malloc(size_t size);
void free(void*);

//string operation
int strcmp(const char *str1, const char *str2);
// io operation
int read(int fd, void* buf, size_t size);
int write(int fd, const void *buf, size_t size);
int open(const char *pathname, int flags, int mode);
int close(int fd);
int fopen(const char *pathname, const char *mode);
int fclose(FILE *fp);
int fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

#ifdef __cplusplus
}
#endif
#endif
