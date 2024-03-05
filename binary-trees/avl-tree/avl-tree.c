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
  uint16_t height; 
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

int16_t balance_factor(Node* x); 
uint16_t height(Node* x); 

bool node_exists(Node* root, int32_t node_data); 
Node* search_and_get(Node* root, int32_t node_data); 

void insert(AVLTree* tree, int32_t node_data); 
Node* insert_helper(AVLTree* tree, Node* root, int32_t node_data); 

void delete(AVLTree* tree, int32_t node_data); 
Node* delete_helper(AVLTree* tree, Node* root, int32_t node_data); 
Node* min_successor(Node* root); 

Node* rotate_left(Node* x); 
Node* rotate_right(Node* x); 

int get_tree_balance(Node* root); 

int get_tree_height(Node* root);
int get_max(uint a, uint b); 

void print_preorder(Node* root);
void print_postorder(Node* root);
void print_inorder(Node* root); 

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

/** 
 * Initialize a new AVL Tree
 *
 * @returns: A new AVL tree
 */

AVLTree initialize_tree() {
  AVLTree tree; 
  tree.root = NULL; 
  tree.size = 0;

  return tree; 
}

/**
 * Initialize a new node to be placed within the tree 
 *
 * @param: node_data -> an i32 representing the value for the new nodes data 
 * @returns: A pointer to the new node to be placed within the tree 
 */

Node* initialize_node(int32_t node_data) {
  Node* node = (Node*) malloc(sizeof(Node)); 

  if (node == NULL) {
    DEBUG_PRINT("Error  allocating memory for node with data: %d\n", node_data); 
    exit(EXIT_FAILURE); 
  }

  node->data = node_data; 
  node->left = NULL;
  node->right = NULL; 
  node->height = 1; 

  return node; 
}

/**
 * Free all tree nodes from memory 
 *
 * @param: tree -> The AVL tree to free the nodes from 
 */

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
 * Get the balance factor of node x by checking its decendents
 *
 * @param: x -> The node to check the balance factor of 
 * @returns: The balance factor of node x, ideally this should never be greater the 2 or less than -2 as this indicates that their is an unbalanced tree and rotations are needed; 
 */

int16_t balance_factor(Node* x) {
  if (x == NULL) return 0;  

  return height(x->left) - height(x->right); 
}

/** 
 * Get the height of a given node "x"
 *
 * @param: x -> The node to get the height of
 * @returns: the height of the given node or 0 should the node be NULL
 */

uint16_t height(Node* x) {
  if (x == NULL) return 0; 

  return x->height; 
}

/**
 * Get the max between two unsigned integers
 *
 * @param: { a, b } - The two integers to compare
 * @param: The max number of either a or b. If they are equal it will implicitly return b 
 */

uint16_t max(uint16_t a, uint16_t b) {
  return a > b ? a : b; 
}

/** 
 * AVL Tree left rotation method 
 *
 * @param: x -> The node to perform the rotation around
 * @returns: The new node in x's place with the heights set to their new value 
 */

Node* rotate_left(Node* x) {
  Node* y = x->right;  
  Node* z = y->left; 
  x->right = z; 
  y->left = x; 

  y->height = 1 + max(height(y->left), height(y->right)); 
  x->height = 1 + max(height(x->left), height(x->right)); 

  return y;
}

/** 
 * AVL Tree right rotation method 
 *
 * @param: x -> The node to perform the rotation around
 * @returns: The new node in x's place with the heights set to their new value 
 */

Node* rotate_right(Node* x) {
  Node* y = x->left; 
  Node* z = y->right; 
  x->left = z; 
  y->right = x; 

  y->height = 1 + max(height(y->left), height(y->right));
  x->height = 1 + max(height(x->left), height(x->right)); 

  return y; 
}

/**
 * Wrapper method for tree insert 
 *
 * @param: tree -> The tree to insert within 
 * @param: node_data -> The data to insert to a new node 
 */

void insert(AVLTree* tree, int32_t node_data) {
   tree->root = insert_helper(tree, tree->root, node_data); 
}

Node* insert_helper(AVLTree* tree, Node* root, int32_t node_data) {

  if (root == NULL) return initialize_node(node_data);
 
  if (node_data < root->data) {
    root->left = insert_helper(tree, root->left, node_data);
  } else if (node_data > root->data) {
    root->right = insert_helper(tree, root->right, node_data); 
  } 

  root->height = 1 + max(height(root->left), height(root->right)); 

  int16_t bf = balance_factor(root);

  // Check the balance of the tree 

  return root; 
}

/**
 * Searches the tree for a node with given node_data and returns it if it exists
 *
 * @param: root -> The current node being checked
 * @returns: The node with the given node_data or NULL if it does not exist
 */

Node* search_and_get(Node* root, int32_t node_data) {
  if (root == NULL) return NULL; 
  if (node_data == root->data) return root;

  Node* found_node; 

  if (node_data < root->data) found_node = search_and_get(root->left, node_data);
  if (node_data > root->data) found_node = search_and_get(root->right, node_data);

  return found_node; 
}

/**
 * Searches the tree for a node with the given node_data and returns a boolean value 
 * indicating whether the node exists
 * 
 * @param: root -> The current node being checked 
 * @param: node_data -> The node data to find 
 * @returns: a boolean value indicating whether a node with the given data has been found 
 */

bool node_exists(Node* root, int32_t node_data) {
  if (root == NULL) return false; 
  if (node_data == root->data) return true; 

  bool is_found = false; 

  if (node_data < root->data) is_found = node_exists(root->left, node_data);
  if (node_data > root->data) is_found = node_exists(root->right, node_data);
  
  return is_found; 
}

/**
 * Print the tree using Pre order traversal
 */

void print_preorder(Node* root) {
  if (root == NULL) return;  

  printf("%d ", root->data); 
  print_preorder(root->left);
  print_preorder(root->right); 

}

/**
 * Print the tree using in order traversal
 */

void print_inorder(Node* root) {
  if (root == NULL) return; 

  print_inorder(root->left);
  printf("%d ", root->data); 
  print_inorder(root->right); 
  
}

/**
 * Print the tree using post order traversal
 */

void print_postorder(Node* root) {
  if (root == NULL) return;

  print_postorder(root->left);
  print_postorder(root->right); 
  printf("%d ", root->data); 
  
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


