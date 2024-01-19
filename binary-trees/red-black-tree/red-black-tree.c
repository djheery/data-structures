#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

#define RED 1
#define BLACK 0
#define QUEUE_CAPACITY 30 

typedef struct {
  int data; 
  int color; 
  void* left; 
  void* right; 
  void* parent; 
} Node; 

typedef struct {
  Node* head;
  int size; 
  bool ll; 
  bool rr; 
  bool lr; 
  bool rl; 
} RedBlackTree; 

typedef struct {
  Node** queue; 
  int size; 
  int capacity; 
  int front; 
  int rear; 
} CircularQueue; 

RedBlackTree initialize_tree(); 
Node* initialize_node(int node_data); 
void free_tree(RedBlackTree* tree); 

void insert(RedBlackTree* tree, int node_data); 
Node* insert_helper(RedBlackTree tree, Node* root, int node_data); 

void delete(Node* root, int node_to_delete); 

bool search(Node* root, int node_data); 

int size(Node* root, int current_sum); 

void ll_rotation(Node* root); 
void lr_rotation(Node* root); 
void rr_rotation(Node* root); 
void rl_rotation(Node* root); 

int height(Node* root); 
int get_max(int a, int b);

int invert(Node* root); 

void enqueue(CircularQueue* queue, Node* node); 
Node* dequeue(CircularQueue* queue);

int main() {
  return 0; 
}

/**
 * =========================================
 * || RedBlackTree Method Implementations ||
 * =========================================
 */

/**
 * ====================================
 * || Circular Queue Implementations ||
 * ====================================
 */

CircularQueue initialize_queue() {

  CircularQueue queue; 
  queue.queue = (Node**) malloc(sizeof(Node) * QUEUE_CAPACITY); 

  if(queue.queue == NULL) {
    exit(EXIT_FAILURE); 
  }

  queue.capacity = QUEUE_CAPACITY; 
  queue.size = 0; 
  queue.front = 0; 
  queue.rear = -1; 

  return queue;  
}

void enqueue(CircularQueue* queue, Node* node) {
  if(queue->capacity == queue->size) return;

  queue->rear += 1; 
  queue->queue[queue->rear] = node;
  queue->size += 1; 
}; 

Node* dequeue(CircularQueue* queue) {
  if(queue->size == 0) return NULL;

  Node* node = queue->queue[queue->front]; 
  queue->front += 1; 
  queue->size -= 1; 

  if(queue->size == 0) {
    queue->front = 0; 
    queue->rear = -1; 
  }

  return node; 
}
