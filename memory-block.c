/*
 * Memory Block: A set of simple functions to manage the memory of a dynamic array with fixed size items and contiguous memory.
 * Jonas Raoni Soares da Silva <http://raoni.org>
 * https://github.com/jonasraoni/memory-block
 */

#ifndef __MEMORY_BLOCK__
#define __MEMORY_BLOCK__

#include <stdlib.h>
#include "memory-block.h"

MemoryBlock MemoryBlockCreate(const size_t size, const size_t capacity){
	MemoryBlock mb = (MemoryBlock)malloc(sizeof(struct __MemoryBlock));
	if(mb) {
		mb->data = NULL;
		mb->size = size;
		mb->capacity = capacity && (mb->data = (void *)malloc(capacity * size)) ? capacity : 0;
	}
	return mb;
}

void MemoryBlockFree(const MemoryBlock mb){
	free(mb->data);
	free(mb);
}

void MemoryBlockFreeEx(const MemoryBlock mb){
	free(mb);
}

int MemoryBlockResize(const MemoryBlock mb, const size_t capacity){
	void *data = (void *)realloc(mb->data, capacity * mb->size);
	if(data || !capacity){
		mb->data = data;
		return mb->capacity = capacity;
	}
	return 0;
}

int MemoryBlockGrowTo(const MemoryBlock mb, const size_t capacity){
	if(mb->capacity >= capacity)
		return mb->capacity;
	size_t newCapacity = capacity + (capacity > 64 ? capacity / 4 : capacity > 8 ? 16 : 4);
	return MemoryBlockResize(mb, newCapacity);
}

int MemoryBlockGrow(const MemoryBlock mb){
	return MemoryBlockGrowTo(mb, mb->capacity + 1);
}

void *MemoryBlockItem(const MemoryBlock mb, const size_t position){
	return position < mb->capacity ? (char *)mb->data + position * mb->size : NULL;
}

void *MemoryBlockGetItem(const MemoryBlock mb, const size_t position){
	return position >= mb->capacity && !MemoryBlockGrowTo(mb, position) ? NULL : MemoryBlockItem(mb, position);
}

#endif
