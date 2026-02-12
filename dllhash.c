#include <string>
#include <cstdint>
#include <stdlib.h>

#define TABLE_SIZE 10

struct Node {
	int key;
	int value;
	struct Node* prev;
	struct Node* next;
	struct Node* h_next;
} Node;

// Should have sentinel head and tail
struct DoublyLinkedList {
	int size;
	struct Node* head;
	struct Node* tail;
};

struct HashTable {
	struct Node* buckets[TABLE_SIZE];
	double load_factor;
};

int hash(int key) {
	return key % TABLE_SIZE;
}


int ht_get(struct HashTable* ht, int key) {
	int hashed_key = hash(key);
	struct Node* curr = ht->buckets[hashed_key];
	// While current is not null
	while (curr != null) {
		if (curr->key == key) {
			return curr->value;

			// Move to top of dll too
		}
		curr = curr->next;
	}

	// return -1 for value if it is not found?
	return -1;
}

// ht_put

// ht_remove

// ht_get

// Put, get, remove, resize, clear entire table, hash, containskey, isempty