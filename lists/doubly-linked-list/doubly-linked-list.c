/**
 * *-----------------------------------*
 * * Doubly Linked List Data Structure *
 * *-----------------------------------*
 *
 * This is my implementation of a doubly linked list Data structure 
 * The implementation follows the structure of the the Singularly Linked List Data Structure included in the lists project folder 
 *
 * Methods implements: 
 *
 * - Reverse 
 * - Insert Node 
 * - Remove Node 
 * - Tail 
 * - Head 
 * - Insert at head 
 * - Insert at Tail 
 * - Insert at position
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define RUN_TESTS true 
#define DEBUG 
#define LIST_HEAD_INDEX 1 

#ifdef DEBUG 
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__); 
#else 
#define DEBUG_PRINT(fmt, ...) 
#endif


typedef struct {
  void* next; 
  void* prev; 
  int data; 
} Node; 

typedef struct {
  Node* head; 
  Node* tail; 
  int size; 
} DoublyLinkedList; 

typedef struct {
  Node* current; 
} Iterator; 

// List utility Methods

DoublyLinkedList initialize_list(); 
Node* intialize_node(); 
void free_list(DoublyLinkedList* list); 
Node* head(DoublyLinkedList* list); 
Node* tail(DoublyLinkedList* list); 
bool validate_insertion(DoublyLinkedList* list, int position); 
bool insert_node(DoublyLinkedList* list, int node_data, int position); 
bool insert_head(DoublyLinkedList* list, int node_data, Node* new_node); 
bool insert_tail(DoublyLinkedList* list, int node_data, Node* new_node); 
int remove_node(DoublyLinkedList* list, int node_data); 
int remove_head(DoublyLinkedList* list); 
int remove_tail(DoublyLinkedList* list); 
bool search(DoublyLinkedList* list, int data_to_search); 
void reverse(DoublyLinkedList* list); 
void traverse_reverse(DoublyLinkedList* list); 
void to_string(DoublyLinkedList* list); 

// Iterator Methods 

Iterator to_iter(DoublyLinkedList* list); 
Node* current(Iterator* iter); 
Node* next(Iterator* iter); 
bool has_next(Iterator* iter); 
bool has_current(Iterator* iter); 
void iter_next(Iterator* iter); 

// CLI/UI Methods 

void cli_head(DoublyLinkedList* list); 
void cli_tail(DoublyLinkedList* list); 
void cli_insert_at_position(DoublyLinkedList* list);
void cli_insert_at_head(DoublyLinkedList* list); 
void cli_insert_at_tail(DoublyLinkedList* list); 
void cli_remove_node(DoublyLinkedList* list); 
void cli_remove_head(DoublyLinkedList* list); 
void cli_remove_tail(DoublyLinkedList* list); 
void cli_search(DoublyLinkedList* list); 
void cli_reverse(DoublyLinkedList* list); 

// Program Methods

void print_menu(); 
void program_loop(); 
int get_user_input(char text_prompt[]); 
bool validate_user_input(char* p); 


// Tester methods 

void run_tests(); 
void populate_list(DoublyLinkedList* test_list); 
void test_head_insertion(DoublyLinkedList* test_list, int node_data); 
void test_tail_insertion(DoublyLinkedList* test_list, int node_data); 
void test_position_insertion(DoublyLinkedList* test_list, int node_data, int position); 
void test_node_removal(DoublyLinkedList* test_list, int node_data); 
void test_position_removal(DoublyLinkedList* test_list, int node_data, int position); 
void test_head_removal(DoublyLinkedList* test_list); 
void test_tail_removal(DoublyLinkedList* test_list); 
void test_reverse(DoublyLinkedList* test_list); 
void test_traverse_reverse(DoublyLinkedList* test_list); 
void test_search(DoublyLinkedList* test_list, int node_to_search); 


// ==========================
// || Main Program Methods ||
// ==========================

int main() {
  program_loop(); 
  return 0; 
}

void program_loop() {
  printf("===================================\n"); 
  printf("|| Doubly Linked List Playground ||\n"); 
  printf("===================================\n\n"); 

  if(RUN_TESTS) {
    run_tests(); 
  }
}

void print_menu() {
  
}

int get_user_input(char text_prompt[]) {
  const int max_retries = 3; 
  int current_retries = 0; 
  int user_input = -1; 

  while(current_retries < max_retries) {
    char buffer[10];
    printf("> %s ", text_prompt);  
    fgets(buffer, sizeof(buffer), stdin);
    printf("\n"); 

    buffer[strcspn(buffer, "\n")] = 0; 

    char* p = buffer; 

    bool is_valid = validate_user_input(p);

    if(is_valid) {
      user_input = atoi(buffer); 
      break; 
    }

    current_retries += 1; 

    if(current_retries == max_retries) {
      printf("Whoops, you have entered incorrectly too many times\n"); 
      printf("Returning to the menu\n\n"); 
      break; 
    }

    // This means they are still within range
    printf("Whoops, incorrect user input\n"); 
    printf("Please try again... remembber to enter an integer\n\n"); 
  }

  return user_input; 
}

/**
 * A very basic method for validating the users input (just check it's an integer 
 *
 * @param: *p - A pointer to the buffer created for reading the user user_input
 * @returns: True of False depending if the input is valid given the small criteria
 */

bool validate_user_input(char* p) {
  while(*p) {
    if(!isdigit((unsigned char)* p)) {
      return false; 
    }

    p++;
  }

  return true; 
}

// =====================
// || Utility Methods ||
// =====================

/**
 * Convert the list to string 
 *
 * @param: The list to print
 */

void to_string(DoublyLinkedList* list) {
  if(list->size == 0) {
    printf("Your list is currently empty\n"); 
    return; 
  }

  if(list->head == NULL || list->tail == NULL) {
    printf("ERROR: The list size is empty and the tail or head is null please check the logic\n"); 
    printf("The program will exit...\n");
    exit(EXIT_FAILURE); 
  }

  Iterator iter = to_iter(list); 

  while(has_current(&iter)) {
    printf("%d <=> ", current(&iter)->data);  
    iter_next(&iter);
  }

  printf(" END_OF_LIST\n\n");
}

/**
 * Initialize the list 
 *
 * @returns: An instance of a DoublyLinked List
 */

DoublyLinkedList initialize_list() {
  DoublyLinkedList list; 
  list.head = NULL; 
  list.tail = NULL; 
  list.size = 0; 
  return list; 
}

/**
 * Initialize a Linked List Node
 *
 * @param: data - The data to be stored inside the given node
 * @returns: A node with NULL pointers to the next and prev (to be populated on insertion)  
 */

Node* initialize_node(int data) {
  Node* n = (Node*) malloc(sizeof(Node)); 

  if(n == NULL) {
    printf("Error whilst allocating the memory for the node\n\n"); 
    exit(EXIT_FAILURE); 
  }

  n->data = data; 
  n->prev = NULL; 
  n->next = NULL; 

  return n; 
}

/**
 * Free the list 
 *
 * @param: list - The list to free all the nodes within
 */

void free_list(DoublyLinkedList* list) {
  Iterator iter = to_iter(list); 

  while(has_current(&iter)) {
    Node* current_node = current(&iter); 
    iter_next(&iter);
    DEBUG_PRINT("Freeing Node: %d\n", current_node->data);
    free(current_node); 
  }

  DEBUG_PRINT("\nLIST_FREED_SUCCESSFULLY\n\n", NULL); 

  list->size = 0; 
  list->head = NULL; 
  list->tail = NULL; 
}

/**
 * Get the head of the list
 *
 * @returns: The head of the list if it exists, NULL if not
 */

Node* head(DoublyLinkedList* list) {
  if(list->head == NULL || list->size == 0) {
    return NULL; 
  }

  return list->head; 
}


/**
 * Get the tail of the list
 *
 * @returns: The tail of the list if it exists, NULL if not
 */

Node* tail(DoublyLinkedList* list) {
  if(list->tail == NULL || list->size == 0) {
    return NULL; 
  }

  return list->tail; 
}

/**
 * Insert a node in the list at a given position. 
 * This method is reusable for inserting at the head of the list and the tail of the list
 *
 * @param: list - The list to insert into 
 * @param: node_data - The data to be associated with the inserted node 
 * @param: position - The position to insert into
 *
 * @returns: True or false depending on whether there has been a successful insertion or not
 */

bool insert_node(DoublyLinkedList* list, int node_data, int position) {

  Node* new_node = initialize_node(node_data);

  if(new_node == NULL) {
    printf("Something went wrong initializing the new node, the program will exit\n\n"); 
    exit(EXIT_FAILURE);
  }

  if(position == LIST_HEAD_INDEX) {
    bool has_inserted = insert_head(list, node_data, new_node);  
    return has_inserted; 
  }

  if(position == (list->size + 1)) {
    bool has_inserted = insert_tail(list, node_data, new_node); 
    return has_inserted; 
  }

  Iterator iter = to_iter(list);
  int count = 1; 
  Node* current_node = current(&iter);

  while((count < (position - 1))) { 
    iter_next(&iter);
    current_node = current(&iter);
    if(current_node == NULL) {
      DEBUG_PRINT("!!DBG!! Current Node is NULL within the loop before expected\n\n", NULL); 
      free(new_node); 
      return false; 
    }
    count++;
  }

  // DEBUG_PRINT("!!DBG!! COUNT: %d, POS: %d, NODE_DATA: %d, LIST_SIZE: %d, CURRENT_NODE: %d\n", count, position, node_data, list->size, current_node->data); 

  if(count != position - 1) {
    DEBUG_PRINT("!!DBG ERROR!!", NULL);
    DEBUG_PRINT("!!DBG!! There are not enough elements to insert another element. \n", NULL); 
    DEBUG_PRINT("!!DBG!! This should not be called as this condition should be checked prior to reaching this point\n\n", NULL); 
    return false; 
  }
 
  Node* new_next = current_node->next; 
  current_node->next = new_node; 
  new_node->prev = current_node; 
  new_node->next = new_next; 
  new_next->prev = new_node; 
  list->size += 1; 

  if(position == list->size) {
    list->tail = new_node; 
    new_node->next = NULL; 
  }

  return true;  

}

/**
 * Insert a node in the head position. 
 *
 * @param: list - The list to insert into 
 * @param: node_data - The data to be associated with the inserted node 
 *
 * @returns: True or false depending on whether there has been a successful insertion or not
 */


bool insert_head(DoublyLinkedList* list, int node_data, Node* new_node) {

  if(list->size == 0 || list->head == NULL) {
    list->head = new_node; 
    list->tail = new_node; 
    list->size += 1; 
    return true;  
  }

  if(list->size == 1) {
    Node* prev_head = list->head; 
    new_node->next = prev_head; 
    prev_head->prev = new_node; 
    prev_head->next = NULL; 
    list->head = new_node;     
    list->tail = prev_head; 
    list->size += 1;

    return true; 
  }

  Node* prev_head = list->head; 
  new_node->next = prev_head; 
  prev_head->prev = new_node; 
  list->head = new_node; 
  list->size += 1; 

  return true;  

}

/**
 * Insert a node in the tail position. 
 *
 * @param: list - The list to insert into 
 * @param: node_data - The data to be associated with the inserted node 
 *
 * @returns: True or false depending on whether there has been a successful insertion or not
 */


bool insert_tail(DoublyLinkedList* list, int node_data, Node* new_node) {

  new_node->prev = list->tail;
  list->tail->next = new_node; 
  list->tail = new_node; 
  list->size += 1;

  return true;  

}

/**
 *  TODO: ADD GUARD CHECKS
 *
 * Remove the first instance of a node given specific node data 
 *
 * @param: list - The list to remove the node within
 * @param: node_data - The data to remove if it exists within the list
 *
 * @returns: The node data removed or -1 if the node was not found
 */

int remove_node(DoublyLinkedList* list, int node_data) {
  int removed_node_data = -1; 
  Iterator iter = to_iter(list); 
  Node* current_node;

  while(has_current(&iter)) {
    current_node = current(&iter);  

    if(current_node->data == node_data) {
      removed_node_data = current_node->data; 
      Node* prev_node = current_node->prev; 
      Node* next_node = current_node->next; 
      prev_node->next = next_node; 
      next_node->prev = prev_node; 

      free(current_node); 
      break; 
    }

    iter_next(&iter); 
  }
 
  return removed_node_data; 
}

/**
 * Remove the head of the list
 *
 * @param: list - the list to remove the head of
 * @returns: the data of the removed node
 */

int remove_head(DoublyLinkedList* list) {

  if(list->size == 0 || list->head == NULL) {
    return -1; 
  }

  Node* current_head = list->head; 
  Node* new_head = list->head->next; 
  int removed_node_data = current_head->data; 

  new_head->prev = NULL; 
  list->head = new_head; 
  list->size -= 1; 

  if(list->size == 0) {
    list->head = NULL; 
    list->tail = NULL; 
  }

  free(current_head); 

  return removed_node_data;  
}

/**
 * Remove the tail of the list 
 *
 * @param: list - The list to remove the tail of 
 * @returns: The data of the removed node
 */

int remove_tail(DoublyLinkedList* list) {

  if(list->size == 0 || list->tail == NULL) {
    return -1; 
  }

  Node* current_tail = list->tail;  
  Node* new_tail = current_tail->prev; 
  int removed_node_data = current_tail->data; 

  new_tail->next = NULL; 
  list->tail = new_tail; 
  list->size -= 1; 

  if(list->size == 0) {
    list->head = NULL; 
    list->tail = NULL; 
  }

  free(current_tail);

  return removed_node_data; 
}

/**
 * Search for the first instance of a node in the list given the node data 
 *
 * @param: list - The list to search within 
 * @param: data_to_search - The data to search for within the list 
 *
 * @returns: True or False depending on whether the node data is found within the list
 */

bool search(DoublyLinkedList* list, int data_to_search) {

  if(list->size == 0 || list->head == NULL) {
    return false; 
  }

  bool node_exists = false;  

  Iterator iter = to_iter(list); 

  while(has_current(&iter)) {
    Node* current_node = current(&iter); 

    if(current_node->data == data_to_search) {
      node_exists = true; 
      break; 
    }

    iter_next(&iter);
  }

  return node_exists; 
}

/**
 * Reverse the list 
 * This affects the actual list
 *
 * @param: list - The list to reverse
 */

void reverse(DoublyLinkedList* list) {
  if(list->size == 0) {
    printf("The list is currently empty, thus a reverse cannot be performed\n\n"); 
    return; 
  }

  Node* current_node = list->head; 
  Node* next_node = NULL; 
  Node* prev_node = NULL; 

  while(current_node != NULL) {
    next_node = current_node->next;  
    current_node->next = prev_node;
    current_node->prev = next_node; 
    prev_node = current_node; 
    current_node = next_node; 
  }

  Node* prev_head = list->head; 
  list->head = list->tail; 
  list->tail = prev_head; 

  to_string(list); 
}

/**
 * Traverses the list in reverse
 *
 * @param: list - The list 
 */

void traverse_reverse(DoublyLinkedList* list) {
  if(list->size == 0) {
    printf("The list is currently empty, thus a reverse cannot be performed\n\n"); 
    return; 
  }

  Node* current_node = list->tail; 

  while(current_node != NULL) {
    printf("%d <=> ", current_node->data);  
    current_node = current_node->prev; 
  }

  printf(" START_OF_LIST\n\n");
}


// ======================
// || Iterator Methods ||
// ======================

/**
 *  TODO: ADD A PATTERN TO CHECK IF YOU WANT TO ITERATE FORWARDS OR BACKWARDS
 * Create an iterator for the list 
 *
 * @param: list - An instance of a Doubly Linked List 
 * @returns: A new instance of an iterator for the given list
 */

Iterator to_iter(DoublyLinkedList* list) {
  if(list->head == NULL || list->size == 0) {
    printf("Iterator cannot be made as the list size is 0\n\n"); 
  }

  Iterator iter; 
  iter.current = list->head; 
  return iter; 
}

/**
 * Return the current target of the iterator 
 *
 * @param: iter - An iterator for a given list
 * @returns: The Current target of the iterator within the List
 */

Node* current(Iterator* iter) {
  return iter->current; 
}

/**
 * Get the next item in the list using the iterator 
 *
 * @param: iter - An iterator for a given list
 * @returns: The next item in the list given the iterator 
 */

Node* next(Iterator* iter) {
  iter->current = iter->current->next; 
  return iter->current; 
}

Node* prev(Iterator* iter) {
  iter->current = iter->current->prev; 
  return iter->current; 
}

/**
 * Check if there is a next item in the list 
 *
 * @param: iter - An iterator for a given list
 * @returns: True or false depending if the next item is null
 */

bool has_next(Iterator* iter) {
  return iter->current->next != NULL; 
}


bool has_prev(Iterator* iter) {
  return iter->current->prev != NULL; 
}


/**
 * Check if there is a current item in the iterator 
 *
 * @param: iter - An iterator for a given list
 * @returns: True or false depending if the current item is null
 */

bool has_current(Iterator* iter) {
  return iter->current != NULL; 
}

/**
 * Increment the current iterator item without returning the next item
 *
 * @param: iter - A reference to an iterator for a given list
 */

void iter_next(Iterator* iter) {
  if(iter->current != NULL) {
    iter->current = iter->current->next; 
  } else {
    printf("What is going on mate?\n\n"); 
  }
}

void iter_prev(Iterator* iter) {
  if(iter->current != NULL) {
    iter->current = iter->current->prev; 
  } else {
    printf("?etam no gniog si thaW\n\n"); 
  }
}

// =====================
// || CLI Methods     ||
// =====================



// =====================
// || Testing Methods ||
// =====================

/**
 * Test the traverse reverse of the list 
 *
 * This does not reverse it in memory 
 */

void traverse_reverse_test(DoublyLinkedList* test_list) {
  printf("Traverse Reverse Test: \n"); 
  traverse_reverse(test_list);

  printf("Testing the list is still the same after reversed traversal\n"); 
  to_string(test_list); 
}

/**
 * Test the reverse of the list 
 *
 * This method should reverse the list in memory 
 */

void reverse_test(DoublyLinkedList* test_list, char expected_output[]) {
  printf("Full List Reversal Test:\n\n");  
  printf("Expected Output:\n%s\n\nActual:\n", expected_output);
  reverse(test_list);  
}

void test_index_insertion(DoublyLinkedList* test_list) {
  insert_node(test_list, 25, test_list->size + 1);   
  insert_node(test_list, 7, 2); 
  insert_node(test_list, 17, 5); 

  DEBUG_PRINT("\n", NULL);
  to_string(test_list); 
}

/**
 * Some Automated tests that run when the Run Tests Flag is True
 */

void run_tests() {

  DoublyLinkedList test_list = initialize_list();  

  populate_list(&test_list); 

  traverse_reverse_test(&test_list); 

  printf("LIST_HEAD: %d\n\n", test_list.head->data);

  printf("LIST_TAIL: %d\n\n", test_list.tail->data);

  test_index_insertion(&test_list); 

  reverse_test(&test_list, "20 <=> 15 <=> 10 <=> 5 <=> END_OF_LIST"); 

  free_list(&test_list); 
}

void populate_list(DoublyLinkedList* test_list) {
  insert_node(test_list, 20, LIST_HEAD_INDEX);  
  insert_node(test_list, 15, LIST_HEAD_INDEX);  
  insert_node(test_list, 10, LIST_HEAD_INDEX);  
  insert_node(test_list, 5, LIST_HEAD_INDEX);  
  
  printf("Test List is populated:\n"); 
  to_string(test_list); 
}
