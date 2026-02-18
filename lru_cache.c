#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash(int key, int capacity);

typedef struct Node {
	int key;
	int value;
	Node* prev;
	Node* next;
	Node* h_next;
} Node;

typedef struct LRUCache {
	int capacity;
	int num_of_items;
	Node* head;
	Node* tail;
	Node** hashmap;
} LRUCache;

Node* create_node(int key, int value) {
	Node* node = malloc(sizeof(Node));
	if (!node) {
		return NULL;
	}

	node->key = key;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	node->h_next = NULL;

	return node;
}

LRUCache* create_LRUCache(int capacity) {
	if (capacity <= 0) {
		return NULL;
	}

	LRUCache* cache = malloc(sizeof(LRUCache));
	if (!cache) {
		return NULL;
	}

	cache->capacity = capacity;
	cache->num_of_items = 0;

	cache->hashmap = calloc(capacity, sizeof(Node*));
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

	cache->head->key = 0;
	cache->head->prev = NULL;
	cache->head->next = cache->tail;
	cache->head->h_next = NULL;

	cache->tail->key = 0;
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
		free(curr);
		curr = next;
	}

	free(cache->head);
	free(cache->tail);
	free(cache->hashmap);
	free(cache);
}

int get(LRUCache* cache, int key) {
	if (!cache) {
		return -1;
	}
	int index = hash(key, cache->capacity);
	Node* curr = cache->hashmap[index];
	while (curr) {
		if (curr->key == key) {
			remove_node(curr);
			add_to_front(cache, curr);
			return curr->value;
		}
		curr = curr->h_next;
	}
	return -1;
}

int put(LRUCache* cache, int key, int value) {
	if (!cache) {
		return -1;
	}
	int index = hash(key, cache->capacity);
	Node* curr = cache->hashmap[index];
	while (curr) {
		if (curr->key == key) {
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
		lru_node->prev = NULL;
		lru_node->next = NULL;
		lru_node->h_next = NULL;

		remove_from_hashmap(cache, lru_node);
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

void add_to_front(LRUCache* cache, Node* node) {
	node->next = cache->head->next;
	node->prev = cache->head;

	cache->head->next->prev = node;
	cache->head->next = node;
}

void remove_node(Node* node) {
	if (!node) {
		return;
	}
	node->prev->next = node->next;
	node->next->prev = node->prev;
}

void remove_from_hashmap(LRUCache* cache, Node* node) {
	int index = hash(node->key, cache->capacity);
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

unsigned int hash(int key, int capacity) {
	return (unsigned int)key % capacity;
}

