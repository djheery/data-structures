#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

#define LEFT 'L' 
#define RIGHT 'R' 
#define RED 1
#define BLACK 0
#define QUEUE_CAPACITY 30 
#define DEBUG 

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

typedef struct Node Node; 

typedef struct Node {
  int data; 
  Node* parent; 
  Node* left; 
  Node* right; 
  int color; 
} Node;  


typedef struct {
  Node* root;
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
Node* insert_helper(RedBlackTree* tree, Node* root, int node_data); 
Node* rotation_helper(RedBlackTree* tree, Node* root); 
bool set_conflict_flag(RedBlackTree* tree, Node* current_node, char direction); 
void conflict_helper(RedBlackTree* tree, Node* root); 

bool delete(RedBlackTree* tree, int node_to_delete); 
Node* delete_helper(RedBlackTree* tree, Node* root, int node_to_delete);

bool search(RedBlackTree* tree, int node_data); 
bool search_helper(Node* root, int node_data); 

int size(Node* root, int current_sum); 

Node* rotate_left(Node* root); 
Node* rotate_right(Node* root); 

int height(Node* root); 
int get_max(int a, int b);

void invert_tree(RedBlackTree* tree); 
Node* invert_tree_helper(Node* root); 

// Traversal methods 

void print_tree_inorder(Node* root); 
void print_tree_postorder(Node* root); 
void print_tree_postorder(Node* root);

char get_node_color(Node* root); 

//  NOTE: Remove When done. This is just for a refresher on BST deletion
Node*  bst_delete_helper(RedBlackTree* tree, Node* root, int node_data); 
Node* bst_delete_min_successor(Node* root);

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
void test_insertion(RedBlackTree* test_tree, int node_data); 
void test_deletion(RedBlackTree* test_tree); 
void test_search(RedBlackTree* test_tree); 
void test_inversion(RedBlackTree* test_tree); 
void test_print_methods(RedBlackTree* test_tree);
void test_validate_tree(RedBlackTree* test_tree);

/**
 * ==========================
 * || Main Program Methods ||
 * ==========================
 */ 

int main() {
  run_tests();
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

  tree.root = NULL; 
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
  if(tree == NULL || tree->root == NULL) {
    return; 
  }

  CircularQueue queue = initialize_queue(); 
  enqueue(&queue, tree->root); 

  while(queue.size != 0) {
    Node* current = dequeue(&queue);  

    if(current->left != NULL) enqueue(&queue, current->left); 
    if(current->right != NULL) enqueue(&queue, current->right); 
    
    DEBUG_PRINT("Freeing Node: %d\n", current->data); 
    free(current); 
  }

  DEBUG_PRINT("\nList Feed Successfully\n\n", NULL); 

  tree->root = NULL; 
  tree->size = 0; 
  tree->rl = false; 
  tree->rr = false; 
  tree->ll = false; 
  tree->lr = false; 

}

/** 
 * The wrapper method for insertion into the binary tree
 *
 * @param: tree -> The tree to bbe inserted into 
 * @param: node_data -> the data of the node to be inserted
 */

void insert(RedBlackTree* tree, int node_data) {
  DEBUG_PRINT("Inserting Node %d\n\n", node_data); 
  tree->root = insert_helper(tree, tree->root, node_data); 
  tree->root->color = BLACK; 
  tree->size += 1; 
}

/** 
 * A recursive method for insertion into the RedBlackTree
 * This method is complex so I have bbroken the logic into three main helper funcitons they are: 
 *
 * set_conflict_flag(RBT* tree, Node* root, char direction)  
 * rotation_helper(RBT* tree, Node* root) 
 * conflict_helper(RBT* tree, Node* root)
 *
 * @param: tree -> the tree to insert into 
 * @param: root -> the current node 
 * @param: node_data -> the data for the new node
 *
 * @returns: It will eventually return the root 
 */

Node* insert_helper(RedBlackTree* tree, Node* root, int node_data) {
  bool red_red_conflict = false;  

  if(root == NULL) return initialize_node(node_data);
  
  if(node_data < root->data) {
    root->left = insert_helper(tree, root->left, node_data);  
    root->left->parent = root; 
    red_red_conflict = set_conflict_flag(tree, root, LEFT); 
  } else {
    root->right = insert_helper(tree, root->right, node_data); 
    root->right->parent = root; 
    red_red_conflict = set_conflict_flag(tree, root, RIGHT); 
  }
  

  root = rotation_helper(tree, root); 

  if(red_red_conflict) {
    // DEBUG_PRINT("%d->%d->%d ", root->parent->data, root->data, root->right->data);
    conflict_helper(tree, root); 
    red_red_conflict = false;  
  }

  
  return root; 
}

/** 
 * Set the conflict lag to check if there is a RED->RED conflict in the tree after insertion
 *
 * @param: tree -> The tree 
 * @param: current_node -> the current_node
 * @param: direciton -> a Char representation of the direction left or right 
 *
 * @returns: A boolean value indicating whether there is a RED->RED conflict or not
 */

bool set_conflict_flag(RedBlackTree* tree, Node* current_node, char direction) {
  if(direction != LEFT && direction != RIGHT) {
    DEBUG_PRINT("You've messed up you bozo \n", NULL);  
    DEBUG_PRINT("the direction must be either 'L' or 'R'. Your Tree may be messed up now\n\n", NULL);
    return false; 
  }

  Node* node_to_check = direction == LEFT ? current_node->left : current_node->right;  

  if(current_node == tree->root) return false; 

  return current_node->color == RED && node_to_check->color == RED; 
}

/**
 * A helper method for rotating the tree where necessary
 *
 * @param: tree -> The tree to perform the rotations on 
 * @param: root -> The current node and base for rotations
 * @returns: .....
 */

Node* rotation_helper(RedBlackTree* tree, Node* root) {

  if(tree->ll) {
    root = rotate_left(root); 
    root->color = BLACK; 
    root->left->color = RED; 
    tree->ll = false; 
  } else if (tree->rr) {
    root = rotate_right(root); 
    root->color = BLACK; 
    root->right->color = RED; 
    tree->rr = false;
  } else if (tree->rl) {
    root->right = rotate_right(root->right); 
    root->right->parent = root; 
    root = rotate_left(root); 
    root->color = BLACK; 
    root->left->color = RED; 
    tree->rl = false; 
  } else if (tree->lr) {
    root->left = rotate_left(root->left); 
    root->left->parent = root; 
    root = rotate_right(root); 
    root->color = BLACK; 
    root->right->color = RED;
    tree->lr = false; 
  }

  return root; 
}

/**
 * The implementation of a Left Rotation
 *
 * @param: root -> The base node to perform the rotation around 
 * @returns: The new node in place after rotation
 */ 

Node* rotate_left(Node* root) {
  Node* x = root->right; 
  Node* y = x->left; 
  x->left = root;  
  root->right = y;
  root->parent = x; 

  if(y != NULL) y->parent = x; 

  return x;  
}

/**
 * The implementation of the Right Rotation
 *
 * @param: root -> The base node to perform the rotation around 
 * @returns: The new node in place after rotation
 */

Node* rotate_right(Node* root) {
  Node* x = root->left; 
  Node* y = x->right; 
  x->right = root; 
  root->left = y; 
  root->parent = x; 

  if(y != NULL) y->parent = root; 

  return x;  
}

/** 
 * A helper for setting the rotation flags that need to be performed when there is a RED_RED conflict in the tree 
 *
 * This code is overly verbose but I am unsure how I can sort this I have tried to invert the outer nested if statement 
 * which has helped a little but there is still duplication
 *
 * @param: tree -> the tree currently performing the insertion or deletion on 
 * @param: root -> the current node 
 *
 */

void conflict_helper(RedBlackTree* tree, Node* root) {
  bool current_is_right_child = root->parent->right == root;  

  if(current_is_right_child) {
    bool uncle_left_is_black = root->parent->left == NULL || root->parent->left->color == BLACK;

    if(!uncle_left_is_black) {
      root->parent->left->color = BLACK; 
      root->color = BLACK; 

      if(root->parent != tree->root) root->parent->color = RED; 

      return; 
    } 

    if(root->left != NULL && root->left->color == RED) {
      tree->rl = true;  
    } else if(root->right != NULL && root->right->color == RED) {
      tree->ll = true; 
    }

    return;  
  }

  //  NOTE: We are dealing with the left child 
  
  bool uncle_right_is_black = root->parent->right == NULL || root->right->color == BLACK; 

  if(!uncle_right_is_black) {
    root->parent->right->color = BLACK;
    root->color = BLACK; 

    if(root->parent != tree->root) root->parent->color = RED; 

    return; 
  } 

  if(root->left != NULL && root->left->color == RED) {
    tree->rr = true; 
  } else if(root->right != NULL && root->right->color == RED) {
    tree->lr = true; 
  } 

}

/**
 * A wraper method for the delete function
 *
 * @param: tree -> The red black tree to delete from 
 * @param: node_data -> The data to be deleted 
 * @returns: A boolean value indicating whether a node was deleted or not 
 */

bool delete(RedBlackTree* tree, int node_data) {
  if(tree->size == 0 || tree->root == NULL) return false;

  //  NOTE: Maybe an unecerssary overhead but good for flagging to users if a node does not exist

  bool node_exists = search_helper(tree->root, node_data); 

  if(!node_exists) return false; 

  tree->root = delete_helper(tree, tree->root, node_data); 

  return true;
}

/** 
 * A recursive method for deleting a node from a RedBlackTree 
 *
 * @param: tree -> The tree to delete a node from
 * @param: root -> The current node
 * @param: node_data -> The data of a node to be deleted
 * @returns: Eventually will return the root of the tree 
 */

Node* delete_helper(RedBlackTree* tree, Node* root, int node_data) {
  if(root == NULL) return NULL

  int original_color = root->color;

  if(node_data < root->data) {
    root->left = delete_helper(tree, root->left, node_data);
    return root;
  }

  if(node_data > root->data) {
    root->right = delete_helper(tree, root->right, node_data); 
    return root;
  }

  if(root->left == NULL) {
    Node* temp = root->right;
    free(root);
    tree->size -= 1;
    return temp;
  }

  if(root->right == NULL) {
    Node* temp = root-left;
    free(root);
    tree->size -= 1;
    return temp;
  }

  Node* y = min_right_subtree(root);
  int y_color = y->color;
  
  
   

  return NULL; 
}

Node* min_right_subtree(Node* root) {
  Node* parent = root;
  Node* sucessor = root->right;

  while(successor->left != NULL) {
    parent = successor;
    sucessor = sucessor->left;
  }

  if(parent != root) {
    parent->left = successor->right; 
  } else {
    parent->right = successor->right;
  }

  return successor;
}

/**
 * !WARNING: DELETE THIS CODE WHEN A PROPER METHOD HAS BEEN MADE 
 *
 * BST DELETE METHODS FOR REFERENCE TO BE DELETED
 */

Node* bst_delete_helper(RedBlackTree* tree, Node* root, int node_data) {
  if(root == NULL) return NULL;  

  if(node_data < root->data) {
    root->left = bst_delete_helper(tree, root->left, node_data); 
    return root;
  }

  if(node_data > root->data) {
    root->right = bst_delete_helper(tree, root->right, node_data); 
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

  bst_delete_min_successor(root); 
  tree->size -= 1; 

  return root; 
}

Node* bst_delete_min_successor(Node* root) {
  Node* parent = root;  
  Node* successor = parent->right;  

  while(successor->left != NULL) {
    parent = successor; 
    successor = successor->left; 
  }

  if(parent != root) {
    parent->left = successor->right;  
  } else {
    parent->right = successor->right; 
  }

  root->data = successor->data; 
  free(successor); 

  return root; 
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
  if(tree->root == NULL || tree->size == 0) return false;  
  if(tree->root->data == data_to_search) return true; 
  if(tree->root->data != data_to_search && tree->size == 1) return false; 

  return search_helper(tree->root, data_to_search); 
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

/**
 * A method to clone the RedBlackTree 
 *
 * Only really used for the purpose of inversion and will not be available to a user 
 *
 * @param: tree -> The tree to clone 
 * @returns: A clone of the RedBlackTree passed as a parameter
 */

RedBlackTree clone(RedBlackTree* tree) {
  RedBlackTree test_tree = initialize_tree();   

  CircularQueue q = initialize_queue(); 
  enqueue(&q, tree->root); 

  while(q.size != 0) {
    Node* current = dequeue(&q);

    insert(&test_tree, current->data);

    if(current->left != NULL) enqueue(&q, current->left); 
    if(current->right != NULL) enqueue(&q, current->right); 
  }

  return test_tree; 
}

/** 
 * Invert the current red black tree 
 *
 * It performs this operation on a clone of the tree so that the integrity of the original tree is kept 
 * This is so that the original tree can continue to be used after a dummy inversion 
 * If I did not do this the implementation would become a lot more complex with flags for the direction of 
 * the tree and duplicate insertions, deletion and searching methods depending on the current inversion 
 * status of the tree 
 *
 * @param: tree -> the tree to clone and invert 
 */

void invert_tree(RedBlackTree* tree) {
  RedBlackTree test_tree = clone(tree); 
  invert_tree_helper(test_tree.root); 

  print_tree_inorder(test_tree.root);
  printf("\n\n"); 
  
  free_tree(&test_tree); 
  
}

/**
 * A recursive tree inversion method 
 *
 * @param: root -> the current node to invert the subtree of 
 * @returns: It will eventually return the root of the tree 
 */ 

Node* invert_tree_helper(Node* root) {
  if(root == NULL) return NULL; 

  Node* prevLeft = invert_tree_helper(root->left); 
  root->left = invert_tree_helper(root->right); 
  root->right = prevLeft; 

  return root; 
}

/** 
 * Inorder Traversal Print method 
 *
 * @param: root -> The current node
 */

void print_tree_inorder(Node* root) {
  if(root == NULL) return; 

  print_tree_inorder(root->left); 
  printf("[%d, %c]", root->data, get_node_color(root)); 
  print_tree_inorder(root->right); 
  
}

/** 
 * PostOrder Traversal Print method 
 *
 * @param: root -> The current node
 */

void print_tree_postorder(Node* root) {
  if(root == NULL) return; 

  print_tree_postorder(root->left); 
  print_tree_postorder(root->right); 
  printf("[%d, %c]", root->data, get_node_color(root)); 
}

/** 
 * PreOrder Traversal Print method 
 *
 * @param: root -> The current node
 */

void print_tree_preorder(Node* root) {
  if(root == NULL) return; 

  printf("[%d, %c]", root->data, get_node_color(root)); 
  print_tree_preorder(root->left); 
  print_tree_preorder(root->right);
}

char get_node_color(Node* root) {
  return root->color == RED ? 'R' : 'B';  
}

void validate_red_black_tree(Node* root) {
 
}

/**
 * Get the minimum node in the tree 
 *
 * @param: root -> the current node being recursed through until eventually the min 
 * @returns: The minimum value node in the tree
 */

Node* get_min_node(Node* root) {

  if(root->left == NULL) return root; 

  return get_min_node(root->left); 

}

/**
 * Get the maximum node in the tree 
 *
 * @param: root -> The current node being recursed through until eventually the node with the max value
 * @returns: The node with the max value in the tree 
 */

Node* get_max_node(Node* root) {
  if(root->right == NULL) return root; 

  return get_max_node(root->right);
}

/** 
 * Get the height of the tree 
 *
 * @param: root -> The current node being recursed through 
 * @returns: The max value of either the left or right subtree
 */

int height(Node* root) {
  if(root == NULL) return 0;  

  return get_max(1 + height(root->left), 1 + height(root->right));
}

/**
 * Get the max of two values (specifically for the height method above 
 *
 * @param: { a, b } -> The integers to compare
 * @returns: The larger of either a or b
 */

int get_max(int a, int b) {
  return a > b ? a : b; 
}

/** 
 * A helper function for validating the RedBlackTree and checking there are no RED-RED conflicts
 *
 * @param: root -> The current node to check
 * @param: prev_color -> The color of the previous node
 * @returns: A boolean value indicating if there is a RED-RED conflict
 */

bool validate_has_red_conflict(Node* root, int prev_color) {
  bool red_conflict = ((root && root->color == RED) && prev_color == RED);  
  return red_conflict; 
}


/**
 * =============================
 * || Program Tester Methods  ||
 * =============================
 */

void run_tests() {
  RedBlackTree test_tree = initialize_tree();

  populate_tree(&test_tree);

  free_tree(&test_tree);
}

void populate_tree(RedBlackTree* test_tree) {
  test_insertion(test_tree, 50);  
  test_insertion(test_tree, 20); 
  test_insertion(test_tree, 35); 
  test_insertion(test_tree, 75); 
  test_insertion(test_tree, 62); 
  test_insertion(test_tree, 98); 
  test_insertion(test_tree, 10); 
  test_insertion(test_tree, 66);
  test_insertion(test_tree, 1); 
}

void test_insertion(RedBlackTree* test_tree, int node_data) {
  insert(test_tree, node_data); 
  print_tree_inorder(test_tree->root);
  printf("\n\nRoot: %d\n\n", test_tree->root->data);  
}

void test_deletion(RedBlackTree* test_tree) {
  
}

void test_search(RedBlackTree* test_tree) {
  
}

void test_inversion(RedBlackTree* test_tree) {
  
}

void test_print_methods(RedBlackTree* test_tree) {
  
}

void test_validate_tree(RedBlackTree* test_tree) {
  
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
