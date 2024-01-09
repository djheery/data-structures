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
} Queue; 

/**
 * ================================
 * || Binary Search Tree Methods ||
 * ================================
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
int height_helper(BST* tree); 
int height_max_util(int a, int b); 

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
 * ===================
 * || Queue Methods ||
 * ================== 
 */

Queue initialize_queue(); 


// Test Methods

/** 
 * ==========================
 * || Main program methods ||
 * ==========================
 */

int main() {
  return 0; 
}

