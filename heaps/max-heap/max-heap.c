#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define QUEUE_CAPACITY 50

#define DEBUG true

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

typedef struct Node Node; 

typedef struct Node {
  Node* left; 
  Node* right; 
  int32_t data; 
} Node;

typedef struct {
  Node* root;
  uint16_t size; 
  uint16_t height; 
} MaxHeap; 

typedef struct {
  Node** queue;
  uint16_t front;
  int16_t rear; 
  uint16_t size; 
  uint16_t capacity;
} Queue;

void max_heapify(MaxHeap* heap);
void insert(MaxHeap* heap, int32_t node_data); 
void delete(MaxHeap* heap, int32_t node_data);
Node* search(MaxHeap* heap, int32_t node_data); 
bool node_exists(MaxHeap* heap, int32_t node_data);

// Queue Utility
Queue initialize_queue(); 
void free_queue(Queue* q);
void enqueue(Queue* q, Node* x); 
Node* dequeue(Queue* q);

/**
 * ===================
 * || Queue Methods ||
 * ===================
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

void free_queue(Queue* q) {
  if (q == NULL) {
    DEBUG_PRINT("Attempt to free a NULL queue\n\n", NULL);
    return; 
  } 

  free(q->queue); 
  q = NULL;
}

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
