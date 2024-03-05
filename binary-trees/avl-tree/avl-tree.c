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

/**
 * Initialize the queue 
 *
 * @returns: A new CircularQueue
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

/**
 * Free the queue and set the struct to NULL 
 *
 * @param: circ_queue -> The queue to set to NULL which contains the queue to free 
 */

void free_queue(CircularQueue* circ_queue) {
  
  if (circ_queue == NULL) {
    printf("Queeu should not be NULL when calling free queue\n\n"); 
    exit(EXIT_FAILURE); 
  }

  free(circ_queue->queue); 
  circ_queue = NULL; 

}

/** 
 * Enqueue a new node in the queue 
 *
 * @param: circ_queue -> The queue struct to enqueue within 
 * @param: node -> The node to enqueue
 */

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

/**
 * Standard dequeue method for a circular queue
 *
 * @param: circ_queue -> The queue struct to dequeue from 
 * @returns: The element at the front of the queue (Can return NULL if the queue is empty) 
 */

Node* dequeue(CircularQueue* circ_queue) {

  if (circ_queue == NULL) {
    printf("Queue should not be NULL when calling dequeue\n"); 
    exit(EXIT_FAILURE); 
  }

  if (circ_queue->length == 0 || circ_queue->queue[circ_queue->front] == NULL) {
    printf("There is nothing to dequeue\n"); 
    return NULL; 
  }

  Node* dequeued_node = circ_queue->queue[circ_queue->front]; 
  circ_queue->front -= 1; 
  circ_queue->length -= 1; 

  return dequeued_node; 

}


