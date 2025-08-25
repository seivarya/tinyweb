#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void) {
    struct queue queue = queue_constructor();

    printf("=== pushing elements ===\n");
    for (int i = 0; i < 20; i++) {
        int *val = malloc(sizeof(int));
        *val = i + 21;  // same as i + 23 - 2
        printf("push: %d\n", *val);
        queue.push(val, &queue);
    }

    printf("=== popping first 10 elements ===\n");
    for (int i = 0; i < 10; i++) {
        int *val = (int*) queue.pop(&queue);
        printf("pop: %d\n", *val);
        free(val);  // free the popped data
    }

    printf("=== popping remaining elements ===\n");
    while (queue.list.length > 0) {
        int *val = (int*) queue.pop(&queue);
        printf("pop: %d\n", *val);
        free(val);  // free the popped data
    }

    printf("all elements popped successfully\n");
    return 0;
}
