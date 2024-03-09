#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define RESIZE_LOAD_FACTOR .7 
#define INITIAL_HEAP_CAPACITY 20 
#define QUEUE_CAPACITY 50

#define DEBUG true

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

typedef struct {
  int32_t data; 
  uint16_t idx; 
} Node;

typedef struct {
  uint16_t size; 
  Node* first; 
  Node* last; 
  Node** heap; 
} MaxHeap; 

typedef struct {
  Node** queue;
  uint16_t front;
  int16_t rear; 
  uint16_t size; 
  uint16_t capacity;
} Queue;

// Setup/ Teardown Methods 

MaxHeap initialize_heap();
Node* initialize_node(int32_t node_data); 

// Heap Operations 

void max_heapify(MaxHeap* heap, uint16_t idx);
void insert(MaxHeap* heap, int32_t node_data); 
void delete(MaxHeap* heap, int32_t node_data);
Node* right_child(MaxHeap* heap, uint16_t idx); 
Node* left_child(MaxHeap* heap, uint16_t idx); 

// Queue Utility
Queue initialize_queue(); 
void free_queue(Queue* q);
void enqueue(Queue* q, Node* x); 
Node* dequeue(Queue* q);

/**
 * =====================
 * || Program methods ||
 * =====================
 */

/**
 * Initialize a heap heap and return it 
 *
 * @returns: A new heap struct 
 */

MaxHeap initialize_heap() {
  MaxHeap heap; 
  heap.heap = (Node**) malloc(sizeof(Node) * INITIAL_HEAP_CAPACITY);

  if (heap.heap == NULL) {
    DEBUG_PRINT("Error Allocating memory for the heap\n\n", NULL); 
    exit(EXIT_FAILURE);
  }

  heap.first = NULL; 
  heap.last = NULL; 
  heap.size = 0;

  return heap;
}

/**
 * Free all nodes in the heap and the heap itself 
 * This will set the heap struct to NULL after destroying the heap and it's nodes 
 *
 * @param: heap -> The heap to free 
 */

void free_heap(MaxHeap* heap) {
  uint32_t heap_length = sizeof(heap->heap) / sizeof(Node);  
  Node** h = heap->heap;

  for (int i = 0; i < heap_length; i++) {
    DEBUG_PRINT("Freeing node -> %d\n", h[i]->data); 
    free(h[i]);
  }

  DEBUG_PRINT("All heap nodes found have been freed\n\n", NULL);

  free(heap->heap);
  heap = NULL; 
}

void swap(Node** arr, uint16_t i, uint16_t j) {
  Node* temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp; 
  
}

/** 
 * Max Heapify the heap given an idx 
 *
 * @param: heap -> The heap struct to heapify (The acctual heap is contained in heap->heap) 
 * @param: idx -> The idx to start the heapify method at
 */

void max_heapify(MaxHeap* heap, uint16_t idx) {
  Node* l = left_child(heap, idx);  
  Node* r = right_child(heap, idx);
  Node* i = heap->heap[idx];
  Node* largest = i; 

  if (l != NULL && l->data > largest->data) {
    largest = l; 
  }

  if (r != NULL && r->data > largest->data) {
    largest = r; 
  }

  if (largest != i) {
    swap(heap->heap, i->idx, largest->idx); 
    max_heapify(heap, largest->idx);
  }
    
}

/**
 * Get the right child of a given node 
 */

Node* right_child(MaxHeap* heap, uint16_t idx) {
  uint16_t r_idx = (idx * 2) + 2; 

  if (r_idx > heap->size) return NULL;

  return heap->heap[r_idx];
}

/**
 * Get the left child of a given node
 */

Node* left_child(MaxHeap* heap, uint16_t idx) {
  uint16_t l_idx = (idx * 2) + 1;

  if (l_idx > heap->size) return NULL; 

  return heap->heap[l_idx];
}

/**
 * Get the parent of a given node 
 */

Node* parent(MaxHeap* heap, uint16_t idx) {
  uint16_t p_idx = (uint16_t) (idx / 2) + 1;  

  return heap->heap[p_idx];
}

/**
 * Insert into the heap 
 */

void insert(MaxHeap* heap, int32_t idx) {
  Node* last = heap->heap[heap->size - 1]; 

   
}



/**
 * ===================
 * || Queue Methods ||
 * ===================
 */

/**
 * Initialize the queue (This is a circular queue) 
 *
 * @returns: A new Circular Queue
 */

Queue initialize_queue() {
  Queue q; 
  Node** queue = (Node**) malloc(sizeof(Node) * QUEUE_CAPACITY); 
  
  if (queue == NULL) {
    DEBUG_PRINT("Error Allocating Memory for the queue data structure\n", NULL);    
    exit(EXIT_FAILURE);
  }

  q.queue = queue; 
  q.size = 0; 
  q.front = 0;
  q.rear = -1;
  q.capacity = QUEUE_CAPACITY;

  return q; 
}

/**
 * Free the queue
 *
 * @param: The queue to free 
 */

void free_queue(Queue* q) {
  if (q == NULL) {
    DEBUG_PRINT("Attempt to free a NULL queue\n\n", NULL);
    return; 
  } 

  free(q->queue); 
  q = NULL;
}

/**
 * Enqueue a node in the queue 
 *
 * @param: q -> The queue to enqueue within 
 * @param: x -> The node to enqueue 
 */

void enqueue(Queue* q, Node* x) {

  if (q == NULL) {
    DEBUG_PRINT("Error: Attempting to enqueue into a NULL queue\n", NULL); 
    return;
  }

  if (x == NULL) {
    DEBUG_PRINT("Error: Attempting to enqueue a NULL node\n", NULL); 
    return;
  }

  if (q->size == q->capacity) {
    DEBUG_PRINT("Error: Attempting to enqueue when the queue is at capacity. Please dequeue some nodes\n", NULL); 
    return;
  }

  q->rear = ((q->rear + 1) % q->capacity); 
  q->queue[q->rear] = x; 
  q->size += 1; 
  
}

/**
 * Dequeue a node from the queue 
 *
 * @param: q -> The queue to dequeue from 
 * @returns: A node from the front of the queue (if it exists) or NULL if there are no Nodes in the queue  
 */

Node* dequeue(Queue* q) {

  if (q == NULL) {
    DEBUG_PRINT("Error: Attempting to dequeue from a NULL queue\n", NULL); 
    return NULL;
  }

  if (q->size == 0 || q->rear == -1) {
    DEBUG_PRINT("Error: The queue is empty so cannot dequeue a node\n", NULL);
    return NULL;
  }

  Node* x = q->queue[q->front];
  q->front = ((q->front + 1) % q->capacity);
  q->size -= 1; 

  if (q->size == 0) {
    q->front = 0;  
    q->rear = -1; 
  }
 
  return x;

}

/** 
 * =================
 * || Main Method ||
 * =================
 */

int main() {
  return 0;
}
