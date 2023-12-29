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
bool insert_head(DoublyLinkedList* list, int node_data); 
bool insert_tail(DoublyLinkedList* list, int node_data); 
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
void incr_next(Iterator* iter); 

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
  return 0; 
}

void program_loop() {
  
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


  if(position == LIST_HEAD_INDEX) {
    bool has_inserted = insert_head(list, node_data);  
    return has_inserted; 
  }

  Node* new_node = initialize_node(node_data);

  if(new_node == NULL) {
    printf("Something went wrong initializing the new node, the program will exit\n\n"); 
    exit(EXIT_FAILURE);
  }

  Iterator iter = to_iter(list);
  int count = 0; 
  Node* current_node;

  while((count < position - 1) && has_next(&iter)) { 
    current_node = current(&iter);
    incr_next(&iter);
    count++;
  }

  if(count != position - 1) {
    DEBUG_PRINT("!!ERROR!!", NULL);
    DEBUG_PRINT("There are not enough elements to insert another element. \n", NULL); 
    DEBUG_PRINT("This should not be called as this condition should be checked prior to reaching this point\n\n", NULL); 
    return false; 
  }

  Node* new_next = current_node->next; 
  current_node->next = new_node; 
  new_node->prev = current_node; 
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


bool insert_head(DoublyLinkedList* list, int node_data) {
  Node* new_node = initialize_node(node_data);

  if(new_node == NULL) {
    printf("Something went wrong initializing the new node, the program will exit\n\n"); 
    exit(EXIT_FAILURE);
  }
  
  if(list->size == 0 || list->head == NULL) {
    list->head = new_node; 
    list->tail = new_node; 
    list->size += 1; 
    return true;  
  }

  new_node->next = list->head; 
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


bool insert_tail(DoublyLinkedList* list, int node_data) {
  Node* new_node = initialize_node(node_data); 

  if(new_node == NULL) {
    printf("Something went wrong initializing the new node, the program will exit\n\n"); 
    exit(EXIT_FAILURE);
  }

  new_node->prev = list->tail;
  list->tail->next = new_node; 
  list->tail = new_node; 
  list->size += 1;

  return true;  
}



// ======================
// || Iterator Methods ||
// ======================

/**
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

/**
 * Check if there is a next item in the list 
 *
 * @param: iter - An iterator for a given list
 * @returns: True or false depending if the next item is null
 */

bool has_next(Iterator* iter) {
  return iter->current->next != NULL; 
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

void incr_next(Iterator* iter) {
  iter->current = iter->current->next; 
}

// =====================
// || CLI Methods     ||
// =====================



// =====================
// || Testing Methods ||
// =====================

void run_tests() {
  DoublyLinkedList test_list = initialize_list();  
}
