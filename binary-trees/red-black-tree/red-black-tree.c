#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

#define RED 1; 
#define BLACK 0; 
#define QUEUE_CAPACITY 30; 

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

void insert(Node* root, int node_data); 

void delete(Node* root, int node_to_delete); 

bool search(Node* root, int node_data); 

int size(Node* root, int current_sum); 

void left_rotation(Node* root); 
void right_rotation(Node* root); 

int height(Node* root); 
int get_max(int a, int b);

int invert(Node* root); 

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

void enqueue(CircularQueue* queue); 
