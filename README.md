# Memory Management System: First Fit & Best Fit

## Overview

This project implements and compares two dynamic memory allocation strategies used in Operating Systems:

* **First Fit Allocation**
* **Best Fit Allocation**

The system simulates heap memory using a linked list of memory blocks and demonstrates memory allocation, deallocation, block splitting, and block merging.

---

## Features

* Simulated heap memory management
* First Fit allocation strategy
* Best Fit allocation strategy
* Block splitting during allocation
* Memory deallocation
* Adjacent free block merging (coalescing)
* Heap status visualization

---

## Allocation Strategies

### First Fit

Allocates the first free block that is large enough to satisfy the memory request.

**Advantages:**

* Fast allocation
* Simple implementation

### Best Fit

Allocates the smallest free block that can satisfy the memory request.

**Advantages:**

* Better memory utilization
* Reduced memory wastage

---

## Data Structure

Each memory block is represented using a linked list node containing:

* Block size
* Allocation status (free/allocated)
* Pointer to the next block

---

## Technologies Used

* C Programming
* Linked Lists
* Dynamic Memory Allocation

---

## Compilation

### First Fit

```bash
gcc first_fit.c -o first_fit
./first_fit
```

### Best Fit

```bash
gcc best_fit.c -o best_fit
./best_fit
```

---

## Learning Outcomes

This project demonstrates:

* Heap Management
* Dynamic Memory Allocation
* First Fit and Best Fit Algorithms
* Memory Fragmentation
* Block Splitting and Coalescing
