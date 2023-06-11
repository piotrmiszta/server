#ifndef UTIL_THREAD_LIST_H_
#define UTIL_THREAD_LIST_H_
#include <threads.h>
#include <utility.h>

typedef struct ListS ListS;

ListS* util_list_create(void (*free_fun)(void*), int (*comp_fun)(void*));
int util_list_destroy(ListS* list);

int util_list_push_back(ListS* list, void* data);
int util_list_push_front(ListS* list, void* data);
int util_list_push_index(ListS* list, void* data, size_t index);

void* util_list_pop_back(ListS* list);
void* util_list_pop_front(ListS* list);
void* util_list_pop_index(ListS* list, size_t index);

void* util_list_get_back(ListS* list);
void* util_list_get_front(ListS* list);
void* util_list_get_index(ListS* list, size_t index);

int util_list_find(ListS* list, void* data);
size_t util_list_get_size(ListS* list);

#endif //UTIL_THREAD_LIST_H_
