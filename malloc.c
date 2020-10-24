#define HEAP_SIZE 1024*1024*32
#define ADDR_ADD(base, size)

enum state_t{FREE,UESD};

typedef struct header{
    state_t state;
    unsigned int size;
    struct header *prev;
    struct header *next;
}header;

static int brk(void *end_data_segment){
    int ret = 0;
    __asm__("movl $45, %%eax"
            "movl %1, %%ebx"
            "int $0x80"
            "movl %%eax,$0"
            :"=r"(ret):"m"(end_data_segment));
}

int mini_crt_heap_init(){
    void *base, *end;

    base = (void*)brk(0);
    end = (void *)
}
