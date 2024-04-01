#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RESIZE_LOADFACTOR .7
#define INITIAL_CAPACITY 10

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

typedef struct {
  char* key; 
  char* value; 
  void* next;
} BucketNode;

typedef struct {
  BucketNode* head; 
  BucketNode* tail;
  int16_t size;
} Bucket;

typedef struct {
  Bucket** table; 
  int16_t size; 
  int16_t capacity; 
  int16_t loadfactor; 
} HashTable;

Bucket* initialize_bucket() {
  Bucket* b = (Bucket*) malloc(sizeof(Bucket)); 

  b->head = NULL;
  b->tail = NULL;
  b->size = 0;

  return b; 
}

BucketNode* initialize_bucket_node(char key[], char value[]) {
  BucketNode* bn = (BucketNode*) malloc(sizeof(BucketNode)); 

  if (bn == NULL) {
    printf("Error: Something went wrong allocating memory for new Bucket Node\n\n");
    exit(1);
  }

  bn->key = key; 
  bn->value = value; 
  bn->next = NULL;

  return bn;
}

HashTable initialize_hash_table() {
  HashTable ht; 
  Bucket** table = (Bucket**) malloc(sizeof(Bucket) * INITIAL_CAPACITY);

  if (table == NULL) {
    printf("Error: Something went wrong initializing Buckets for the hash table\n\n");
    exit(1);
  }

  ht.table = table; 
  ht.loadfactor = 0; 
  ht.size = 0; 
  ht.capacity = INITIAL_CAPACITY; 

  return ht;
}

char* hash_func() {
  return "";
}

void free_table(HashTable* table) {
  
}

void resize(HashTable* table) {
  if (table->loadfactor < RESIZE_LOADFACTOR) return;

}

BucketNode* get(HashTable* table, char key[]) {
  int k = 0;

  if (table->table[k] == NULL) {
    return NULL;
  }

  return NULL;
}

BucketNode* search(HashTable* table, char key[]) {
  int k = 0; 

  if (k > table->capacity || k < 0) {
    printf("Error: Key has been calculated as out of bounds. Check Hash Function\n\n");
    exit(1);
  }

  Bucket* bn = table->table[k];

  if (bn == NULL) return NULL;

  BucketNode* current = bn->head;

  while (current != NULL && strcmp(current->key, key) != 0) {
    current = current->next;  
  }

  if (current == NULL) return NULL;

  // So that we do not return a node that is not the node we are looking for 
  if (strcmp(current->key, key) != 0) return NULL;

  return current; 
}

void bucket_insert(Bucket* b, char key[], char value[]) {
  BucketNode* current = b->head;  

  while(current->next != NULL) {
    current = current->next;  
  }

  current->next = initialize_bucket_node(key, value); 
  b->size += 1; 
  b->tail = current->next;
}

/**
 * Standard put method for a chained hash table
 *
 * @param: table -> The wrapper hash table struct
 * @param: { key, value } -> The key and value to be inserted
 */

void put(HashTable* table, char key[], char value[]) {
  // hash the key
  int k = 0;  
  // put in the hashtable vector
  if (table->table[k] != NULL) {
    bucket_insert(table->table[k], key, value);     
  } else {
    Bucket* b = initialize_bucket();
    b->head = initialize_bucket_node(key, value);
    b->size += 1;
  }
 
}

void test_get(HashTable* t) {
  char** keys = (char**) malloc((sizeof(char) * 20) * 5); 

  keys[0] = "Hello";
  keys[1] = "World"; 
  keys[2] = "Yes layd";
  keys[3] = "Heritical";
  keys[4] = "Space Marine";

  for (int i = 0; i < 3; i++) {
    BucketNode* v = get(t, keys[i]); 

    if (v == NULL) {
      DEBUG_PRINT("The key %s is NULL thus not found\n", keys[i]);
      continue;
    }

    DEBUG_PRINT("Key found: %s || Value: %s\n", keys[i], v->value); 
  }

}

int main() {
  return 0; 
}
