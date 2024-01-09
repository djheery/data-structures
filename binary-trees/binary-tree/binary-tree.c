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
  Node* root; 
  int size; 
} BinaryTree; 

typedef struct {
  Node** queue; 
  size_t capacity;  
  size_t size;  
} Queue;

// Queue Utility 

Queue initialize_queue(int capacity); 
void enqueue(Queue* queue, Node* node); 
Node* dequeue(Queue* queue); 

// Binary Tree Methods 

BinaryTree intialize_binary_tree(); 
Node* initialize_node(int data); 
void height(BinaryTree* tree); 
void size(BinaryTree* tree); 
void level(BinaryTree* tree); 
void search(BinaryTree* tree); 
void insert(BinaryTree* tree, int node_data); 
void delete(BinaryTree* tree, int node_data);
void pre_order_traversal(BinaryTree* tree); 
void in_order_traversal(Node* tree); 
void post_order_traversal(BinaryTree* tree); 

// Tester methods 
void run_tests(); 
void populate_tree(BinaryTree* test_tree);

/**
 * ==========================
 * || Main Program Methods ||
 * ==========================
 */

int main() {
  if(RUN_TESTS) {
    run_tests(); 
  }
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

BinaryTree initialize_binary_tree() {
  BinaryTree tree; 
  tree.root = NULL; 

  return tree; 
}

Node* initialize_node(int data) {
  Node* node = (Node*) malloc(sizeof(Node)); 

  if(node == NULL) {
    printf("There has been an error allocating the memory for the node\n\n"); 
    exit(EXIT_FAILURE); 
  }

  node->data = data; 
  node->left = NULL; 
  node->right = NULL; 

  return node; 
}

void free_tree_nodes(BinaryTree* tree) {
  if(tree->root == NULL) return; 

  Queue q = initialize_queue(20); 
  enqueue(&q, tree->root); 

  while(q.size != 0) {
    Node* current = dequeue(&q);  

    if(current->left != NULL) enqueue(&q, current->left);
    if(current->right != NULL) enqueue(&q, current->right); 

    DEBUG_PRINT("Freeing Node: %d\n", current->data);
    free(current); 
  }

  DEBUG_PRINT("List freed sucessfully!!\n\n", NULL); 
}

void insert(BinaryTree* tree, int node_data) {

  Node* new_node = initialize_node(node_data);

  if(tree->root == NULL) {
    tree->root = new_node;     
    return; 
  }

  Queue queue = initialize_queue(20); 
  enqueue(&queue, tree->root); 

  while(queue.size != 0) {
    Node* current_node = dequeue(&queue); 
    printf("CURRENT_DATA: %d\n", current_node->data); 

    if(current_node->left != NULL) {
      enqueue(&queue, current_node->left);  
    } else {
      current_node->left = new_node; 
      break;
    }

    if(current_node->right != NULL) {
      enqueue(&queue, current_node->right); 
    } else {
      current_node->right = new_node; 
      break; 
    }
  }
}


void delete(BinaryTree* tree, int node_data) {

  if(tree->root == NULL) return; 

  bool no_leaves = tree->root->left == NULL && tree->root->right == NULL; 

  if(no_leaves && tree->root->data == node_data) {
    free(tree->root);  
    tree->root = NULL; 
  }

  if(no_leaves && tree->root->data != node_data) return; 

  bool node_found = false;  

  Queue queue = initialize_queue(20);
  enqueue(&queue, tree->root); 

  Node* current_node = NULL; 
  Node* node_to_delete = NULL; 
  Node* prev = NULL; 


  while(queue.size != 0) {
    Node* current_node = dequeue(&queue); 

    if(current_node->data == node_data && node_to_delete == NULL) {
      node_to_delete = current_node;  
    }

    if(current_node->left != NULL) enqueue(&queue, current_node->left); 
    if(current_node->right != NULL) enqueue(&queue, current_node->right); 

    // If the following condition is true we are at the deepest rightmost node (due to inorder traversal thus: 
    // - set the node_to_deletes data to the deepest node data 
    // - free the deepest node 
    // - Set the prev node left or right to NULL depending on which points to the deepest node 
    
    if(queue.size == 0 && node_to_delete == current_node) {
      if(prev->left == current_node) prev->left = NULL; 
      if(prev->right == current_node) prev->right = NULL; 

      free(current_node); 
    }

    if(queue.size == 0 && node_to_delete != NULL) {
      node_to_delete->data = current_node->data; 

      if(prev->left == current_node) prev->left = NULL; 
      if(prev->right == current_node) prev->right = NULL; 

      free(current_node); 
      break; 
    }

    if(current_node->left != NULL || current_node->right != NULL) {
      prev = current_node;  
    }
  }

  if(node_to_delete == NULL) return; 
}

void in_order_traversal(Node* node) {
  if(node == NULL) return; 

  printf("%d ", node->data); 

  in_order_traversal(node->left); 
  in_order_traversal(node->right); 
}

/**
 * =====================
 * || Testing Methods ||
 * =====================
 */

void populate_tree(BinaryTree* test_tree) {

  insert(test_tree, 5);  
  insert(test_tree, 10); 
  insert(test_tree, 15); 
  insert(test_tree, 20); 

  // expected order 5 10 15 20
  in_order_traversal(test_tree->root);
  printf("\n\n"); 
}

void run_tests() {
  DEBUG_PRINT("HELLO TEST\n", NULL);
  BinaryTree test_tree = initialize_binary_tree();  
  DEBUG_PRINT("TEST TREE\n", NULL);

  populate_tree(&test_tree); 

  free_tree_nodes(&test_tree); 
}

/**
 * =====================
 * || Queue Methods   ||
 * =====================
 *
 * Queues are needed for different operations so I have added a very basic queue at the bottom of the file
 */

Queue initialize_queue(int capacity) {
  Queue queue; 
  queue.size = 0; 
  queue.capacity = capacity; 
  queue.queue = (Node**) malloc(capacity * sizeof(Node)); 

  if(queue.queue == NULL) {
    printf("Error Intializing Queue\n"); 
    printf("Exiting Program...\n\n"); 
    exit(EXIT_FAILURE);
  }
  
  return queue; 
}; 

void enqueue(Queue* queue, Node* node) {
  if(queue->size == queue->capacity) {
    printf("Adding another item to the queue is impossible, you should restrict this program to your usecase\n\n"); 
    return; 
  }

  queue->queue[queue->size] = node; 
  queue->size += 1;
}

Node* dequeue(Queue* queue) {
  Node* d = queue->queue[0];  
  
  for(int i = 0; i < queue->size; i++) {
    queue->queue[i] = queue->queue[i + 1]; 
  }

  queue->size -= 1; 

  return d;
}
