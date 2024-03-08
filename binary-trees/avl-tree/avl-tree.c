#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#define QUEUE_CAPACITY 50
#define DEBUG true

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

AVLTree clone(AVLTree* tree); 
Node* invert(Node* root); 

void print_preorder(Node* root);
void print_postorder(Node* root);
void print_inorder(Node* root); 

// Test Methods 

void test_insertion(AVLTree* test_tree); 
void test_deletion(AVLTree* test_tree); 
void test_search(AVLTree* test_tree); 
void test_inversion(AVLTree* test_tree); 

// Queue methods 

CircularQueue initialize_queue();
Node* dequeue(CircularQueue* circ_queue); 
void enqueue(CircularQueue* circ_queue, Node* node); 
void free_queue(CircularQueue* circ_queue); 


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

    if (current == NULL) {
      DEBUG_PRINT("SOMETHING WENT WRONG\n\n", NULL); 
      exit(EXIT_FAILURE);
    }

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

  x->height = 1 + max(height(x->left), height(x->right)); 
  y->height = 1 + max(height(y->left), height(y->right)); 

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

  x->height = 1 + max(height(x->left), height(x->right)); 
  y->height = 1 + max(height(y->left), height(y->right));

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

/**
 * A recursive insert method
 *
 * @param: tree -> The avl tree to insert into 
 * @param: root -> The current node being checked 
 * @param: node_data -> The data to insert into the new node 
 * @returns: Recursively returns the current node until reaching the root of the tree after insertion
 */

Node* insert_helper(AVLTree* tree, Node* root, int32_t node_data) {

  if (root == NULL) {
    Node* leaf = initialize_node(node_data); 
    tree->size += 1; 
    return leaf; 
  }

  if (root->data == node_data) {
    DEBUG_PRINT("Cannot add duplicate nodes with data: %d\n\n", node_data);
    return root;
  }
 
  if (node_data < root->data) {
    root->left = insert_helper(tree, root->left, node_data);
  } else if (node_data > root->data) {
    root->right = insert_helper(tree, root->right, node_data); 
  } 

  root->height = 1 + max(height(root->left), height(root->right)); 

  int16_t bf = balance_factor(root);

  Node* node_left = root->left; 
  Node* node_right = root->right; 

  // ll
  if (bf > 1 && node_data < node_left->data) {
    return rotate_right(root); 
  }

  // rr
  if (bf < -1 && node_data > node_right->data) {
    return rotate_left(root); 
  }

  // lr
  if (bf > 1 && node_data > node_left->data) {
    root->left = rotate_left(root->left); 
    return rotate_right(root); 
  }

  // rl 
  if (bf < -1 && node_data < node_right->data) {
    root->right = rotate_right(root->right);
    return rotate_left(root); 
  }

  return root; 
}

/**
 * Delete wrapper method 
 *
 * @param: tree -> The tree to delete from
 * @param: node_data -> The data of the node to find and delete 
 */

void delete(AVLTree* tree, int32_t node_data) {
  bool is_found = node_exists(tree->root, node_data); 

  if (!is_found) {
    DEBUG_PRINT("Node not found with data: %d\n\n", node_data);
    return; 
  } 

  tree->root = delete_helper(tree, tree->root, node_data); 

}

/**
 * A recursive delete method 
 *
 * @param: tree -> The tree to delete from; 
 * @param: root -> The current node being checked; 
 * @param: node_data -> The data of the node to delete; 
 * @returns: The current node and eventually bubbles back up to the tree root; 
 */

Node* delete_helper(AVLTree* tree, Node* root, int32_t node_data) {
   if (root == NULL) return NULL;

   if(node_data < root->data) {
     root->left = delete_helper(tree, root->left, node_data);
   } else if (node_data > root->data) {
     root->right = delete_helper(tree, root->right, node_data); 
   } else {

     if (root->left == NULL) {
       Node* temp = root;  
       root = root->right; 
       free(temp); 
     } else if (root->right == NULL) {
        Node* temp = root;  
        root = root->left;
        free(temp); 
     } else {
       Node* y = min_successor(root);
       root->data = y->data; 
       free(y);
     }

     tree->size -= 1; 
   }

   if (root == NULL) return NULL; 

   // Rebalance tree
   root->height = 1 + max(height(root->left), height(root->right)); 

   int16_t bf = balance_factor(root);

   if (bf > 1 && balance_factor(root->left) >= 0) {
      return rotate_right(root); 
   }

   if (bf < -1 && balance_factor(root->right) <= 0) {
      return rotate_left(root); 
   }

   if (bf > 1 && balance_factor(root->left) < 0) {
     root->left = rotate_left(root->left); 
     return rotate_right(root); 
   }

   if (bf < -1 && balance_factor(root->right) > 0) {
      root->right = rotate_right(root->right); 
      return rotate_left(root); 
   }


  
   return root; 
}

/**
 * Get the min successor of node 
 * Primarily used as a utility method for test_deletion
 *
 * @param: root -> The node to get the min_successor of
 * @returns: The min-successor of the root->rights children 
 */

Node* min_successor(Node* root) {
  Node* parent = root;
  Node* successor = parent->right; 

  while(successor->left != NULL) {
    parent = successor;
    successor = successor->left; 
  }

  if (parent != root) {
    parent->left = successor->right;
  } else {
    parent->right = successor->right; 
  }

  return successor;
}

AVLTree clone(AVLTree* tree) {
  AVLTree tree_clone = initialize_tree();
  CircularQueue circ_queue = initialize_queue(); 

  enqueue(&circ_queue, tree->root);

  while(circ_queue.length != 0) {
    Node* current = dequeue(&circ_queue);

    if (current->left != NULL) enqueue(&circ_queue, current->left);
    if (current->right != NULL) enqueue(&circ_queue, current->right);

    insert(&tree_clone, current->data);
  }

  free_queue(&circ_queue);

  return tree_clone; 
}


Node* invert(Node* root) {
  if (root == NULL) return NULL; 

  Node* prevLeft = invert(root->left); 
  root->left = invert(root->right); 
  root->right = prevLeft; 

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

bool check_invariants(Node* root, int32_t node_data) {
  if (root == NULL) return 0;  
  

  int16_t bf = balance_factor(root);
  bool meets_invariants = true; 

  if(bf < -1 || bf > 1) {
    meets_invariants = false; 
    DEBUG_PRINT("After insertion or deletion of node %d a potential violation has occrured at node: %d, BF: %d\n\n", node_data, root->data, bf);
  }

  check_invariants(root->left, node_data);
  check_invariants(root->right, node_data);

  return meets_invariants; 
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
 * ============= 
 * || Testing ||
 * ============= 
 */

void test_insertion_helper(AVLTree* tree, int32_t node_data) {
  insert(tree, node_data);  
  bool meets_invariants = check_invariants(tree->root, node_data);
  printf("Node to insert: %d\n", node_data); 

  if (!meets_invariants) {
    printf("\nInsertion of node %d potentially destroys Invariants\n", node_data);
  }
  
  print_inorder(tree->root);
  printf("\nRoot: %d\n", tree->root->data); 
  

}

void test_insertion(AVLTree* tree) {
  
  DEBUG_PRINT("\n\n================", NULL);
  DEBUG_PRINT("\n|| Insertion  ||", NULL);
  DEBUG_PRINT("\n================\n", NULL);

  int nums[] = { 10, 20, 30, 40, 50, 25, 35, 63, 42, 22, 15, 7 }; 

  int i; 
  for (i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
    test_insertion_helper(tree, nums[i]); 
    printf("\n");
  }

}

void test_deletion_helper(AVLTree* tree, int32_t node_data) {
  delete(tree, node_data);  
  bool meets_invariants = check_invariants(tree->root, node_data);
  printf("Node to delete: %d\n", node_data); 

  if (!meets_invariants) {
    printf("\nDelete of node %d potentially destroys invariants\n", node_data);
  }

  print_inorder(tree->root);
  printf("\nRoot: %d\n", tree->root->data); 
}

void test_deletion(AVLTree* tree) {

  DEBUG_PRINT("\n\n================", NULL);
  DEBUG_PRINT("\n|| Deletion   ||", NULL);
  DEBUG_PRINT("\n================\n", NULL);

  int nums[] = { 10, 50, 30, 25, 42, 55, 12, 7 }; 

  int i; 

  for (i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
    test_deletion_helper(tree, nums[i]);  
    printf("\n");
  }

}

void test_invert_tree(AVLTree* tree) {

  DEBUG_PRINT("\n\n================", NULL);
  DEBUG_PRINT("\n|| Inversion  ||", NULL);
  DEBUG_PRINT("\n================\n", NULL); 

  DEBUG_PRINT("Before: ", NULL);
  print_inorder(tree->root);
  printf("\n", NULL);

  AVLTree tree_clone = clone(tree); 
  invert(tree_clone.root);

  DEBUG_PRINT("After: ", NULL);
  print_inorder(tree_clone.root);
  printf("\n\n", NULL);
  

  free_tree(&tree_clone); 
}

void test_search(AVLTree* tree) {

  DEBUG_PRINT("\n\n================", NULL);
  DEBUG_PRINT("\n|| Search     ||", NULL);
  DEBUG_PRINT("\n================\n", NULL);

  int nums[] = { 10, 14, 83, 4, 50, 30, 25, 42, 55, 12, 7 }; 


  for (int i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
    bool exists = node_exists(tree->root, nums[i]); 

    DEBUG_PRINT("Node %d is found: %s\n", nums[i], exists ? "TRUE" : "FALSE");
  }

  DEBUG_PRINT("\n", NULL);

}

void run_tests() {
  AVLTree test_tree = initialize_tree();   

  test_insertion(&test_tree);

  test_deletion(&test_tree);

  test_insertion(&test_tree); 

  test_search(&test_tree); 

  test_invert_tree(&test_tree); 

  DEBUG_PRINT("\n===============\n", NULL);
  DEBUG_PRINT("|| Free Tree ||\n", NULL);
  DEBUG_PRINT("===============\n\n", NULL);

  free_tree(&test_tree);

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
  circ_queue.queue = queue; 

  return circ_queue; 
}

/**
 * Free the queue and set the struct to NULL 
 *
 * @param: circ_queue -> The queue to set to NULL which contains the queue to free 
 */

void free_queue(CircularQueue* circ_queue) {
  
  if (circ_queue == NULL) {
    printf("Queue should not be NULL when calling free queue\n\n"); 
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
  circ_queue->front += 1; 
  circ_queue->length -= 1; 

  if(circ_queue->length == 0) {
    circ_queue->front = 0;
    circ_queue->rear = -1; 
  }

  return dequeued_node; 

}



/**
 * Main method boi 
 */

int main() {
  run_tests(); 
  return 0; 
}
