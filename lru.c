#include <stdlib.h>

#define INITIAL_SIZE 10

/*
* The API should only have put and get
* I want it to store keys that are strings and values that are JSON blobs								
* 
* 
*
*/

struct Node {
	int key;
	int value;
	struct Node* next;
	struct Node* prev;
	struct Node* ht_next;
};

struct LRUCache {
	int capacity;
	int size;
	struct Node** hash_table;
	struct Node* head;
	struct Node* tail;
};

// hash helper, put, get, remove

int hash(int key, int buckets) {
	return key % buckets;
}

int put(struct LRUCache* lru_cache, int key, int value) {

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


//Node initializer helper
struct Node* initialize_node(int key, int value) {
	struct Node* node = malloc(sizeof(struct Node));
	node->key = key;
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	node->ht_next = NULL;
	return node;
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

// Create node, create cache functions

struct Node* create_node(int key, int value) {
	struct Node* node = malloc(sizeof(struct Node));
	node->key = key;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	node->ht_next = NULL;
	return node;
}

struct LRUCache* create_cache(int capacity) {
	struct LRUCache* cache = malloc(sizeof(struct LRUCache));


	return cache;
}