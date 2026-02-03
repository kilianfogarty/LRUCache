#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 16
#define LOAD_FACTOR 0.75

struct Node {
	char *key;
	void *value;
	struct Node* next;
};

struct HashMap {
	struct Node **buckets;
	int size; // number of buckets
	int count; // numner of elements
	void (*free_value)(void*); // What does this do?
};

// keep it simple with djb2 hashing
unsigned int hash(const char* key) {
	unsigned long hash = 5381;
	int c;
	while ((c = *key++))
		hash = ((hash << 5) + hash) + c;
	return hash;
}

struct HashMap *create_hashmap(void (*free_value)(void*)) {
	struct HashMap *map = malloc(sizeof(struct HashMap));
	map->size = INITIAL_SIZE;
	map->count = 0;
	map->free_value = free_value;
	map->buckets = calloc(map->size, sizeof(struct Node*));
	return map;
}

