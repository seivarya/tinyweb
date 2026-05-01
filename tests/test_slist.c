#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <structs/slist/slist.h>

static void test_rev_one(void) {
        slist *l = slist_construct();
        int val = 42;
        slist_insert(l, 0, &val, sizeof(int));
        
        slist_reverse(l);
        
        assert(l->length == 1);
        assert(l->head != NULL);
        assert(*(int*)l->head->data == 42);
        
        slist_destruct(l);
        fprintf(stdout, "[%s]: debug passed test_rev_one\n", __func__);
}

static void test_rev_even(void) {
        slist *l = slist_construct();
        int val1 = 1, val2 = 2;
        slist_insert(l, 0, &val2, sizeof(int));
        slist_insert(l, 0, &val1, sizeof(int));
        
        slist_reverse(l);
        
        assert(l->length == 2);
        assert(*(int*)slist_fetch_data(l, 0) == 2);
        assert(*(int*)slist_fetch_data(l, 1) == 1);
        
        slist_destruct(l);
        fprintf(stdout, "[%s]: debug passed test_rev_even\n", __func__);
}

int main(void) {
        fprintf(stdout, "[%s]: debug running slist tests\n", __func__);
        test_rev_one();
        test_rev_even();
        fprintf(stdout, "[%s]: debug all slist tests passed\n", __func__);
        return 0;
}
