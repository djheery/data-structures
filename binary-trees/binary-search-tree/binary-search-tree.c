#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define QUEUE_CAPACITY 20
#define RUN_TESTS true 
#define DEBUG
#define MIN_INT_ALLOWED 1 
#define MAX_INT_ALLOWED 100
#define ROOT_DATA 50
#define ALLOW_DUPLICATES true

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

BST initialize_tree(bool is_test); 
Node* initialize_node(int node_data);
void free_tree(BST* tree); 

// Util Methods 

bool insert(BST* tree, int node_data); 
Node* insert_helper(Node* current_node, int node_data); 

bool delete(BST* tree, int node_data);
<<<<<<< HEAD
Node* delete_helper(Node* root, int node_data); 
Node* delete_node_handler(Node* root);
=======
Node* delete_helper(BST* tree, Node* node, int node_data); 
Node* inorder_successor(Node* root); 
>>>>>>> fa77c3771c8ca497577d8eacb146e66d2a7abd8a

Node* search(BST* tree, int node_data); 
Node* search_helper(Node* node, int node_data);

int size(BST* tree); 
int count_nodes(BST* tree); 

int height(BST* tree); 
int height_helper(Node* node); 
int get_max(int a, int b); 

Node* find_min(Node* root); 
Node* find_max(Node* root); 

Node* inorder_successor(Node* root); 
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


Node* initialize_node(int node_data) {
  Node* node = (Node*) malloc(sizeof(Node));  

  if(node == NULL) {
    DEBUG_PRINT("ERROR CREATING NODE\n\n", NULL); 
    return NULL;   
  }

  node->data = node_data; 
  node->left = NULL; 
  node->right = NULL; 

  return node; 
}

/**
 * Initialize the Tree 
 *
 * @param: is_test -> This is a flag that is used to decide whether to initialize a root node or not
 */

BST initialize_tree(bool is_test) {
  BST tree; 
  tree.root = is_test ? initialize_node(ROOT_DATA) : NULL; 
  tree.size = 1; 
  return tree; 
}

/**
 * Free the tree nodes from memory 
 *
 * @param: tree -> The BST to free the nodes from
 */

void free_tree(BST* tree) {
  if(tree->root == NULL) return; 

  CircularQueue queue = initialize_queue(); 
  enqueue(&queue, tree->root); 

  while(queue.size != 0) {
    Node* current = dequeue(&queue);

    if(current->left != NULL) enqueue(&queue, current->left); 
    if(current->right != NULL) enqueue(&queue, current->right); 

    DEBUG_PRINT("Freeing node: %d\n", current->data); 
    free(current); 
  }

  free(queue.queue); 

  DEBUG_PRINT("\n\nList Freed Succesfully!\n\n", NULL);
}

/**
 * Wrapper method for handling insertion into the binary tree 
 *
 * @param: tree -> The Tree to insert into 
 * @param: node_data -> The data to be added to the new node 
 *
 * @returns: A boolean value depending of whether there was a succesful insertion 
 */

bool insert(BST* tree, int node_data) {

  if(node_data < MIN_INT_ALLOWED || node_data > MAX_INT_ALLOWED) {
    return false; 
  }

  if(tree->root == NULL) {
    tree->root = initialize_node(node_data); 
    tree->size = 1; 
    return true; 
  }

  Node* root = insert_helper(tree->root, node_data);

  bool is_root = root == tree->root; 

  if(!is_root) {
    printf("Something is very odd with your insertion or your understanding of recursive insertion\n\n"); 
  }

  return is_root;      
}

/**
 * A helper for the insertion function to insert recursively 
 *
 * @param: current_node -> The current node to evaluate 
 * @param: node_data -> The node data to insert
 *
 * @returns: The current_node (As this is recursive it should eventually return the root back to the initial caller)
 */

Node* insert_helper(Node* current_node, int node_data) {

  if(current_node == NULL) {
    Node* new_node = initialize_node(node_data); 
    return new_node; 
  }

  bool is_equal = current_node->data == node_data; 

  if(is_equal && !ALLOW_DUPLICATES) {
    printf("DUPLICATES_NOT_ALLOWED!\n\n");  
    return current_node; 
  }

  if(current_node->data < node_data) {
    current_node->right = insert_helper(current_node->right, node_data);
  }; 

  if((current_node->data > node_data) || (is_equal && ALLOW_DUPLICATES)) {
    current_node->left = insert_helper(current_node->left, node_data); 
  }


  return current_node; 
}

bool delete(BST* tree, int node_data) {
  
  if(tree->root == NULL || tree->size == 0) {
    return false; 
  }

  delete_helper(tree->root, node_data); 

  return true; 
}

/**
 * A recursive delete function to find the node to delete 
 * This node is then passed to the delete handler to get the successor and delete accordingly 
 *
 * @param: root -> Starts with the root of the tree then recursively calls itself with the next given node until the deletion node is found
 * @param: node_data -> The node data to search for and thus the node to delete
 * @returns: Eventually returns the root of the tree
 */

Node* delete_helper(Node* root, int node_data) {
  if(root == NULL) return NULL;  


  if(node_data < root->data) {
    root->left = delete_helper(root->left, node_data); 
    return root;
  } else if (node_data > root->data) {
    root->right = delete_helper(root->right, node_data); 
    return root; 
  } 

  if(root->left == NULL) {
    Node* temp = root->right; 
    free(root); 
    return temp;
  }

  if(root->right == NULL) {
    Node* temp = root->left; 
    free(root); 
    return temp; 
  }

<<<<<<< HEAD
=======
  Node* successor_node = inorder_successor(root); 

  if(successor_node == NULL) {
    exit(EXIT_FAILURE);
  }

  root->data = successor_node->data; 
  free(successor_node);
>>>>>>> fa77c3771c8ca497577d8eacb146e66d2a7abd8a
  
  return delete_node_handler(root); 
}

/**
 * A method to handle the deletion of a given node 
 * 
 * The method works by finding the inorder_successor of a given node, replacing the root->data with the successor->data and 
 * assigning its left and right accordingly 
 *
 * if the parent is equal to the root passed in then we should make the root->right = to the successor->right 
 *  - This is because we are assigning the root to the data of the successor (which is the right node of the successor) and since 
 *    The while loop has been skipped this means the successors left is null so we can only assign the right to the parent 
 * if the parent is not equal to the root then we can assign the parent->left to the successor->right 
 *  - This is because we are replacing the roots data with the successor which will be the furthest left node and the parent will not be the root 
 *    So we need to make sure that any leaf nodes are not detatched. As we know that the successor does not have another left node the only place that could be a node 
 *    is the right node so we make sure that the parents left node = the successor->right node (which will always be less than the parent because of the way BSTs are constructed 
 *    Before assigning the successors data to the root node (node to delete/replace) then we free the successor
 *
 * then replaced the root data with the successors data and free the successor 
 *
 * @param: root - The node with the data to delete 
 * @returns: The root with the new data associated inside it (The data of the inorder successor which has been freed) 
 */

Node* delete_node_handler(Node* root) {
  Node* parent = root; 
  Node* succ = parent->right; 

  while(succ->left != NULL) {
    parent = succ;
    succ = root->left; 
  }

  if(parent != root) {
    parent->left = succ->right; 
  } else {
    parent->right = succ->right; 
  }

  root->data = succ->data; 
  free(succ); 

  return root; 
}

/** 
 * Get the inorder_successor of a given node
 *
 * @param: root - The node to get the inorder successor for 
 * @returns: The inorder successor
 */

Node* inorder_successor(Node* root) {
  Node* parent = root; 
  Node* succ = parent->right; 

  while(succ->left != NULL) {
    parent = succ;
    succ = root->left; 
  }

  if(succ->right != NULL) {
    prevSucc->left = succ->right;  
  }

  return succ;   
}

/**
 *  WARNING: After using this method the insertion, deletion and search will be broken
 *  TODO: Implement a flag to tell whether a tree is inverted and then perform the other operations based on this flag
 *
 * A method using for inverting the tree 
 *
 * @param: root - Starting with the tree->root then recursively inverts the left Subtree then the right subtree
 * @returns: The root of the tree eventually
 */

Node* invert_tree(Node* root) {
   if(root == NULL) return NULL; 

   Node* prevLeft = invert_tree(root->left); 
   root->left = invert_tree(root->right); 
   root->right = prevLeft; 

   return root; 
}

/**
 * The wrapper function for searching for a given node in the tree 
 *
 * @returns: A boolean value depending on whether the node was found 
 */

Node* search(BST* tree, int node_data) {
  if(tree->root == NULL) return false; 

  Node* found_node = search_helper(tree->root, node_data); 

  return found_node;
}

/**
 *
 * A Helper function to search recursively through the tree 
 *
 * @param: node - The current node to check the data of
 * @param: node_data - The node data to search for
 * 
 * @returns: A boolean value depending on whether the node was found
 */

Node* search_helper(Node* node, int node_data) {
  if(node == NULL) return NULL; 

  if(node->data == node_data) return node; 

  Node* found = NULL; 

  if(node->data > node_data) found = search_helper(node->left, node_data); 
  if(node->data < node_data) found = search_helper(node->right, node_data); 

  return found; 
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

  queue->rear = (queue->rear + 1) % QUEUE_CAPACITY; 
  queue->queue[queue->rear] = node;  
  queue->size += 1; 

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




