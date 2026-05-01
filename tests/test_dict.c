#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <structs/dict/dict.h>

static void test_col(void) {
        dict *d = dict_construct();
        int val1 = 1, val2 = 2;
        dict_insert(d, "key1", &val1, sizeof(int));
        dict_insert(d, "key2", &val2, sizeof(int));
        
        int *res1 = (int*)dict_search(d, "key1");
        int *res2 = (int*)dict_search(d, "key2");
        assert(res1 && *res1 == 1);
        assert(res2 && *res2 == 2);
        
        dict_destruct(d);
        fprintf(stdout, "[%s]: debug passed test_col\n", __func__);
}

static void test_abs(void) {
        dict *d = dict_construct();
        void *res = dict_search(d, "absent_key");
        assert(res == NULL);
        dict_destruct(d);
        fprintf(stdout, "[%s]: debug passed test_abs\n", __func__);
}

static void test_rm(void) {
        dict *d = dict_construct();
        int val = 42;
        dict_insert(d, "remove_me", &val, sizeof(int));
        assert(dict_search(d, "remove_me") != NULL);
        
        dict_remove(d, "remove_me");
        assert(dict_search(d, "remove_me") == NULL);
        
        dict_destruct(d);
        fprintf(stdout, "[%s]: debug passed test_rm\n", __func__);
}

int main(void) {
        fprintf(stdout, "[%s]: debug running dict tests\n", __func__);
        test_col();
        test_abs();
        test_rm();
        fprintf(stdout, "[%s]: debug all dict tests passed\n", __func__);
        return 0;
}
