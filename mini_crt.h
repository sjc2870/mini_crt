#ifndef MINI_CRT_H
#define MINI_CRT_H
#define NULL 0
#define size_t unsigned int
int mini_crt_heap_init();
int mini_crt_io_init();
void exit(int);
void *malloc(int size);
void free(void*);

int read(int fd, void* buf, size_t size);
int write(int fd, const void *buf, size_t size);
int fopen(const char *pathname, int flags, int mode);
int fclose(int fd);
#endif