#ifndef UTIL_THREAD_LIST_H_
#define UTIL_THREAD_LIST_H_
#include <threads.h>
#include <utility.h>

typedef struct ListS ListS;
/**
 * @brief constructor for list
 * @param [in] free_fun pointer to function to free element data
 * @param [in] comp_fun pointer to function to compare data
*/
ListS* util_list_create(void (*free_fun)(void*), int (*comp_fun)(void* a, void* b));
/**
 * @brief destructor for list
 * @param [in] list pointer to List
 *
*/
int util_list_destroy(ListS* list);
/**
 * @brief adding element to end of list
 * @param [in] list pointer to list
 * @param [in] data pointer to data
*/
int util_list_push_back(ListS* list, void* data);
/**
 * @brief adding element at begining of list
 * @param [in] list pointer to list
 * @param [in] data pointer to data
*/
int util_list_push_front(ListS* list, void* data);
/**
 * @brief adding element to index specify by index
 * @param [in] list pointer to list
 * @param [in] data pointer to data
 * @param [in] index number of element to be set
*/
int util_list_push_index(ListS* list, void* data, size_t index);
/**
 * @brief returning and erasing element from back of list
 * @param [in] list pointer to list
*/
void* util_list_pop_back(ListS* list);
/**
 * @brief returning and erasing element from begin of list
 * @param [in] list pointer to list
*/
void* util_list_pop_front(ListS* list);
/**
 * @brief returning and erasing element from index of list
 * @param [in] list pointer to list
 * @param [in] index number of element to returning
*/
void* util_list_pop_index(ListS* list, size_t index);
/**
 * @brief returning pointer to element data from back of list
 * @param [in] list pointer to list
*/
void* util_list_get_back(ListS* list);
/**
 * @brief returning pointer to element data from begin of list
 * @param [in] list pointer to list
*/
void* util_list_get_front(ListS* list);
/**
 * @brief returning pointer to element data from index of list
 * @param [in] list pointer to list
 * @param [in] index number of element to returning
*/
void* util_list_get_index(ListS* list, size_t index);
/**
 * @brief returning index of element which containt data, -1 when not found
 * @param [in] list pointer to list
 * @param [in] data pointer to data which will be find
*/
int util_list_find(ListS* list, void* data);
/**
 * @brief returning size of list or 0 when list is not created
 * @param [in] list pointer to list
*/
size_t util_list_get_size(ListS* list);

#endif //UTIL_THREAD_LIST_H_
