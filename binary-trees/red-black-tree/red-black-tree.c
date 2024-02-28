#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

/**
 * ===================================
 * || Red Black Tree Implementation ||
 * ===================================
 *
 * This is my implementation of a Red Black tree
 *
 * The project structure is as follows: 
 *
 * - Begins with some definitions and macros
 * - Setup the data structures
 * - Method delarations 
 * - Red Black Tree method Implementations
 * - Tests 
 * - Utility Data Structure implementations 
 *
 *  WARNING: This is still a work in progress
 *  NOTE: I seem to have unwitingly used two separate ways of implementing a Red Black Tree as can be seen in the differences between Insert and Delete 
 *  NOTE: Insert relies on recursion and delete is a mix of Recursion and procedural programming - This is because when implementing delete I started to read "Introduction to Algorithms" (Corman, T. et al)
 *  NOTE: Red black trees are confusing to those new to this, so I have tried to make this code as verbose as possible.
 */

#define LEFT 'L' 
#define RIGHT 'R' 
#define RED 1
#define BLACK 0
#define QUEUE_CAPACITY 30 
#define DEBUG 
#define INSERT 'I'
#define DELETE 'D'

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
  Node* TNIL; 
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
Node* initialize_node(int node_data, RedBlackTree* tree); 
void free_tree(RedBlackTree* tree); 

// Util Methods 

void insert(RedBlackTree* tree, int node_data); 
Node* insert_helper(RedBlackTree* tree, Node* root, int node_data); 
Node* rotation_helper(RedBlackTree* tree, Node* root); 
bool set_conflict_flag(RedBlackTree* tree, Node* current_node, char direction, char caller); 
void conflict_helper(RedBlackTree* tree, Node* root); 

bool delete(RedBlackTree* tree, int node_to_delete); 
void delete_helper(RedBlackTree* tree, Node* root, Node* to_delete);
void delete_fixup(RedBlackTree* tree, Node* x); 
Node* transplant(RedBlackTree* tree, Node* root, Node* child);
Node* min_successor(Node* root);

bool search(RedBlackTree* tree, int node_data); 
bool search_helper(Node* root, int node_data); 
Node* get_node(Node* root, int node_data); 

int size(Node* root, int current_sum); 

Node* rotate_left(Node* root, RedBlackTree* tree); 
Node* rotate_right(Node* root, RedBlackTree* tree); 

int height(Node* root); 
int get_max(int a, int b);

void invert_tree(RedBlackTree* tree); 
Node* invert_tree_helper(Node* root); 

// Traversal methods 

void print_tree_inorder(RedBlackTree* tree, Node* root); 
void print_tree_postorder(RedBlackTree* tree, Node* root); 
void print_tree_preorder(RedBlackTree* tree, Node* root);

char get_node_color(Node* root); 

//  NOTE: Remove When done. This is just for a refresher on BST deletion
Node*  bst_delete_helper(RedBlackTree* tree, Node* root, int node_data); 
Node* bst_delete_y(Node* root);

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

  Node* TNIL = (Node*) malloc(sizeof(Node)); 
  
  if (TNIL == NULL) {
    DEBUG_PRINT("Error initializing TNIL\n", NULL); 
    exit(EXIT_FAILURE);
  }

  TNIL->color = BLACK; 
  tree.TNIL = TNIL;

  return tree;  
}

/** 
 * Initialize a Node (pointer) for the RedBlackTree
 *
 * @param: node_data -> The data to insert into the node 
 * @returns: A pointer to the node on the heap
 */

Node* initialize_node(int node_data, RedBlackTree* tree) {
  Node* node = (Node*) malloc(sizeof(Node));  

  if(node == NULL) {
    DEBUG_PRINT("Error initializing Node: %d\n", node_data); 
    DEBUG_PRINT("Exiting Program\n\n", NULL); 
    exit(EXIT_FAILURE); 
  }

  node->data = node_data; 
  node->parent = NULL; 
  node->left = tree->TNIL; 
  node->right = tree->TNIL; 
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

    if(current->left != tree->TNIL) enqueue(&queue, current->left); 
    if(current->right != tree->TNIL) enqueue(&queue, current->right); 
    
    DEBUG_PRINT("Freeing Node: %d\n", current->data); 
    free(current); 
  }

  free(tree->TNIL); 

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

  if(root == NULL || root == tree->TNIL) return initialize_node(node_data, tree);
  
  if(node_data < root->data) {
    root->left = insert_helper(tree, root->left, node_data);  
    root->left->parent = root; 
    red_red_conflict = set_conflict_flag(tree, root, LEFT, INSERT); 
  } else {
    root->right = insert_helper(tree, root->right, node_data); 
    root->right->parent = root; 
    red_red_conflict = set_conflict_flag(tree, root, RIGHT, INSERT); 
  }
  

  root = rotation_helper(tree, root); 

  if(red_red_conflict) {
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

bool set_conflict_flag(RedBlackTree* tree, Node* current_node, char direction, char caller) {
  if(direction != LEFT && direction != RIGHT) {
    DEBUG_PRINT("You've messed up you bozo \n", NULL);  
    DEBUG_PRINT("the direction must be either 'L' or 'R'. Your Tree may be messed up now\n\n", NULL);
    return false; 
  }

  Node* node_to_check = direction == LEFT ? current_node->left : current_node->right;  
  int color_to_check = caller == INSERT ? RED : BLACK;

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
    root = rotate_left(root, tree); 
    root->color = BLACK; 
    root->left->color = RED; 
    tree->ll = false; 
  } else if (tree->rr) {
    root = rotate_right(root, tree); 
    root->color = BLACK; 
    root->right->color = RED; 
    tree->rr = false;
  } else if (tree->rl) {
    root->right = rotate_right(root->right, tree); 
    root->right->parent = root; 
    root = rotate_left(root, tree); 
    root->color = BLACK; 
    root->left->color = RED; 
    tree->rl = false; 
  } else if (tree->lr) {
    root->left = rotate_left(root->left, tree); 
    root->left->parent = root; 
    root = rotate_right(root, tree); 
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

Node* rotate_left(Node* root, RedBlackTree* tree) {
  Node* x = root->right; 
  Node* y = x->left; 
  x->left = root;  
  root->right = y;
  root->parent = x; 

  if(y != tree->TNIL) y->parent = x; 

  return x;  
}


/**
 * The implementation of the Right Rotation
 *
 * @param: root -> The base node to perform the rotation around 
 * @returns: The new node in place after rotation
 */

Node* rotate_right(Node* root, RedBlackTree* tree) {
  Node* x = root->left; 
  Node* y = x->right; 
  x->right = root; 
  root->left = y; 
  root->parent = x; 

  if(y != NULL) y->parent = root; 

  return x;  
}

void rotate_left_del(RedBlackTree* tree, Node* root) {
  Node* y = root->right; 
  root->right = y->left;

  if (y->left != tree->TNIL) {
    y->left->parent = y; 
  }

  y->parent = root->parent; 

  if (root->parent == NULL) {
    tree->root = y;
  } else if ( root == root->parent->left) {
    root->parent->left = y;
  } else  {
    root->parent->right = y; 
  }

  y->left = root; 
  root->parent = y; 
}

void rotate_right_del(RedBlackTree* tree, Node* root) {
  Node* y = root->left; 
  root->left = y->right; 

  y->parent = root->parent; 

  if (root->parent == NULL) {
    tree->root = y; 
  } else if (root == root->parent->left) {
    root->parent->left = y; 
  } else {
    root->parent->right = y; 
  }

  root->parent = y;
  y->right = root;
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
    bool uncle_left_is_black = root->parent->left == tree->TNIL || root->parent->left->color == BLACK;

    if(!uncle_left_is_black) {
      root->parent->left->color = BLACK; 
      root->color = BLACK; 

      if(root->parent != tree->root) root->parent->color = RED; 

      return; 
    } 

    if(root->left != tree->TNIL && root->left->color == RED) {
      tree->rl = true;  
    } else if(root->right != NULL && root->right->color == RED) {
      tree->ll = true; 
    }

    return;  
  }

  //  NOTE: We are dealing with the left child 
  
  bool uncle_right_is_black = root->parent->right == tree->TNIL || root->right->color == BLACK; 

  if(!uncle_right_is_black) {
    root->parent->right->color = BLACK;
    root->color = BLACK; 

    if(root->parent != tree->root) root->parent->color = RED; 

    return; 
  } 

  if(root->left != tree->TNIL && root->left->color == RED) {
    tree->rr = true; 
  } else if(root->right != tree->TNIL && root->right->color == RED) {
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

  Node* to_delete = get_node(tree->root, node_data); 

  if(to_delete == NULL) return false; 

  delete_helper(tree, tree->root, to_delete); 

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

void delete_helper(RedBlackTree* tree, Node* root, Node* to_delete) {

  Node* x;
  Node* y = to_delete; 
  int y_color = y->color;

  if (to_delete->left == tree->TNIL) {
    x = to_delete->right;  
    transplant(tree, to_delete, to_delete->left);
  } else if (to_delete->right == tree->TNIL) {
    x = to_delete->left; 
    transplant(tree, to_delete, to_delete->right); 
  } else {

    y = min_successor(to_delete);
    y_color = y->color; 
    x = y->right; 

    if (y != to_delete->right) {
      transplant(tree, y, y->right); 
      y->right = to_delete->right; 
      y->right->parent = y; 
    } else {
      x->parent = y;
    } 

    transplant(tree, to_delete, y); 
    y->left = to_delete->left; 
    y->left->parent = y; 
    y->color = to_delete->color; 
  }

  DEBUG_PRINT("GOTEM %d\n", to_delete->data);

  if (y_color == BLACK) delete_fixup(tree, x);

  free(to_delete); 
  tree->size -= 1; 

}

/**
 * Transplant root with child to restucture the tree after deletion 
 *
 * @param: tree -> The tree to perform the traspant within
 * @param: root -> The node to be transplanted
 * @param: child -> The child of the root
 * @returns: The child that has been transplated
 */

Node* transplant(RedBlackTree* tree, Node* root, Node* child) {

  // Is root the actual tree root, could also be written as root == tree->root
  if(root->parent == NULL) {
    tree->root = child; 
  } else if (root->parent->left == root) {
    root->parent->left = child; 
  } else {
    root->parent->right = child; 
  }

  child->parent = root->parent; 

  return child; 
}

/** 
 * A utility method to check if a given node is black from which the user can infer the color of the node if its not black (it's red you dummy) ; 
 *
 * @param: x -> The node with a color to check 
 * @returns: A boolean value representing whether the given node is Black or not
 */


bool is_black(Node* x, RedBlackTree* tree) {
  return x == NULL || x->color == BLACK || x == tree->TNIL; 
}

/**
 * A method for fixing the structure and color of the tree to keep to the rules of a RedBlackTree
 *
 * @param: tree -> The red black tree to fix the structure of
 * @param: x -> The child node of y in the delete method (see this method and the README for more information)
 */

void delete_fixup(RedBlackTree* tree, Node* x) {

  while (is_black(x, tree) && x != tree->root) {

    Node* sibling = x->parent->left == x ? x->parent->right : x->parent->left; 
    bool sibling_is_red = is_black(sibling, tree) == false; 


    if (x == x->parent->left) {

      if(sibling_is_red) {
        sibling->color = BLACK; 
        x->color = RED;
        rotate_left_del(tree, x->parent); 
        sibling = x->parent->right; 
      }

      if(is_black(sibling->left, tree) && is_black(sibling->right, tree)) {
        sibling->color = RED; 
        x = x->parent; 
        continue; 
      }

      if(is_black(sibling->right, tree)) {
        sibling->left->color = BLACK; 
        sibling->color = RED; 
        rotate_right_del(tree, sibling); 
        sibling = x->parent->right; 
      }

      sibling->color = x->parent->color;
      x->parent->color = BLACK;
      sibling->right->color = BLACK;
      rotate_left_del(tree, x->parent); 
      x = tree->root; 
      continue;
    }

    if(sibling_is_red) {
      sibling->color = BLACK; 
      x->color = RED; 
      rotate_right_del(tree, x->parent); 
      sibling = x->parent->left; 
    }

    if(is_black(sibling->left, tree) && is_black(sibling->right, tree)) {
      sibling->color = RED;
      x = x->parent;
      continue; 
    }

    if(is_black(sibling->left, tree)) {
      sibling->right->color = BLACK;
      sibling->color = RED;
      rotate_left_del(tree, sibling);
      sibling = x->parent->left; 
    }

    sibling->color = x->parent->color;
    x->parent->color = BLACK;
    sibling->left->color = BLACK;
    rotate_left_del(tree, x->parent); 
    x = tree->root; 
  }

  x->color = BLACK; 
}

/**
 * Get the mininimum successor 
 *
 * @param: root -> The current node 
 * @returns: An array of [Successor, successor_right_chid]
 */


Node* min_successor(Node* root) {
  Node* parent = root;
  Node* successor = root->right;

  while(successor->left != NULL) {
    parent = successor;
    successor = successor->left;
  }

  return successor;
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
 * A search method that returns the actual node if it exists
 *
 * @param: root -> The current node 
 * @param: node_data -> The data of the node we are looking for 
 * @returns: NULL or a pointer to the node that was found (This should be checked in the caller) 
 */

Node* get_node(Node* root, int node_data) {
  if (root == NULL) return NULL; 
  if (root->data == node_data) return root; 

  Node* n; 

  if (node_data < root->data) n = get_node(root->left, node_data);
  if (node_data > root->data) n = get_node(root->right, node_data); 

  return n;
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

  print_tree_inorder(tree, test_tree.root);
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

void print_tree_inorder(RedBlackTree* tree, Node* root) {
  if(root == tree->TNIL) return; 

  print_tree_inorder(tree, root->left); 
  printf("[%d, %c]", root->data, get_node_color(root)); 
  print_tree_inorder(tree, root->right); 
  
}

/** 
 * PostOrder Traversal Print method 
 *
 * @param: root -> The current node
 */

void print_tree_postorder(RedBlackTree* tree, Node* root) {
  if(root == tree->TNIL) return; 

  print_tree_postorder(tree, root->left); 
  print_tree_postorder(tree, root->right); 
  printf("[%d, %c]", root->data, get_node_color(root)); 
}

/** 
 * PreOrder Traversal Print method 
 *
 * @param: root -> The current node
 */

void print_tree_preorder(RedBlackTree* tree, Node* root) {
  if(root == tree->TNIL) return; 

  printf("[%d, %c]", root->data, get_node_color(root)); 
  print_tree_preorder(tree, root->left); 
  print_tree_preorder(tree, root->right);
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

  test_deletion(&test_tree);

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
  print_tree_inorder(test_tree, test_tree->root);
  printf("\n\nRoot: %d\n\n", test_tree->root->data);  
}

void test_deletion(RedBlackTree* test_tree) {
  delete(test_tree, 68); 
  print_tree_inorder(test_tree, test_tree->root);
  printf("\n\n"); 
  delete(test_tree, 50); 
  print_tree_inorder(test_tree, test_tree->root);
  printf("\n\n");
  delete(test_tree, 62); 
  print_tree_inorder(test_tree, test_tree->root);
  printf("\n\n");
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
