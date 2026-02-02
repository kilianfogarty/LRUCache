# define HASH_SIZE 1024

struct Node {
	int key;
	int value;
	struct Node *previous;
	struct Node *next;
};

struct {};

struct LRUCache {
	int capacity;
	int size;
	Node* head;
	Node* tail;

};

// Hash function using djb2
unsigned long hash(const char* str) {
	unsigned long hash = 5381;
	int c;

	while ((c = *str++)) {
		// hash << 5 is an arithemtic left shift of 2^5
		// hash = hash * 33 + c
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}


// How does a hashtable work?
// Either an array of linked lists or an array with probing
// put, get, delete
// put: hash value, mod, access that location

// Need a hashtable that holds a pointer to a Node
// DLL of nodes
// 

int get(int key) {
	// Look up in hashtable
	// if not there return -1
	// Else remove node from current position and move to head
	// return node value
}

void put(int key) {
	// If key exists:
	// look up the node in the hashtable
	// Update value
	// Move to head
	// If it doesn't exist:
	// If full:
	// Remove tail node, remove from hashtable, free memory
	// create new new, insert at head, add to hashtable

}

int main(void) {
	return 0;
}