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
void confilict_helper(RedBlackTree* tree, Node* root); 

void delete(Node* root, int node_to_delete); 

bool search(RedBlackTree* tree, int node_data); 
bool search_helper(Node* root, int node_data); 

int size(Node* root, int current_sum); 

Node* rotate_left(Node* root); 
Node* rotate_right(Node* root); 

int height(Node* root); 
int get_max(int a, int b);

void invert_tree(RedBlackTree* tree); 
Node* invert_tree_helper(Node* root); 

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
    confilict_helper(tree, root); 
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
    DEBUG_PRINT("You've messed up you bozo -> the direction must be either 'L' or 'R'. Your Tree may be messed up now\n\n", NULL);  
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

    tree->rl = false; 
  } else if (tree->lr) {

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

void confilict_helper(RedBlackTree* tree, Node* root) {
  bool current_is_right_child = root->parent->right == root;  

  if(current_is_right_child) {
    bool uncle_left_is_black = root->parent->left == NULL || root->parent->left->color == BLACK;

    if(!uncle_left_is_black) {
      root->parent->left->color = BLACK; 
      root->color = BLACK; 

      if(root->parent == tree->root) root->parent->color = RED; 

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
  
  bool uncle_right_is_black = root->parent->right != NULL || root->right->color == BLACK; 

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

  // TODO: Print the inverted Tree
  
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
  printf("%d ", root->data); 
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
  printf("%d ", root->data);
}

/** 
 * PreOrder Traversal Print method 
 *
 * @param: root -> The current node
 */

void print_tree_preorder(Node* root) {
  if(root == NULL) return; 

  printf("%d ", root->data); 
  print_tree_preorder(root->left); 
  print_tree_preorder(root->right);
}


/**
 * =============================
 * || Program Tester Methods  ||
 * =============================
 */

void run_tests() {
  
}

void populate_tree(RedBlackTree* test_tree) {
  
}

void test_insertion(RedBlackTree* test_tree) {
  
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
