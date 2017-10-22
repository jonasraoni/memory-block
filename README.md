# Memory Block

A set of simple functions to manage the memory of a dynamic array with fixed size items and contiguous memory.

The MemoryBlock structure contains 4 elements:  
data: pointer to the real data  
capacity: storage capacity  
size: data size of each item

The block grows according to the current capacity, when capacity is:  
&gt; 64: allocate extra space for "capacity / 4" items  
&gt; 8: allocate extra space for 16 items  
&lt; 9: allocate extra space for 4 items

Being a dynamic block of memory, do not hold pointers to its internal data for too long as it may be reallocated to another address whenever there's not enough contiguous memory to grow.

## How to use

The header [memory-block.h](memory-block.h) contains the documentation.

Also check the file [test.c](test.c), it contains some examples and expectations. To compile the test:  
- gcc: <code>gcc -lm memory-block.c test.c -o test</code>  
- g++: <code>g++ memory-block.c test.c -o test</code>
