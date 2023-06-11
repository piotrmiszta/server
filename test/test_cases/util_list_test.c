#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmocka.h>
#include "util_list.h"

typedef struct test {
    int k;
}test;

static void push_pop_back (void** state) {
    ListS* list = util_list_create(free, NULL);
    for(int i = 0; i < 10; i++) {
        test* temp;
        temp = calloc(1 , sizeof(test));
        temp->k = i;
        util_list_push_back(list, temp);
    }
    assert_int_equal((int)util_list_get_size(list), 10);
    for(int i = 0; i < 10; i++) {
        test* k = util_list_pop_front(list);
        assert_int_equal(k->k, i);
        free(k);
    }
    util_list_destroy(list);
}

static void push_pop_front (void** state) {
    ListS* list = util_list_create(free, NULL);
    for(int i = 0; i < 10; i++) {
        test* temp;
        temp = calloc(1 , sizeof(test));
        temp->k = i;
        util_list_push_front(list, temp);
    }
    assert_int_equal((int)util_list_get_size(list), 10);
    for(int i = 0; i < 10; i++) {
        test* k = util_list_pop_back(list);
        assert_int_equal(k->k, i);
        free(k);
    }
    util_list_destroy(list);
}

static void push_pop_index (void** state) {
    ListS* list = util_list_create(free, NULL);
    for(int i = 0; i < 10; i++) {
        test* temp;
        temp = calloc(1 , sizeof(test));
        temp->k = i;
        util_list_push_back(list, temp);
    }
    assert_int_equal((int)util_list_get_size(list), 10);
    for(int i = 0; i < 9; i++) {
        test* k = util_list_pop_index(list, 1);
        assert_int_equal(k->k, i+1);
        free(k);
    }
    assert_int_equal((int)util_list_get_size(list), 1);
    util_list_destroy(list);
}

static void push_pop_index_2 (void** state) {
    ListS* list = util_list_create(free, NULL);
    for(int i = 0; i < 10; i++) {
        test* temp;
        temp = calloc(1 , sizeof(test));
        temp->k = i;
        util_list_push_back(list, temp);
    }
    for(int i = 0; i < 10; i++) {
        test* temp;
        temp = calloc(1 , sizeof(test));
        temp->k = i;
        util_list_push_index(list, temp, 5);
    }
    assert_int_equal((int)util_list_get_size(list), 20);

    for(int i = 9; i > -1; i--) {
        test* k = util_list_pop_index(list, 5);
        assert_int_equal(k->k, i);
        free(k);
    }
    assert_int_equal((int)util_list_get_size(list), 10);
    util_list_destroy(list);
}

static void push_destroy (void** state) {
    ListS* list = util_list_create(free, NULL);
    for(int i = 0; i < 10; i++) {
        test* temp;
        temp = calloc(1 , sizeof(test));
        temp->k = i;
        util_list_push_front(list, temp);
    }
    assert_int_equal((int)util_list_get_size(list), 10);
    util_list_destroy(list);
}



int main(void)
{
  const struct CMUnitTest tests[] = {
    unit_test(push_pop_back),
    unit_test(push_pop_front),
    unit_test(push_destroy),
    unit_test(push_pop_index),
    unit_test(push_pop_index_2),

  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}