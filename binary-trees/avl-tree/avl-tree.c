#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#define QUEUE_CAPACITY 50
#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

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

// Setup / Teardown methods 

AVLTree initialize_tree(); 
Node* initialize_node(int32_t node_data); 
void free_tree(AVLTree* tree); 

// General Tree Methods 

bool node_exists(Node* root); 
Node* search_and_get(Node* root); 

void insert(AVLTree* tree, int32_t node_data); 
Node* insert_helper(AVLTree* tree, Node* root, int32_t node_data); 

void delete(AVLTree* tree, int32_t node_data); 
Node* delete_helper(AVLTree* tree, Node* root, int32_t node_data); 

void rotate_left(AVLTree* tree, Node* x); 
void rotate_right(AVLTree* tree, Node* x); 

int get_tree_balance(Node* root); 

int get_tree_height(Node* root);
int get_max(uint a, uint b); 

// Queue methods 

CircularQueue initialize_queue();
Node* dequeue(CircularQueue* circ_queue); 
void enqueue(CircularQueue* circ_queue, Node* node); 
void free_queue(CircularQueue* circ_queue); 

int main() {
  return 0; 
}

/**
 * =====================
 * || Program Methods || 
 * =====================
 */

AVLTree initialize_tree() {
  AVLTree tree; 
  tree.root = NULL; 
  tree.size = 0;

  return tree; 
}

Node* initialize_node(int32_t node_data) {
  Node* node = (Node*) malloc(sizeof(Node)); 

  if (node == NULL) {
    DEBUG_PRINT("Error  allocating memory for node with data: %d\n", node_data); 
    exit(EXIT_FAILURE); 
  }

  node->data = node_data; 
  node->left = NULL;
  node->right = NULL; 

  return node; 
}

void free_tree(AVLTree* tree) {
  
  if (tree->root == NULL) {
    printf("There are no nodes in the tree that can be reached\n\n");  
    return; 
  }

  if (tree->size == 0) {
    DEBUG_PRINT("The tree size is 0 but there are nodes in the tree - something is wrong\n\n", NULL);
    return; 
  }

  CircularQueue circ_queue = initialize_queue(); 
  enqueue(&circ_queue, tree->root); 

  while (circ_queue.length > 0) {
    Node* current = dequeue(&circ_queue);

    if (current->left != NULL) enqueue(&circ_queue, current->left); 
    if (current->right != NULL) enqueue(&circ_queue, current->right); 

    DEBUG_PRINT("Freeing node with data: %d\n", current->data); 
    free(current); 
  }

  DEBUG_PRINT("\nAll nodes found have been freed\n\n", NULL); 

  free_queue(&circ_queue); 

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


