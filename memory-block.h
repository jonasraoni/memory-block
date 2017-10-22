/*
 * Memory Block: Functions to manage a dynamic array with fixed size items and contiguous memory
 * Jonas Raoni Soares da Silva <http://raoni.org>
 * https://github.com/jonasraoni/memory-block
 */

#ifndef __MEMORY_BLOCK_H__
#define __MEMORY_BLOCK_H__

#include <stdlib.h>

/*
 * An structure containing basic information to manage the slice of memory
 */
typedef struct __MemoryBlock {
	void *data; //data pointer
	size_t
		capacity, //current capacity
		size; //size of each item
}* MemoryBlock;


/*
 * Creates a new memory block
 * size: the size of each data item
 * capacity: initial capacity
 * returns a MemoryBlock, null on error
 */
MemoryBlock MemoryBlockCreate(const size_t size, const size_t capacity);

/*
 * Frees up the memory block altogether with its data
 * mb: the memory block
 * returns void
 */
void MemoryBlockFree(const MemoryBlock mb);

/*
 * Frees up only the memory block
 * mb: the memory block
 * returns void
 */
void MemoryBlockFreeEx(const MemoryBlock mb);

/*
 * Resizes the memory block to accommodate the "capacity" amount of items
 * mb: the memory block
 * capacity: new capacity
 * returns the new capacity, 0 on fail
 */
int MemoryBlockResize(const MemoryBlock mb, const size_t capacity);

/**
 * Grows the memory block's capacity dinamically at least by the specified amount
 * mb: the memory block
 * capacity: the required minimum capacity
 * returns the new capacity, 0 on fail
 */
int MemoryBlockGrowTo(const MemoryBlock mb, const size_t capacity);

/*
 * Grows the memory block's capacity dinamically according to its current capacity
 * mb: the memory block
 * returns the new capacity, 0 on fail
 */
int MemoryBlockGrow(const MemoryBlock mb);

/**
 * Retrieves a pointer to the memory block item at the specified position, null if non-existent
 * mb: the memory block
 * position: the item position to be retrieved
 * returns a pointer to the item, null if non-existent
 */
void *MemoryBlockItem(const MemoryBlock mb, const size_t position);

/**
 * Retrieves a pointer to the memory block item at the specified position, if non-existent, auto-grows the memory block
 * mb: the memory block
 * position: the item position to be retrieved
 * returns a pointer to the item, null on error
 */
void *MemoryBlockGetItem(const MemoryBlock mb, const size_t position);

#endif
