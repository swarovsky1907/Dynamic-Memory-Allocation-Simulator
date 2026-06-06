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

// Initialize the heap
void init_heap() {
    // Entire heap starts as one large free block
    freeList = (Block*)heap;
    freeList->size = HEAP_SIZE - sizeof(Block);
    freeList->free = 1;
    freeList->next = NULL;
}

//Split heap based on requirement if available block is larger than required size
void split(Block* block, int size) {
    // Create a new block after the allocated space
    Block* newBlock = (Block*)((char*)block + sizeof(Block) + size);

    // Remaining size after splitting
    newBlock->size = block->size - size - sizeof(Block);
    newBlock->free = 1;
    newBlock->next = block->next;

    // Update current block
    block->size = size;
    block->free = 0;
    block->next = newBlock;
}

// Allocates the smallest free block that can satisfy the request
void* allocate(int size) {

    Block* curr = freeList;

    // Stores the best block found so far
    Block* bestFit = NULL;

    // Search entire list
    while (curr != NULL) {

        if (curr->free && curr->size >= size) {

            // First suitable block found
            if (bestFit == NULL)
                bestFit = curr;

            // Better fit found
            if (curr->size < bestFit->size)
                bestFit = curr;
        }

        curr = curr->next;
    }

    // No suitable block found
    if (bestFit == NULL)
        return NULL;

    // Split block if enough extra space exists
    if (bestFit->size > size + sizeof(Block))
        split(bestFit, size);

    // Mark allocated
    bestFit->free = 0;

    // Return memory after metadata
    return (void*)(bestFit + 1);
}


// Merge adjacent free blocks
void merge() {

    Block* curr = freeList;

    while (curr != NULL && curr->next != NULL) {

        // If both current and next blocks are free
        if (curr->free && curr->next->free) {

            // Combine them
            curr->size= curr->size+ curr->next->size + sizeof(Block);

            curr->next = curr->next->next;
        }
        else {
            curr = curr->next;
        }
    }
}

// Free a memory block
void free_block(void* ptr) {

    if (ptr == NULL)
        return;

    // Move back to block metadata
    Block* block = (Block*)ptr - 1;

    block->free = 1;

    // Merge neighbouring free blocks
    merge();
}

//Display entire heap memory list
void display() {

    Block* curr = freeList;

    printf("\nHeap Blocks:\n");

    while (curr != NULL) {

        printf("Size = %-4d | Free = %d\n",
               curr->size,
               curr->free);

        curr = curr->next;
    }
}

int main() {

    init_heap();

    // Create several allocated blocks
    void* p1 = allocate(300);
    void* p2 = allocate(100);
    void* p3 = allocate(200);
    void* p4 = allocate(50);

    printf("\nAfter Initial Allocations:\n");
    display();

    // Free two blocks of different sizes
    free_block(p1);   // 300-byte free block
    free_block(p3);   // 200-byte free block

    printf("\nAfter Freeing p1 (300) and p3 (200):\n");
    display();

    // If we want to allocate 150 bytes, first fit would pick 300 whereas best fit should pick 200.

    printf("\nAllocating 150 bytes...\n");

    void* p5 = allocate(150);

    printf("\nAfter Allocating 150 bytes:\n");
    display();

    return 0;
}