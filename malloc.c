#include "mini_crt.h"
#define HEAP_SIZE 1024*1024*32
#define ADDR_ADD(base, size)

#ifndef NULL
#define NULL 0
#endif

enum state_t {FREE, USED};

typedef struct header{
    state_t state;
    unsigned int size;
    struct header *prev;
    struct header *next;
}header;

#define HEADER_SIZE sizeof(header)

header *free_list = NULL;
header *used_list = NULL;

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
    end = (void *)brk(((char*)base)+HEAP_SIZE);
    free_list = base;
    free_list->size = HEAP_SIZE;
    free_list->next = NULL;
    free_list->prev = NULL;
    free_list->state = FREE;
}


void *malloc(int size){
    if(size <= 0){
        //printf("error:error parameters in malloc\n");
        return NULL;
    }

    header *free_head = free_list;
    while(free_head && free_head->size < size+HEADER_SIZE){
        free_head = free_head->next;
    }
    //heap space has been used up
    if(free_head == NULL){
        //printf("error:heap space has been used up\n");
        return NULL;
    }
    header *found;
    if(free_head->size >= (size+HEADER_SIZE)){
        found = free_head;
        header *next = ((char*)free_head)+size+HEADER_SIZE;
        next->prev = free_head->prev;
        next->next = free_head->next;
        if(free_head->next){
            free_head->next->prev = next;
        }
        if(free_head->prev){
            free_head->prev->next = next;
        }
        next->size = free_head->size - size - HEADER_SIZE;
        next->state = FREE;

        found->next = used_list->next;
        found->prev = NULL;
        found->state = USED;
        found->size = size;
        if(used_list->next){
            used_list->next->prev = found;
        }
        used_list = found;
    }
    return(void*)((char*)found+ HEADER_SIZE);
}

/* @brief:  1. move block that will be freed to free_list
*/
void free(void *addr){
    header *head = (header*)((char*)addr-HEADER_SIZE);
}
