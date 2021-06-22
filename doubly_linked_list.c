//
// Created by Mateusz Pysera on 08/06/2021.
//

#include "doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

struct doubly_linked_list_t* dll_create() {
    struct doubly_linked_list_t * ddl = malloc(sizeof(struct doubly_linked_list_t));
    if (ddl == NULL) return NULL;
    ddl->head = NULL;
    ddl->tail = NULL;
    return ddl;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value) {
    if (dll == NULL) return 1;
    struct node_t * node = malloc(sizeof(struct node_t)); if (node == NULL) return 2;
    node->data = value;
    node->next = NULL;
    if (dll_is_empty(dll)) {
        node->prev = NULL;
        dll->head = node; dll->tail = node;
    } else {
        node->prev = dll->tail;
        dll->tail->next = node;
        dll->tail = node;
    }
    return 0;
}
int dll_push_front(struct doubly_linked_list_t* dll, int value) {
    if (dll == NULL) return 1;
    struct node_t * node = malloc(sizeof(struct node_t)); if (node == NULL) return 2;
    node->data = value;
    node->prev = NULL;
    if (dll_is_empty(dll)) {
        node->next = NULL;
        dll->head = node;
        dll->tail = node;
    } else {
        node->next = dll->head;
        dll->head->prev = node;
        dll->head = node;
    }
    return 0;
}
int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL || dll->head == NULL || dll->tail == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (dll_is_empty(dll)) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (err_code != NULL) *err_code = 0;
    int value = dll->head->data;
    struct node_t * free_after = dll->head;
    dll->head = dll->head->next;
    if (dll->head != NULL) dll->head->prev = NULL;
    else dll->tail = NULL;
    free(free_after);
    return value;
}
int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL || dll->head == NULL || dll->tail == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (dll_is_empty(dll)) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (err_code != NULL) *err_code = 0;
    int value = dll->tail->data;
    struct node_t * free_after = dll->tail;
    dll->tail = dll->tail->prev;
    if (dll->tail != NULL) dll->tail->next = NULL;
    else dll->head = NULL;
    free(free_after);
    return value;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL || dll->head == NULL || dll->tail == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (err_code != NULL) *err_code = 0;
    return dll->tail->data;
}
int dll_front(const struct doubly_linked_list_t* dll, int *err_code) {
    if (dll == NULL || dll->head == NULL || dll->tail == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (err_code != NULL) *err_code = 0;
    return dll->head->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll) {
    if (dll == NULL) return NULL;
    return dll->head;
}
struct node_t* dll_end(struct doubly_linked_list_t* dll) {
    if (dll == NULL) return NULL;
    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll) {
    if (dll == NULL) return -1;
    if (dll->head == NULL) return 0;
    struct node_t * node = dll->head;
    int counter = 0;
    do {
        node = node->next;
        counter++;
    } while (node != NULL);
    return counter;
}
int dll_is_empty(const struct doubly_linked_list_t* dll) {
    if (dll == NULL) return -1;
    if (dll->head == NULL) return 1;
    return 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if (dll == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (index >= (unsigned int) dll_size(dll)) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (err_code != NULL) *err_code = 0;
    struct node_t * node = dll->head;
    for (unsigned int i = 0; i < index; ++i) {
        node = node->next;
    }
    return node->data;
}
int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value) {
    if (dll == NULL) return 1;
    if (index > ( unsigned int ) dll_size(dll)) return 1;
    if (index == 0) { // insert at beginning
        if (dll_push_front(dll, value) != 0) return 2;
    } else if (index == ( unsigned int ) dll_size(dll)) { // insert at end
        if (dll_push_back(dll, value) != 0) return 2;
    } else { // insert at N
        struct node_t * node = malloc(sizeof(struct node_t)); if (node == NULL) return 2;
        struct node_t * tmp_node = dll->head;
        for (unsigned int i = 0; i < index - 1; ++i) {
            tmp_node = tmp_node->next;
        }
        node->data = value;
        node->prev = tmp_node;
        node->next = tmp_node->next;
        tmp_node->next->prev = node;
        tmp_node->next = node;
    }
    return 0;
}
int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if (dll == NULL) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (index > ( unsigned int ) dll_size(dll)) {
        if (err_code != NULL) *err_code = 1;
        return -1;
    }
    if (index == 0) { // remove at beginning
        return dll_pop_front(dll, err_code);
    } else if (index == ( unsigned int ) dll_size(dll) - 1) { // remove at end
        return dll_pop_back(dll, err_code);
    } else { // remove at N
        struct node_t * tmp_node = dll->head;
        for (unsigned int i = 0; i < index; ++i) {
            tmp_node = tmp_node->next;
        }
        int value = tmp_node->data;
        tmp_node->prev->next = tmp_node->next;
        tmp_node->next->prev = tmp_node->prev;
        free(tmp_node);
        if (err_code != NULL) *err_code = 0;
        return value;
    }
}

void dll_clear(struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->head == NULL || dll->tail == NULL) return;
    struct node_t * node = dll->head;
    struct node_t * tmp_node;
    do {
        tmp_node = node->next;
        free(node);
        node = tmp_node;
    } while (tmp_node != NULL);
    dll->tail = NULL;
    dll->head = NULL;
}

void dll_display(const struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->head == NULL || dll->tail == NULL) return;
    struct node_t *node = dll->head;
    do {
        printf("%d ", node->data);
        node = node->next;
    } while (node != NULL);
}
void dll_display_reverse(const struct doubly_linked_list_t* dll) {
    if (dll == NULL || dll->tail == NULL || dll->head == NULL) return;
    struct node_t * node = dll->tail;
    do {
        printf("%d ", node->data);
        node = node->prev;
    } while (node != NULL);
}
