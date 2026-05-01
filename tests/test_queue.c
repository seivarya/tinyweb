#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <structs/queue/queue.h>

static void test_empty(void) {
        queue *q = queue_construct();
        assert(is_qempty(q) == 1);
        int val = 10;
        enqueue(q, &val, sizeof(int));
        assert(is_qempty(q) == 0);
        queue_destruct(q);
        fprintf(stdout, "[%s]: debug passed test_empty\n", __func__);
}

static void test_enq_deq(void) {
        queue *q = queue_construct();
        int val1 = 42;
        enqueue(q, &val1, sizeof(int));
        
        queue_node *front = get_front(q);
        assert(front != NULL);
        assert(*(int*)(front->data) == 42);
        
        dequeue(q);
        assert(is_qempty(q) == 1);
        
        queue_destruct(q);
        fprintf(stdout, "[%s]: debug passed test_enq_deq\n", __func__);
}

static void test_deq_one(void) {
        queue *q = queue_construct();
        int val = 99;
        enqueue(q, &val, sizeof(int));
        dequeue(q);
        assert(q->head == NULL);
        assert(q->tail == NULL);
        assert(q->length == 0);
        queue_destruct(q);
        fprintf(stdout, "[%s]: debug passed test_deq_one\n", __func__);
}

int main(void) {
        fprintf(stdout, "[%s]: debug running queue tests\n", __func__);
        test_empty();
        test_enq_deq();
        test_deq_one();
        fprintf(stdout, "[%s]: debug all queue tests passed\n", __func__);
        return 0;
}
