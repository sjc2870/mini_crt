#include "mini_crt.h"

extern int main(int, char **);

/* @brief 1. initiliaze runtime env
          2. call main
          3. exit
  */
void mini_crt_entry(){
    int ret;
    int argc;
    char **argv;
    char *ebp = NULL;
    
    if(!mini_crt_heap_init()){
        exit(-1);
    }
    if(!mini_crt_io_init()){
        exit(-1);
    }
    // get ebp regisiter
    __asm__("movl %%ebp 0 \n\t":"=r"(ebp));
    argc = *(int*)(ebp+4);
    argv = (char **)(ebp+8);

    ret = main(argc, argv);
    exit(ret);
}

void exit(int exit_code){
    int eax, ebx;
    eax = 1;
    ebx = exit_code;
    
    __asm__(
            "movl $1,%%eax \n\t"
            "movl %0, %%ebx \n\t"
            "int $0x80"
            ::"m"(exit_code));
}
