#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

/*
This is a very simple hashmap implementation for educational purposes only. It uses a simple hashing function to insert keys into
an open-addressing hash table that uses linear probing. It will have automatic resizing. It will allow for string keys and pointers to 
nodes in a doubly linked list to suit the overall purpose of building an LRU cache.
*/

struct hash_entry {
	int key;
	int value;
};

struct hash_entry* hash_map[SIZE];
struct hash_entry* tombstone;

