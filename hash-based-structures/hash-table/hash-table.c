#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RESIZE_LOADFACTOR .7
#define CHAINED 0
#define OPEN_ADDRESS 1
#define SHA256 "SHA256"


typedef struct {
  char* key; 
  char* value; 
  char* hash; 
  void* next;
} BucketNode;

typedef struct {
  BucketNode* head; 
  BucketNode* tail;
  int16_t size;
  int16_t capacity;
} Bucket;

typedef struct {
  void* table; 
  int16_t size; 
  int16_t capacity; 
  int16_t loadfactor; 
  int16_t addressing_pattern;
} HashTable;

char* hash_func() {
  return "";
}

void free_chained_hashtable(HashTable* table) {
  
}

void resize(HashTable* table) {
  if (table->loadfactor < RESIZE_LOADFACTOR) return;
}

BucketNode* get(HashTable* table, char val[]) {
  if (table->addressing_pattern == CHAINED) {
    return NULL;  
  }

  if (table->addressing_pattern == OPEN_ADDRESS) {
    return NULL;   
  }

  return NULL;
}

void put(HashTable* table, char key[], char value[]) {
  
}

int main() {
  return 0; 
}
