#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 1024

// Structure representing a memory block
typedef struct Block {
    int size;               // Size of the block
    int free;               // 1 = free, 0 = allocated
    struct Block* next;     // Pointer to next block
} Block;

// Simulated heap memory
char heap[HEAP_SIZE];

// Head of the linked list
Block* freeList = NULL;

//Initialise heap
void init_heap() {
    // Entire heap starts as one large free block
    freeList = (Block*)heap;
    freeList->size = HEAP_SIZE - sizeof(Block);
    freeList->free = 1;
    freeList->next = NULL;
}

//Split heap based on requirement if available block is larger than required size
void split(Block* fitting_slot, int size) {
    // Create a new block after the allocated space
    Block* new_block = (void*)((void*)fitting_slot + size + sizeof(Block));

    // Remaining size after splitting
    new_block->size = fitting_slot->size - size - sizeof(Block);
    new_block->free = 1; //New free block
    new_block->next = fitting_slot->next;

    // Update current block
    fitting_slot->size = size;
    fitting_slot->free = 0; //Used block
    fitting_slot->next = new_block;
}

//Allocates first block with size larger than or equal to the required block size
void* allocate(int size) {
    Block* curr = freeList;

    while (curr != NULL) {
        if (curr->free && curr->size >= size) {
            if (curr->size > size + sizeof(Block)) {
                split(curr, size);
            }
            curr->free = 0;
            return (void*)(curr + 1);
        }
        curr = curr->next;
    }

    return NULL;
}

//Merge free blocks
void merge() {
    Block* curr = freeList;

    while (curr != NULL && curr->next != NULL) {
        if (curr->free && curr->next->free) {
            curr->size += curr->next->size + sizeof(Block);
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

//Free a block
void free_block(void* ptr) {
    if (!ptr) return;

    Block* block = (Block*)ptr - 1;
    block->free = 1;

    merge();
}

//Display entire heap memory list
void display() {
    Block* curr = freeList;
    printf("\nHeap Blocks:\n");

    while (curr != NULL) {
        printf("Size: %d | Free: %d\n", curr->size, curr->free);
        curr = curr->next;
    }
}

int main() {
    init_heap();

    void* p1 = allocate(200);
    void* p2 = allocate(100);
    void* p3 = allocate(50);

    display();

    free_block(p2);
    printf("\nAfter freeing p2:\n");
    display();

    free_block(p1);
    printf("\nAfter freeing p1 (should merge with p2):\n");
    display();

    free_block(p3);
    printf("\nAfter freeing all blocks:\n");
    display();

    return 0;
}