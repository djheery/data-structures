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

//  NOTE: There could be more in the Node struct 
//  NOTE: This is just here to treat each item in a heap as a Node rather than just having an array of integers 

typedef struct {
  int32_t data; 
} Node;

typedef struct {
  uint16_t size; 
  uint16_t capacity; 
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
void insert(MaxHeap* heap, uint32_t node_data); 
void delete(MaxHeap* heap, uint32_t node_data);
int16_t right_child_idx(MaxHeap* heap, uint16_t idx); 
int16_t left_child_idx(MaxHeap* heap, uint16_t idx); 
int16_t parent_idx(MaxHeap* heap, uint16_t idx); 
void swap(Node** heap, uint16_t i, uint16_t j); 


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

  heap.size = 0;
  heap.capacity = INITIAL_HEAP_CAPACITY; 

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

/** 
 * Standard swap util method to swap to indexes in an Array/Vector 
 *
 * @param: heap -> The heap to swap the indexes within 
 * @param: { i, j } -> Indexes in the array to swap
 */

void swap(Node** heap, uint16_t i, uint16_t j) {
  Node* temp = heap[i];
  heap[i] = heap[j];
  heap[j] = temp; 
}

/** 
 * Max Heapify the heap given an idx 
 *
 * @param: heap -> The heap struct to heapify (The acctual heap is contained in heap->heap) 
 * @param: idx -> The idx to start the heapify method at
 */

void max_heapify(MaxHeap* heap, uint16_t idx) {
  int16_t l_idx = left_child_idx(heap, idx);  
  int16_t r_idx = right_child_idx(heap, idx);
  uint16_t largest_idx = idx; 
  
  Node* largest = heap->heap[largest_idx];
  Node* right_child = r_idx == -1 ? NULL : heap->heap[r_idx];
  Node* left_child = l_idx == -1 ? NULL : heap->heap[l_idx];

  if (left_child != NULL && left_child->data > largest->data) {
    largest_idx = l_idx; 
  }

  if (right_child != NULL && right_child->data > largest->data) {
    largest_idx = r_idx; 
  }

  if (largest_idx != idx) {
    swap(heap->heap, idx, largest_idx); 
    max_heapify(heap, largest_idx);
  }
    
}

/**
 * Get the right child of a given node 
 */

int16_t right_child_idx(MaxHeap* heap, uint16_t idx) {
  uint16_t r_idx = (idx * 2) + 2; 

  if (r_idx > heap->size) return -1;

  return r_idx;
}

/**
 * Get the left child of a given node
 */

int16_t left_child_idx(MaxHeap* heap, uint16_t idx) {
  uint16_t l_idx = (idx * 2) + 1;

  if (l_idx > heap->size) return -1; 

  return l_idx;
}

/**
 * Get the parent of a given node 
 */

int16_t parent_idx(MaxHeap* heap, uint16_t idx) {
  
  int16_t p_idx = (idx) / 2;  

  if (p_idx < 0) return -1; 

  return p_idx;
}

/**
 * Insert into the heap 
 *
 * @param: heap -> The heap struct to insert into (The actual heap exits in heap->heap)
 * @param: node_data -> The ndoe data to insert 
 */

void insert(MaxHeap* heap, uint32_t node_data) {
  
  if (heap == NULL) {
    DEBUG_PRINT("Error - The heap is not provided or has not yet been instantiated\n\n", NULL);
    return; 
  }

  if (heap->size == heap->capacity) {
    DEBUG_PRINT("TODO - Add resize function\n", NULL); 
    DEBUG_PRINT("Error: Cannot add another element as the heap is full\n\n", NULL); 
    return;
  }

  Node** h = heap->heap; 

  h[heap->size] = initialize_node(node_data); 

  uint16_t c_idx = heap->size;
  int16_t p_idx = parent_idx(heap, c_idx);

  if (p_idx == -1) return; 

  Node* current = h[c_idx];
  Node* parent = h[p_idx]; 

  while(current->data > parent->data) {
    swap(h, c_idx, p_idx); 

    c_idx = p_idx; 
    p_idx = parent_idx(heap, p_idx);

    if (p_idx == -1) break;

    current = h[c_idx];
    parent = h[p_idx];
  }

  heap->size += 1; 

}

/** 
 * Extract the max element -> This is/ should be the root of the heap 
 *
 * @param: heap -> The heap to extract from
 * @returns: The max element (root of the heap) or NULL if the heap is empty 
 */

Node* extract_max(MaxHeap* heap) {
  
  if (heap->size <= 0) {
    DEBUG_PRINT("Trying to extract from the heap when there are no nodes\n", NULL);
    return NULL;
  }

  Node* max = heap->heap[0];
  heap->size -= 1; 
  heap->heap[0] = heap->heap[heap->size - 1];

  max_heapify(heap, 0);
  
  return max; 
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
