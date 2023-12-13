#ifndef LIST_H
#define LIST_H

typedef struct list_node {
    void* data;
    struct list_node* next;
}  list_node;

typedef struct list {
    int length;
    size_t data_size;
    list_node* head;
} list;

list* list_new(size_t data_size);

void list_add(list* l, void* data);

void list_free(list* l);

int list_length(list* l);

#endif
