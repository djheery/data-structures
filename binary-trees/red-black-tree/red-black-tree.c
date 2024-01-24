#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

#define RED 1
#define BLACK 0
#define QUEUE_CAPACITY 30 
#define DEBUG 

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

typedef struct {
  int data; 
  void* parent; 
  void* left; 
  void* right; 
  int color; 
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

/**
 * =======================================
 * || Red Black Tree Method Definitions ||
 * =======================================
 *
 * Below are the methods that will be implemented on the Red Black tree
 */

// Setup/ Teardown Methods

RedBlackTree initialize_tree(); 
Node* initialize_node(int node_data); 
void free_tree(RedBlackTree* tree); 

// Util Methods 

void insert(RedBlackTree* tree, int node_data); 
Node* insert_helper(RedBlackTree tree, Node* root, int node_data); 

void delete(Node* root, int node_to_delete); 

bool search(RedBlackTree* tree, int node_data); 
bool search_helper(Node* root, int node_data); 

int size(Node* root, int current_sum); 

void ll_rotation(Node* root); 
void lr_rotation(Node* root); 
void rr_rotation(Node* root); 
void rl_rotation(Node* root); 

int height(Node* root); 
int get_max(int a, int b);

Node* invert_tree(Node* root); 

/**
 * =======================================
 * || Circular Queue Method definitions ||
 * =======================================
 */

CircularQueue initialize_queue(); 
void enqueue(CircularQueue* queue, Node* node); 
Node* dequeue(CircularQueue* queue);

/**
 * ================================
 * || Testing Method Definitions ||
 * ================================
 */

void run_tests(); 
void populate_tree(RedBlackTree* test_tree); 
void test_insertion(RedBlackTree* test_tree); 
void test_deletion(RedBlackTree* test_tree); 
void test_search(RedBlackTree* test_tree); 

/**
 * ==========================
 * || Main Program Methods ||
 * ==========================
 */ 

int main() {
  return 0; 
}

/**
 * =========================================
 * || RedBlackTree Method Implementations ||
 * =========================================
 */

/**
 * Initialize a RedBlack Tree 
 *
 * @returns: A RedBlackTree to do some stuff with
 */

RedBlackTree initialize_tree() {
  RedBlackTree tree; 

  tree.head = NULL; 
  tree.size = 0; 
  tree.rl = false; 
  tree.rr = false; 
  tree.ll = false; 
  tree.lr = false; 

  return tree;  
}

/** 
 * Initialize a Node (pointer) for the RedBlackTree
 *
 * @param: node_data -> The data to insert into the node 
 * @returns: A pointer to the node on the heap
 */

Node* initialize_node(int node_data) {
  Node* node = (Node*) malloc(sizeof(Node));  

  if(node == NULL) {
    DEBUG_PRINT("Error initializing Node: %d\n", node_data); 
    DEBUG_PRINT("Exiting Program\n\n", NULL); 
    exit(EXIT_FAILURE); 
  }

  node->data = node_data; 
  node->parent = NULL; 
  node->left = NULL; 
  node->right = NULL; 
  node->color = RED; 

  return node;
}

/**
 * Free the RedBlackTree Nodes 
 *
 * @param: tree - The RedBlackTree to free the nodes of
 */

void free_tree(RedBlackTree* tree) {
  if(tree == NULL || tree->head == NULL) {
    return; 
  }

  CircularQueue queue = initialize_queue(); 
  enqueue(&queue, tree->head); 

  while(queue.size != 0) {
    Node* current = dequeue(&queue);  

    if(current->left != NULL) enqueue(&queue, current->left); 
    if(current->right != NULL) enqueue(&queue, current->right); 
    
    DEBUG_PRINT("Freeing Node: %d\n", current->data); 
    free(current); 
  }

  DEBUG_PRINT("\nList Feed Successfully\n\n", NULL); 

  tree->head = NULL; 
  tree->size = 0; 
  tree->rl = false; 
  tree->rr = false; 
  tree->ll = false; 
  tree->lr = false; 

}

/**
 * A method to search for whether a node with specific data exists within the tree
 *
 * @param: tree -> The tree to search 
 * @param: data_to_search -> the Data to search for 
 * @returns: A boolean value representing whether a node with the given data was found
 */


bool search(RedBlackTree* tree, int data_to_search) {
  
  // Not really necessary but whatever
  if(tree->head == NULL || tree->size == 0) return false;  
  if(tree->head->data == data_to_search) return true; 
  if(tree->head->data != data_to_search && tree->size == 1) return false; 

  return search_helper(tree->head, data_to_search); 
}

/**
 * Search for a node in the tree 
 *
 * @param: root -> The current node being searched 
 * @param: data_to_search -> The data to search for 
 * @returns: A boolean value representing whether a node with the given data was found
 */ 

bool search_helper(Node* root, int data_to_search) {
  if(root == NULL) return false; 

  if(root->data == data_to_search) return true; 

  bool found = false; 

  if(data_to_search < root->data) found = search_helper(root->left, data_to_search);
  if(data_to_search > root->data) found = search_helper(root->right, data_to_search);  

  return found; 
}

Node* invert_tree(Node* root) {
  if(root == NULL) return NULL; 

  Node* prevLeft = invert_tree(root->left); 
  root->left = invert_tree(root->right); 
  root->right = prevLeft; 

  return root; 
}

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
