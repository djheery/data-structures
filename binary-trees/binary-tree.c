/**
 * =======================
 * || Basic Binary Tree ||
 * =======================
 *
 * This is my first full construction of a binary tree by hand. I am simply using it to get to grips with how the data structure works. 
 *
 * Methods included: 
 *
 * - Height 
 * - Size 
 * - Level 
 * - Search 
 * - Insert 
 * - Delete 
 * - Post order tree walk 
 * - Pre order tree walk 
 * - In order tree walk 
 * - DFS 
 * - BFS 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
  int data; 
  void* left; 
  void* right; 
} Node; 

typedef struct {
  Node* root; 
  int size; 
} BinaryTree; 

typedef struct {
  int* queue; 
  size_t capacity;  
  size_t size;  
} Queue;

// Queue Utility 

Queue initialize_queue(int capacity); 
void enqueue(Queue* queue, int data); 
int dequeue(Queue* queue); 

// Binary Tree Methods 

void height(BinaryTree* tree); 
void size(BinaryTree* tree); 
void level(BinaryTree* tree); 
void search(BinaryTree* tree); 
void insert(BinaryTree* tree); 
void delete(BinaryTree* tree);
void pre_order_traversal(BinaryTree* tree); 
void in_order_traversal(BinaryTree* tree); 
void post_order_traversal(BinaryTree* tree); 
void depth_first_search(BinaryTree* tree); 
void breadth_first_search(BinaryTree* tree);

/**
 * ==========================
 * || Main Program Methods ||
 * ==========================
 */

int main() {
  return 0; 
}

void program_loop() {
  
}

void print_menu() {
  
}

int get_user_input() {
  return -1; 
}

bool validate_user_input() {
  return false; 
}

/**
 * =================================
 * || Binary Tree Utility Methods ||
 * =================================
 */

/**
 * =====================
 * || Queue Methods   ||
 * =====================
 *
 * Queues are needed for different operations so I have added a very basic queue at the bottom of the file
 */

Queue intialize_queue(int capacity) {
  Queue queue; 
  queue.size = 0; 
  queue.capacity = capacity; 
  queue.queue = (int*) malloc(capacity * sizeof(int)); 

  if(queue.queue == NULL) {
    printf("Error Intializing Queue\n"); 
    printf("Exiting Program...\n\n"); 
    exit(EXIT_FAILURE);
  }
  
  return queue; 
}; 

void enqueue(Queue* queue, int data) {
  if(queue->size == queue->capacity) {
    printf("Adding another item to the queue is impossible, you should restrict this program to your usecase\n\n"); 
    return; 
  }

  queue->queue[queue->size] = data; 
  queue->size += 1;
}

int dequeue(Queue* queue) {
  int d = queue->queue[0];  
  
  for(int i = 0; i < queue->size; i++) {
    queue->queue[i] = queue->queue[i + 1]; 
  }

  queue->size -= 1; 

  return d;
}
