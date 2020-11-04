#ifndef MINI_CRT_H
#define MINI_CRT_H
#define NULL 0
#define size_t unsigned int
typedef int FILE;

int mini_crt_heap_init();
int mini_crt_io_init();
void exit(int);
void *malloc(int size);
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
int fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif
