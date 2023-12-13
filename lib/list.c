#include <stdlib.h>
#include <string.h>

#include "list.h"

list* list_new(size_t data_size) {
    list* l = (list*)malloc(sizeof(list));
    l->head = NULL;
    l->data_size = data_size;
    l->length = 0;
    return l;
}

void list_add(list* l, void* data) {
    list_node* ln = (list_node*)malloc(sizeof(list_node));
    ln->data = malloc(l->data_size);
    memcpy(ln->data, data, l->data_size);
    ln->next = l->head;

    l->head = ln;
    l->length++;
}

void list_free(list* l) {
    list_node* node = l->head;
    while (node != NULL) {
        list_node* temp = node->next;
        free(node->data);
        free(node);
        node = temp;
    }
    free(l);
}

int list_length(list* l) {
    return l->length;
}
