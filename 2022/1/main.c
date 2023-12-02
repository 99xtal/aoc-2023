#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 100

typedef struct node {
    int data;
    struct node* next;
} node;

int compare(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}

int main() {
    int local_sum = 0;
    char line[MAX_LINE_SIZE];
    node* list = NULL;

    while (fgets(line, MAX_LINE_SIZE, stdin) != NULL) {
        if (atoi(line) == 0) {
            node* n = (node*)malloc(sizeof(node));
            n->data = local_sum;
            n->next = list;
            list = n;
            local_sum = 0;
        } else {
            local_sum += atoi(line);
        }
    }

    int c = 0;
    for (node* p = list; p != NULL; p = p->next) {
        c++;
    }

    int sums[c];
    int i = 0;
    for (node* p = list; p != NULL; p = p->next) {
        sums[i] = p->data;
        i++;
    }

    qsort(sums, c, sizeof(int), compare);

    printf("%d\n", sums[0] + sums[1] + sums[2]);
}