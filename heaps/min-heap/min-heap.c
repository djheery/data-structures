#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_HEAP_CAPACITY 20 
#define QUEUE_CAPACITY 50

#define LENGTH(arr, dt) (sizeof(arr) / sizeof(dt))
#define DEBUG true

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

//  NOTE: There could be more in the Node struct 
//  NOTE: This is just here to treat each item in a heap as a Node rather than just having an array of integers 

typedef struct {
  uint16_t data; 
} Node;

typedef struct {
  uint16_t size; 
  uint16_t capacity; 
  Node** heap; 
} MinHeap; 

typedef struct {
  int* queue;
  uint16_t front;
  int16_t rear; 
  uint16_t size; 
  uint16_t capacity;
} Queue;

// Setup/ Teardown Methods 

MinHeap initialize_heap();
Node* initialize_node(uint16_t node_data); 

// Heap Operations 

MinHeap build_heap(Node** arr);
void min_heapify(MinHeap* heap, uint16_t idx);
void insert(MinHeap* heap, uint16_t node_data); 
void delete(MinHeap* heap, uint16_t node_data);
int16_t right_child_idx(MinHeap* heap, uint16_t idx); 
int16_t left_child_idx(MinHeap* heap, uint16_t idx); 
int16_t parent_idx(uint16_t idx); 
void swap(Node** heap, uint16_t i, uint16_t j); 
Node* peek(MinHeap* heap);
void print_heap(MinHeap* heap); 

// Queue Utility
Queue initialize_queue(); 
void free_queue(Queue* q);
void enqueue(Queue* q, int x); 
int dequeue(Queue* q);

MinHeap initialize_heap() {
  MinHeap h;  
  Node** heap = (Node**) malloc(sizeof(Node*) * INITIAL_HEAP_CAPACITY);

  if (heap == NULL) {
    DEBUG_PRINT("Error allocating memory for the heap\n", NULL);
    exit(EXIT_FAILURE);
  }

  h.heap = heap; 
  h.size = 0; 
  h.capacity = INITIAL_HEAP_CAPACITY; 

  return h;
}

Node* initialize_node(uint16_t node_data) {
  Node* n = (Node*) malloc(sizeof(Node));  

  if (n == NULL) {
    DEBUG_PRINT("Error allocating memory for Node: %d", node_data);
    exit(EXIT_FAILURE);
  }

  n->data = node_data;
  return n; 
}

void free_heap(MinHeap* heap) {

  if (heap == NULL || heap->size == 0) {
    DEBUG_PRINT("Trying to free NULL or EMPTY heap\n", NULL);
    return;
  }

  for (int i = 0; i < heap->size; i++) {
    DEBUG_PRINT("Freeing Node: %d\n", heap->heap[i]->data); 
    free(heap->heap[i]);
  }

  DEBUG_PRINT("All Nodes found have been freed\n\n", NULL);

  free(heap->heap);
  heap->heap = NULL; 
  heap = NULL; 

}

void swap(Node** heap, uint16_t i, uint16_t j) {
  Node* temp = heap[i]; 
  heap[i] = heap[j];
  heap[j] = temp;
}

int16_t left_child_idx(MinHeap* heap, uint16_t idx) {
  uint16_t l_idx = (idx * 2) + 1;  

  if (l_idx >= heap->size) return -1; 

  return l_idx; 
}

int16_t right_child_idx(MinHeap* heap, uint16_t idx) {
  uint16_t r_idx = (idx * 2) + 2;  

  if (r_idx >= heap->size) return -1; 

  return r_idx; 
}

int16_t parent_idx(uint16_t idx) {
  uint16_t p_idx = (idx / 2); 

  if (p_idx < 0) return -1;

  return p_idx; 
}

void min_heapify(MinHeap* heap, uint16_t idx) {

  if (heap == NULL) return; 
  if (idx >= heap->size || idx < 0) return;

  int16_t l_idx = left_child_idx(heap, idx);
  int16_t r_idx = right_child_idx(heap, idx); 
  uint16_t min_idx = idx; 

  Node* right = r_idx == -1 ? NULL : heap->heap[r_idx];
  Node* left = l_idx == -1 ? NULL : heap->heap[l_idx];
  Node* min = heap->heap[min_idx];

  if (left != NULL && left->data < min->data) {
    min_idx = l_idx;  
    min = heap->heap[min_idx];
  }

  if (right != NULL && right->data < min->data) {
    min_idx = r_idx;  
    min = heap->heap[min_idx];
  }

  if (min_idx != idx) {
    swap(heap->heap, idx, min_idx); 
    min_heapify(heap, min_idx);
  }
  
}

void insert(MinHeap* heap, uint16_t node_data) {

  if (heap == NULL) return;  
  if (heap->size == heap->capacity) return; 

  Node* new_node = initialize_node(node_data);
  heap->heap[heap->size] = new_node; 

  int16_t p_idx = parent_idx(heap->size);
  uint16_t c_idx = heap->size; 

  if (p_idx == -1) {
    heap->size += 1; 
    return;
  }

  Node* parent = heap->heap[p_idx];
  Node* current = heap->heap[c_idx];

  while (parent->data > current->data) {
    swap(heap->heap, c_idx, p_idx); 

    c_idx = p_idx; 
    p_idx = parent_idx(p_idx);

    if (p_idx == -1) break;

    current = heap->heap[c_idx];
    parent = heap->heap[p_idx];

  }

  heap->size += 1; 

}

//

int16_t extract_min(MinHeap* heap) {

  if (heap == NULL || heap->size == 0) return -1;

  Node* min = heap->heap[0];
  int16_t node_data = min->data;
  swap(heap->heap, 0, heap->size - 1);

  free(heap->heap[heap->size -1]);
  heap->heap[heap->size - 1] = NULL;

  heap->size -= 1;

  min_heapify(heap, 0);
 
  return node_data;

}

Node* peek(MinHeap* heap) {
  if (heap->size == 0) return NULL; 

  return heap->heap[0];
}

void print_heap(MinHeap* heap) {

  if (heap == NULL || heap->size == 0) {
    printf("No heap to print\n");
    return;
  }

  printf("[");

  for (int i = 0; i < heap->size; i++) {
    printf("%u, ", heap->heap[i]->data); 
  }

  printf("]\n");
}

/**
 * ===========
 * || Tests ||
 * ===========
 */

void test_insertion(MinHeap* heap) {
  printf("==================\n");
  printf("|| Insertion    ||\n"); 
  printf("==================\n\n");

  int nums[] = { 38, 384, 27, 46, 463, 47, 200, 40, 64 };
  
  for (int i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
    printf("Adding node: %d\n", nums[i]); 
    insert(heap, nums[i]); 
    print_heap(heap); 
  }

  print_heap(heap); 
  printf("\n");
}



void test_extract_max(MinHeap* heap) {
  printf("==================\n");
  printf("|| Extract Min  ||\n"); 
  printf("==================\n\n");

  for (int i = 0; i < 2; i++) {
    printf("Before: "); 
    print_heap(heap);
    int16_t data = extract_min(heap); 
    printf("Extracted: %d", data); 
    printf("\nAfter: ");
    print_heap(heap);
    printf("\n");
  }

  printf("\n");
}

void test_peek(MinHeap* heap) {
  printf("==================\n");
  printf("|| Peek         ||\n"); 
  printf("==================\n\n");

  Node* node = peek(heap);  

  if (node != NULL) {
    printf("Min: %d\n\n", node->data);
    return;
  }
}

void test_build_heap() {
  
}

void run_tests() {
  MinHeap heap = initialize_heap();

  test_insertion(&heap);

  test_extract_max(&heap);

  test_peek(&heap);

  free_heap(&heap);

}

int main() {
  run_tests();
  return 0;
}
