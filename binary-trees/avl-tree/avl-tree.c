#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_CAPACITY 50

typedef struct Node Node; 

typedef struct Node {
  int32_t data; 
  Node* left; 
  Node* right; 
} Node; 

typedef struct {
  Node* root; 
  uint16_t size; 
} AVLTree; 

typedef struct {
  Node** queue; 
  uint16_t front; 
  int16_t rear;
  uint16_t capacity; 
  uint16_t length; 
} CircularQueue; 

int main() {
  return 0; 
}

/**
 * ====================
 * || Circular Queue ||
 * ====================
 */

CircularQueue initialize_queue() {
  CircularQueue circ_queue; 

  Node** queue = (Node**) malloc(sizeof(Node) * QUEUE_CAPACITY); 

  if (queue == NULL) {
    printf("Something went wrong allocating the queue\n\n");
    exit(EXIT_FAILURE);
  }

  circ_queue.capacity = QUEUE_CAPACITY; 
  circ_queue.front = 0; 
  circ_queue.rear = -1; 
  circ_queue.length = 0; 

  return circ_queue; 
}

void free_queue(CircularQueue* circ_queue) {
  
  if (circ_queue == NULL) {
    printf("Queeu should not be NULL when calling free queue\n\n"); 
    exit(EXIT_FAILURE); 
  }

  free(circ_queue->queue); 
  circ_queue = NULL; 
}

void enqueue(CircularQueue* circ_queue, Node* node) {

  if (circ_queue == NULL) {
    printf("Queue should not be NULL when calling enqueue\n"); 
    exit(EXIT_FAILURE); 
  }

  if (node == NULL) {
    printf("Node* should not be NULL when calling enqueue\n"); 
    exit(EXIT_FAILURE); 
  }

  if (circ_queue->length == circ_queue->capacity) {
    printf("Cannot enqueue another item due to queue reaching capacity\n\n"); 
    exit(EXIT_FAILURE); 
  }

  circ_queue->rear += 1;
  circ_queue->queue[circ_queue->rear] = node; 
  circ_queue->length += 1;

}


