#include <stdbool.h>
#include <stdint.h>
#include "../drivers/display.h"
#include "./memory.h"

#define DYN_MEM_SIZE_TOTAL 4*1024
#define DYN_MEM_SIZE_NODE sizeof(dynamic_mem_node_t)

static uint8_t dynamic_memory[DYN_MEM_SIZE_TOTAL];

typedef struct dyn_mem_node {
    uint32_t size;
    bool in_use;
    struct dyn_mem_node *next;
    struct dyn_mem_node *prev;
} dynamic_mem_node_t;

static dynamic_mem_node_t *dynamic_node;

void dynamicMemory_init () {
    dynamic_node = (dynamic_mem_node_t *) dynamic_memory;
    dynamic_node->size = DYN_MEM_SIZE_TOTAL - DYN_MEM_SIZE_NODE;
    dynamic_node->next = NULL_P;
    dynamic_node->prev = NULL_P;
    return;
}

void *best_mem_block (dynamic_mem_node_t *dynmem, size_t size) {
    dynamic_mem_node_t *best_block = (dynamic_mem_node_t *) NULL_P;
    dynamic_mem_node_t *curr_block = dynmem;
    uint32_t best_block_size = DYN_MEM_SIZE_TOTAL + 1;

    while (curr_block) {
        if ((!curr_block->in_use) && 
            (curr_block->size >= (size + DYN_MEM_SIZE_NODE)) &&
            (curr_block->size <= best_block_size)) {
            best_block = curr_block;
            best_block_size = curr_block->size;
        }

        curr_block = curr_block->next;
    }

    return best_block;
}

void *merge_next (dynamic_mem_node_t *curr_node) {
    dynamic_mem_node_t *next_node = curr_node->next;

    if (next_node != NULL_P && !next_node->in_use) {
        curr_node->size += curr_node->next->size;
        curr_node->size += DYN_MEM_SIZE_NODE;
        curr_node->next = curr_node->next->next;

        if (curr_node->next != NULL_P) {
            curr_node->next->prev = curr_node;
        }
    }

    return curr_node;
}

void *dissolve_current (dynamic_mem_node_t *curr_node) {
    dynamic_mem_node_t *prev_node = curr_node->prev;

    if (prev_node != NULL_P && !prev_node->in_use) {
        prev_node->size += curr_node->size;
        prev_node->size += DYN_MEM_SIZE_NODE;
        prev_node->next = curr_node->next;

        if (curr_node->next != NULL_P) {
            curr_node->next->prev = prev_node;
        }
    }

    return prev_node;
}

void *mem_alloc (size_t size) {
    dynamic_mem_node_t *best_block = (dynamic_mem_node_t *) best_mem_block(dynamic_node, size);

    if (best_block != NULL_P) {
        best_block->size = best_block->size - size - DYN_MEM_SIZE_NODE;

        dynamic_mem_node_t *mem_node = (dynamic_mem_node_t *) (((uint8_t *) best_block) +
                                                                DYN_MEM_SIZE_NODE + 
                                                                best_block->size);
        mem_node->size = size;
        mem_node->in_use = true;
        mem_node->next = best_block->next;
        mem_node->prev = best_block;

        if (best_block->next != NULL_P) {
            best_block->next->prev = mem_node;
        }

        best_block->next = mem_node;

        return (void *) ((uint8_t *) mem_node + DYN_MEM_SIZE_NODE);
    }

    return NULL_P;
}

void mem_cpy (char *source, char *dest, int nbytes) {
    int i;

    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }

    return;
}

void mem_free (void *p) {
    if (p == NULL_P) { return; }

    dynamic_mem_node_t *curr_node = (dynamic_mem_node_t *)((uint8_t *) p - DYN_MEM_SIZE_NODE);

    if (curr_node == NULL_P) { return; }

    curr_node->in_use = false;

    curr_node = merge_next(curr_node);
    dissolve_current(curr_node);

    return;
}

void* alloc (int n) {
    int *p = (int *) mem_alloc(n * sizeof(int));

    if (p == NULL_P) {
        string_print("Out of Memory.\n");
        newline_print();
    } 

    return p;
}


