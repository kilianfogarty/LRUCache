#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	STRING,
	LIST,
	SET,
	DICT
} ValueType;

typedef struct Value {
	ValueType type;
	void* data;
} Value;

typedef struct Node {
	char* key;
	Value value;
	Node* next;
	Node* prev;
	Node* ht_next;
} Node;

typedef struct {
	int capacity;
	int size;
	int buckets;

	Node** hash_table;
	Node* head;
	Node* tail;
} LRUCache;

// hash helper, put, get, remove

unsigned long hash(const char* str, int buckets) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	return hash % buckets;
}

Node* create_node(char* key, Value value) {
	Node* node = malloc(sizeof(struct Node));

	if (!node) {
		return NULL;
	}

	node->key = strdup(key);
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	node->ht_next = NULL;

	return node;
}

LRUCache* create_cache(int capacity) {
	LRUCache* cache = malloc(sizeof(LRUCache));
	if (!cache) {
		return NULL;
	}

	cache->capacity = capacity;
	cache->size = 0;
	cache->buckets = capacity * 2; // 0.5 load allegedly?
	cache->hash_table = calloc(cache->buckets, sizeof(Node*));
	if (!cache->hash_table) {
		free(cache);
		return NULL;
	}

	cache->head = malloc(sizeof(Node));
	cache->tail = malloc(sizeof(Node));

	if (!cache->head || !cache->tail) {
		free(cache->hash_table);
		free(cache->head);
		free(cache->tail);
		free(cache);
		return NULL;
	}

	cache->head->prev = NULL;
	cache->head->next = cache->tail;

	cache->tail->prev = cache->head;
	cache->tail->next = NULL;


	return cache;
}


int put(struct LRUCache* lru_cache, char* key, struct Value value) {

	// Check to see if any parameters that are passed in are null

	int hashed_key = hash(key, lru_cache->size);
	struct Node* curr = lru_cache->hash_table[hashed_key];
	while (curr != NULL) {
		if (curr->key = key) {
			curr->value = value;
			return 1;
		}

		curr = curr->next;
	}
	// init a new node
	struct Node* new_node = initialize_node(key, value);
	new_node->ht_next = curr;
	lru_cache->hash_table[hashed_key] = new_node;
	

	// if DNE, malloc a new node with key and value at the front of the DLL and the front of the bucket


	return 0;
}



// remove_node helper, add to head helper

int get(struct LRUCache* lru_cache, int key) {

	/*
	Hash key
	go to hashed index
	while the pointer points to a real node, check the key
		if key is correct, return value
	if it doesn't exist return DNE

	change the previous and next node to point to each other
	put the node with key behind the sentinel head node
	
	*/
	return 0;
}

int remove(struct LRUCache* lru_cache, int key) {
	return 0;
}