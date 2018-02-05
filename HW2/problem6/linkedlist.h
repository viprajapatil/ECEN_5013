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

void destroy(struct info* head);
struct info* insert_at_beginning(struct info* head, uint32_t userdata);
struct info* insert_at_end(struct info *head, uint32_t userdata);
struct info* insert_at_position(struct info *head, uint32_t userdata, int index);
struct info* delete_from_beginning(struct info *head);
struct info* delete_from_end(struct info *head);
struct info* delete_from_position(struct info *head, int index);
int size(struct info* head);
void display(struct info* head);
uint32_t peak(struct info* head, int index);
        
        
#endif
