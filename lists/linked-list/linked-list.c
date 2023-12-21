#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * *----------------------------*
 * * Linked List Data Structure *
 * *----------------------------*
 *
 * I have decided to implement the Linked List in the following manner 
 *
 * - Separate the CLI methods from the Utility methods (All CLI methods have cli_ proceeding the method called
 * - Implement an iterator for the linked list for operations which require traversal of the list 
 * - Use 1 based indexing on the list (either will work - this is just to make it easier to correspond the size to the node positions for insertion and deletion 
 * - Implement a wrapper class to store the following head and tail of the linked list for O(1) lookup for head and tail alongside the size so that traversal of the list is not needed to get this information.
 *  
 * Methods Implemented: 
 *
 * - Reverse 
 * - insert_node** 
 * - remove_node
 * - tail 
 * - head 
 * - insert_at_begginning 
 * - insert_at_end
 *
 * **The insert method will be called on operations such as insert_at_begginning/end as these methods will just pass 0 || list->size to the insert method
 *
 */

// Node Struct
typedef struct {
 void* next;  
 int data;
} Node; 

typedef struct {
  Node* head;
  Node* tail; 
  int size;
} LinkedList;

typedef struct {
  Node* current;
} Iterator; 

// Linked List Utility Methods
Node* initialize_linked_list_node(); 
Node* head(LinkedList* list); 
Node* tail(LinkedList* list); 
Node* insert_node(LinkedList* list, int data, int position); 
Node* remove_node(LinkedList* list, int data_to_remove); 
Node* reverse(LinkedList* list); 
bool search(LinkedList* list, int data_to_search); 
void free_linked_list(LinkedList* list); 
bool check_valid_insertion(LinkedList* list, int position); 

// Iterator methods
Iterator to_iter(LinkedList* list); 
bool has_next(Iterator* iter); 
Node* next(Iterator* iter); 
Node* current(Iterator* iter); 

// CLI/UI Methods 
void to_string(LinkedList* list);
void cli_head(LinkedList* list); 
void cli_tail(LinkedList* list); 
void cli_reverse(LinkedList* list); 
void cli_insert_at_head(LinkedList* list); 
void cli_insert_at_tail(LinkedList* list); 
void cli_remove_at_head(LinkedList* list); 
void cli_remove_at_tail(LinkedList* list); 
void cli_insert_node_at_position(LinkedList* list); 
void cli_remove_node_at_position(LinkedList* list); 
void cli_iterate(LinkedList* list); 
void cli_search_for_node(LinkedList* list);
void cli_free_list(LinkedList* list); 

// Program Specific Methods
void print_menu();
void program_loop(); 
int get_user_input();
bool validate_user_input(); 

// ==========================
// || Main Program Methods ||
// ==========================

int main() {
  return 0;
}

// Print the program menu

void print_menu() {
    
}

// The main Program loop

void program_loop() {
  printf("================================\n");  
  printf("|| Linked List Data Structure ||\n"); 
  printf("================================\n\n");  
  printf("The head of the list will be initialized to null for you to manipulate\n\n");

  Node* head = initialize_linked_list_node();
  LinkedList list; 
  list.head = head; 
  list.tail = NULL; 
  list.size = 1; 
}

// =================================
// || Linked List Utility Methods ||
// =================================

// A method to tear down the linked list and free all nodes

void free_linked_list(LinkedList* list) {
  
}

// Initiate Linked List head to Null

Node* initiate_linked_list_node() {
  Node* node = (Node*) malloc(sizeof(Node));  

  if(node == NULL) {
    printf("Error when allocating the memory for the node"); 
    exit(EXIT_FAILURE); 
  }

  return node; 
}

// Check for a valid insertion 

bool check_valid_insertion(LinkedList* list, int position) {
  int size = list->size; 
  
  if(size == 0 && position != 1) return false;  
  if(position > size) return false; 

  return true;  
}

// Insert a node

Node* insert_node(LinkedList* list, int data, int position) {
  bool is_valid = check_valid_insertion(list, position); 

  if(!is_valid) {
    printf("Error: The position indicated is not valid\n"); 
    printf("This should not have been called as this should be checked before entrance to the method\n\n"); 
    return NULL;
  }

  Node* new_node = initiate_linked_list_node();
  new_node->data = data; 
  new_node->next = NULL; 

  if(position == 1) {
    Node* next_node = list->head; 
    new_node->next = next_node; 
    list->head = new_node; 
    list->size += 1; 
    return new_node; 
  }

  int count = 1; 
  Iterator iter = to_iter(list);

  while(count < position) {
     if(has_next(&iter)) {
       next(&iter); 
       count++; 
     }
  }

  Node* prev_node = iter.current; 
  new_node->next = prev_node->next; 
  prev_node->next = new_node; 
  list->size += 1; 

  return new_node;
}

// Search the List for an occurence of a node with specified data
bool search(LinkedList* list, int data_to_search) {
  if(list->size == 0) {
    return false; 
  }

  Iterator iter = to_iter(list); 
  Node* current_node; 

  while((current_node = current(&iter)) != NULL) {
    if(current_node->data == data_to_search) {
      return true; 
    }

    next(&iter); 
  }


  return false;
}

// Show the list as a string

void to_string(LinkedList* list) {
  if(list->head == NULL || list->size == 0) return; 

  Iterator iter = to_iter(list);
}

// ================================================
// || Below is the Start of the Iterator Methods ||
// ================================================

// Create an iterator for the LinkedList

Iterator to_iter(LinkedList* list) {
  Iterator iter; 
  iter.current = list->head; 
  return iter; 
}

// Check if there is a next node for the current node of the iterator

bool has_next(Iterator* iter) {
  return iter->current->next != NULL;  
}

// Return the next node of the iterator; 

Node* next(Iterator* iter) {
  if(has_next(iter)) {
    iter->current = iter->current->next; 
    return iter->current; 
  };

  return NULL;    
}

// Get the current node of the iterator

Node* current(Iterator* iter) {
  return iter->current; 
}

// ===========================================
// || Below is the Start of the CLI Methods ||
// ===========================================
