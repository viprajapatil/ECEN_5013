#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

struct node {
struct node * prev;
struct node * next;
};
struct info {
uint32_t data;
struct node obj;
};


// GET_LIST_CONTAINER
#define GET_LIST_CONTAINER(ptr, type, member) ({                \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})
        
        
#endif
