#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* 
* Data Structures
* 
*/

typedef struct Node {
	char* key;
	int value;
	Node* prev;
	Node* next;
	Node* h_next;	// Next node in the hashmap, not the DLL
} Node;

typedef struct LRUCache {
	unsigned int capacity;
	unsigned int num_of_items;
	unsigned int hashmap_size;
	Node* head;		// Sentinel Head
	Node* tail;		// Sentinel Tail
	Node** hashmap;
} LRUCache;

/*
* 
* Private Function Prototypes
* 
*/

static unsigned int hash(const char* key, unsigned int hashmap_size);
static Node* create_node(const char* key, int value);
static void add_to_front(LRUCache* cache, Node* node);
static void remove_node(Node* node);
static void remove_from_hashmap(LRUCache* cache, Node* node);

/*
* 
* Public API
* 
*/

LRUCache* create_LRUCache(unsigned int capacity) {
	if (capacity <= 0) {
		return NULL;
	}

	LRUCache* cache = malloc(sizeof(LRUCache));
	if (!cache) {
		return NULL;
	}

	cache->capacity = capacity;
	cache->num_of_items = 0;
	cache->hashmap_size = capacity * 2;

	cache->hashmap = calloc(cache->hashmap_size, sizeof(Node*));
	if (!cache->hashmap) {
		free(cache);
		return NULL;
	}

	cache->head = malloc(sizeof(Node));
	cache->tail = malloc(sizeof(Node));

	if (!cache->head || !cache->tail) {
		free(cache->hashmap);
		free(cache->head);
		free(cache->tail);
		free(cache);
		return NULL;
	}

	cache->head->key = NULL;
	cache->head->prev = NULL;
	cache->head->next = cache->tail;
	cache->head->h_next = NULL;

	cache->tail->key = NULL;
	cache->tail->prev = cache->head;
	cache->tail->next = NULL;
	cache->tail->h_next = NULL;

	return cache;
}

void free_LRUCache(LRUCache* cache) {
	if (!cache) {
		return;
	}

	Node* curr = cache->head->next;
	while (curr != cache->tail) {
		Node* next = curr->next;
		free(curr->key);
		free(curr);
		curr = next;
	}

	free(cache->head);
	free(cache->tail);
	free(cache->hashmap);
	free(cache);
}

// returns -1 if not found
int get(LRUCache* cache, const char* key) {
	if (!cache) {
		return -1;
	}
	unsigned int index = hash(key, cache->hashmap_size);
	Node* curr = cache->hashmap[index];
	while (curr) {
		if (strcmp(curr->key, key) == 0) {
			remove_node(curr);
			add_to_front(cache, curr);
			return curr->value;
		}
		curr = curr->h_next;
	}
	return -1;
}

/*
* -1 = failure
* 0 = updated
* 1 = inserted
*/

int put(LRUCache* cache, const char* key, int value) {
	if (!cache) {
		return -1;
	}
	unsigned int index = hash(key, cache->hashmap_size);
	Node* curr = cache->hashmap[index];
	while (curr) {
		if (strcmp(curr->key, key) == 0) {
			curr->value = value;
			remove_node(curr);
			add_to_front(cache, curr);
			return 0;
		}
		curr = curr->h_next;
	}

	if (cache->num_of_items >= cache->capacity) {
		Node* lru_node = cache->tail->prev;
		remove_node(lru_node);
		remove_from_hashmap(cache, lru_node);
		free(lru_node->key);
		free(lru_node);
		cache->num_of_items--;
	}

	Node* node = create_node(key, value);
	if (!node) {
		return -1;
	}
	add_to_front(cache, node);
	node->h_next = cache->hashmap[index];
	cache->hashmap[index] = node;
	cache->num_of_items++;
	return 1;
}

/* 
* 
* Private Helper Functions
* 
*/

static unsigned int hash(char* key, unsigned int hashmap_size) {
	unsigned long hash = 0;
	int c;

	while ((c = *key++)) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}
	return hash % hashmap_size;
}

static Node* create_node(const char* key, int value) {
	Node* node = malloc(sizeof(Node));
	if (!node) {
		return NULL;
	}

	node->key = strdup(key);
	if (!node->key) {
		free(node);
		return NULL;
	}

	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	node->h_next = NULL;

	return node;
}

static void add_to_front(LRUCache* cache, Node* node) {
	node->next = cache->head->next;
	node->prev = cache->head;

	cache->head->next->prev = node;
	cache->head->next = node;
}

static void remove_node(Node* node) {
	if (!node || !node->prev || !node->next) {
		return;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

static void remove_from_hashmap(LRUCache* cache, Node* node) {
	unsigned int index = hash(node->key, cache->hashmap_size);
	Node* curr = cache->hashmap[index];
	Node* prev = NULL;
	while (curr) {
		if (curr == node) {
			if (prev) {
				prev->h_next = curr->h_next;
			}
			else {
				cache->hashmap[index] = curr->h_next;
			}
			break;
		}
		prev = curr;
		curr = curr->h_next;
	}
}
