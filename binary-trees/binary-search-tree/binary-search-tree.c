#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_CAPACITY 20
#define RUN_TESTS true 
#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

typedef struct {
  int data; 
  void* left; 
  void* right; 
} Node;

typedef struct {
  int size; 
  Node* root; 
} BST; 

typedef struct {
  Node** queue; 
  int size; 
  int capacity; 
  int front; 
  int rear; 
} CircularQueue; 

/**
 * ===========================================
 * || Binary Search Tree Method Definitions ||
 * ===========================================
 *
 * Below are the general methods that will be implemented for the BST
 */


// Setup & tear down methods

BST initialize_tree(); 
Node* initialize_node(int node_data);
void free_tree(BST* tree); 

// Util Methods 

bool insert(BST* tree, int node_data); 
bool insert_helper(Node* node, int node_data); 

bool delete(BST* tree, int node_data);
bool delete_helper(Node* node, int node_data); 

bool search(BST* tree, int node_data); 
bool search_helper(Node* node, int node_data);

int size(BST* tree); 
int count_nodes(BST* tree); 

int height(BST* tree); 
int height_helper(Node* node); 
int get_max(int a, int b); 

Node* find_min(Node* root); 
Node* find_max(Node* root); 
Node* successor(Node* root, int target); 
Node* predecessor(Node* root, int target);

void invert(BST* tree); 

// DFS Traversal

void inorder_tree_walk(Node* node); 
void preorder_tree_walk(Node* node); 
void postorder_tree_walk(Node* node); 

/**
 * ======================================
 * || CircularQueue Method Definitions ||
 * ======================================
 */

CircularQueue initialize_queue(); 
Node* dequeue(CircularQueue* queue); 
bool enqueue(CircularQueue* queue, Node* node); 


// Test Methods

/** 
 * ==========================
 * || Main program methods ||
 * ==========================
 */

int main() {
  printf("%d\n", 20 % 20); 
  return 0; 
}

/** 
 * ========================================
 * || Binary Tree Method Implementations ||
 * ========================================
 */

/**
 * The wrapper function for searching for a given node in the tree 
 *
 * @returns: A boolean value depending on whether the node was found 
 */

bool search(BST* tree, int node_data) {
  if(tree->root == NULL) return false; 

  bool is_found = search_helper(tree->root, node_data); 

  return is_found;
}

/**
 * TODO: This is not how you search in a BST given the found_left found_right options (Please change) 
 *
 * A Helper function to search recursively through the tree 
 *
 * @param: node - The current node to check the data of
 * @param: node_data - The node data to search for
 * 
 * @returns: A boolean value depending on whether the node was found
 */

bool search_helper(Node* node, int node_data) {
  if(node == NULL) return false; 

  if(node->data == node_data) return true; 

  bool found_left = search_helper(node->left, node_data); 
  bool found_right = search_helper(node->right, node_data); 

  return found_left || found_right; 
}

/** 
 * Inorder tree walk 
 *
 * This method prints the nodes from deepest left, then it's parent, then deepest right (should they exist) 
 *
 * @param: node - The current node (starts with the tree root) 
 */

void inorder_tree_walk(Node* node) {
  if(node == NULL) return; 
 
  inorder_tree_walk(node->left); 
  printf("%d ", node->data); 
  inorder_tree_walk(node->right); 
}

/** 
 * Preorder tree walk 
 *
 * This method prints the root - then the left subtree downwards (from left to right) then the right subtree (from left to right)  
 *
 * @param: node - The current node (starts with the tree root) 
 */

void preorder_tree_walk(Node* node) {
  if(node == NULL) return; 
  
  printf("%d ", node->data); 
  preorder_tree_walk(node->left);
  preorder_tree_walk(node->right); 
}

/** 
 * Preorder tree walk 
 *
 * This method prints the deepest nodes first from left to right (traversing the left subtree first)
 *
 * @param: node - The current node (starts with the tree root) 
 */

void postorder_tree_walk(Node* node) {
  if(node == NULL) return; 

  postorder_tree_walk(node->left); 
  postorder_tree_walk(node->right); 
  printf("%d ", node->data); 
}

/**
 * Get the height of the tree 
 *
 * @param: tree - The BST to get the height
 * @returns: An integer representation of the height/depth/number of levels in the tree 
 */

int height(BST* tree) {
  if(tree->root == NULL) return -1; 
  if(tree->size == 0) return -1; 

  int tree_height = height_helper(tree->root); 

  return tree_height;  
}

/** 
 * A recursive search to find the maximum height/depth of the tree
 *
 * @param: node - Starts at the root then recursively searches through the tree
 * @returns: When the full stack has been searched it will return the largest number found (the height of the tree) 
 */

int height_helper(Node* node) {
  if(node == NULL) return -1; 

  int tree_left_height = height_helper(node->left); 
  int tree_right_height = height_helper(node->right); 

  return 1 + get_max(tree_left_height, tree_right_height);  
}

/**
 * Get the max between two integers 
 *
 * @param: (a, b) - The two integers to compare 
 * @returns: The max number of the two integer arguments
 */

int get_max(int a, int b) {
  return (a > b) ? a : b;  
}

/**
 * ===========================================
 * || CircularQueue Methods Implementations ||
 * ===========================================
 */

CircularQueue initialize_queue() {
  CircularQueue queue; 
  queue.queue = (Node**) malloc(sizeof(Node) * QUEUE_CAPACITY); 
  queue.capacity = QUEUE_CAPACITY; 
  queue.size = 0; 
  queue.front = 0; 
  queue.rear = -1; 
  
  return queue; 
}

bool enqueue(CircularQueue* queue, Node* node) {

  if(queue->size == queue->capacity) return false;  
  if(queue == NULL || node == NULL) return false; 

  queue->queue[queue->rear] = node;  
  queue->size += 1; 
  queue->rear = (queue->rear + 1) % QUEUE_CAPACITY; 

  return true; 
}

Node* dequeue(CircularQueue* queue) {
  if(queue->size == 0 || queue->rear == -1) return false;  
  if(queue == NULL) return false; 

  Node* front = queue->queue[queue->front]; 
  queue->front = (queue->front + 1) % queue->capacity; 
  queue->size -= 1; 

  if(queue->size == 0) {
    queue->front = 0; 
    queue->rear = -1; 
  }

  return front; 
}




