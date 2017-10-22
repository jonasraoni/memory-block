#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "memory-block.h"

//complete test
void completeTest(){
	//creates an empty block of integers
	MemoryBlock block = MemoryBlockCreate(sizeof(int), 0);
	//an empty block must have no data
	assert(block->data == NULL);
	if(block){
		for(int i = 10; i--;){
			//gets/allocates an item
			*((int *)MemoryBlockGetItem(block, i)) = i;
		}
		
		//tests
		//capacity should have grown bigger than 10 by this time
		assert(block->capacity >= 10);
		
		//checking the value through the data pointer
		int *p = (int *)block->data;
		assert(*p == 0);
		
		//checking if it's contiguous
		assert(*(p + 1) == 1);
		
		//through the API
		assert(*(int *)MemoryBlockItem(block, 2) == 2);
		
		//out of bounds access must return NULL
		assert(MemoryBlockItem(block, block->capacity) == NULL);

		//after growing the capacity must be bigger than before
		int oldCapacity = block->capacity;
		MemoryBlockGrow(block);
		assert(block->capacity > oldCapacity);

		//after growing to extra 20 items, the capacity should be bigger than n + 20
		oldCapacity = block->capacity;
		MemoryBlockGrowTo(block, block->capacity + 20);
		assert(block->capacity > oldCapacity + 20);

		//resizing to 0
		MemoryBlockResize(block, 0);
		assert(block->capacity == 0);

		//frees the memory
		MemoryBlockFree(block);	
	}
}

//test with basic type
void testWithBasicType(){
	MemoryBlock block;
	
	//creates an empty block
	assert(block = MemoryBlockCreate(sizeof(int), 0));
	for(int i = 1000; i--;){
		int *current;
		//gets the i-th item, growing the block if needed
		assert(current = (int *)MemoryBlockGetItem(block, i));
		*current = i;
	}
	
	//modifies item 1
	*(int *)MemoryBlockItem(block, 1) = 123;
	
	//tests
	assert(*(int *)MemoryBlockItem(block, 0) == 0);
	assert(*(int *)MemoryBlockItem(block, 1) == 123);
	assert(*(int *)MemoryBlockItem(block, 999) == 999);
	
	//frees the memory	
	MemoryBlockFree(block);
}

//test with struct
void testWithStruct(){
	typedef struct __TestStruct{
		int	number;
		char text[5];
	} __TestStruct, *TestStruct;
	
	MemoryBlock block;
	//creates a block with 10 items
	assert(block = MemoryBlockCreate(sizeof(__TestStruct), 10));
	
	for(int i = 1000; i--;){
		TestStruct current;
		//gets the i-th item, growing the block if needed
		assert(current = (TestStruct)MemoryBlockGetItem(block, i));
		current->number = i;
		sprintf(current->text, "%d", i);
	}

	//modifies the item 0
	*((TestStruct)MemoryBlockItem(block, 0)) = (__TestStruct){
		123,
		"test"
	};
	
	//tests
	assert(block->capacity >= 999);
	assert(((TestStruct)MemoryBlockItem(block, 0))->number == 123);
	assert(((TestStruct)MemoryBlockItem(block, 1))->number == 1);
	assert(((TestStruct)MemoryBlockItem(block, 999))->number == 999);

	//frees the memory
	MemoryBlockFree(block);	
}

//test with char pointer
void testWithCharPointer(){
	MemoryBlock block;
	
	//creates a block with 10 items
	assert(block = MemoryBlockCreate(sizeof(char *), 10));
	
	unsigned int dataLength = 0;
	for(int i = 10; i--;){
		int length = strlen("Line \n") + floor(log10(i ? i : 1)) + 1;
		MemoryBlockGrowTo(block, dataLength + length + 1);
		sprintf((char *)block->data + dataLength, "Line %d\n", i);
		dataLength += length;
	}
	//Modifies the first character to "F"
	*((char *)block->data) = 'F';
	
	//tests
	assert(block->capacity > dataLength);
	assert(strstr((char *)block->data, "Line 0"));
	assert(strstr((char *)block->data, "Fine 9"));

	//frees the memory
	MemoryBlockFree(block);	
}

int main(int argc, char *argv[]){
	completeTest();
	testWithBasicType();
	testWithStruct();
	testWithCharPointer();
	return 0;
}
