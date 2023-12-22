#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define DEBUG true 

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

// Linked List Struct
typedef struct {
  Node* head;
  Node* tail; 
  int size;
} LinkedList;

// Iterator Struct
typedef struct {
  Node* current;
} Iterator; 

// Linked List Utility Methods
Node* initiate_linked_list_node(); 
Node* head(LinkedList* list); 
Node* tail(LinkedList* list); 
Node* insert_node(LinkedList* list, int data, int position); 
bool remove_node(LinkedList* list, int data_to_remove); 
bool  reverse(LinkedList* list); 
bool  search(LinkedList* list, int data_to_search); 
void  free_linked_list(LinkedList* list); 
bool  check_valid_insertion(LinkedList* list, int position); 

// Iterator methods
Iterator to_iter(LinkedList* list); 
bool     has_next(Iterator* iter); 
bool     has_current(Iterator* iter); 
Node*    next(Iterator* iter); 
Node*    current(Iterator* iter); 

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
int  get_user_input();
bool validate_user_input(); 

// Tester Methods 
void populate_linked_list(LinkedList* list); 
void perform_tests(LinkedList* list); 

// ==========================
// || Main Program Methods ||
// ==========================

int main() {
  program_loop();
  return 0;
}

// Print the program menu

void print_menu() {
  printf("Please select the operation you would like to perform\n\n"); 
  printf("[1] Show the Linked List\n"); 
  printf("[2] Show the size of the Linked List\n"); 
  printf("[3] Show the head of the list\n");
  printf("[4] Show the tail of the list\n"); 
  printf("[4] Insert an item to the beginning of the Linked List\n"); 
  printf("[5] Insert an item to the end of the Linked List\n"); 
  printf("[6] Insert an item at a given position of the Linked List\n"); 
  printf("[7] Remove an item from the beginning of the linked list\n"); 
  printf("[8] Remove an item from the end of the linked list\n"); 
  printf("[9] Remove an item from a given postion of the linked list\n"); 
  printf("[10] Search for an item in the linked list\n"); 
  printf("[11] Reverse the linked list\n"); 
  printf("[12] Iterate through the linked list\n"); 
  printf("[0] Exit the program\n\n"); 
}

// The main Program loop

void program_loop() {
  printf("================================\n");  
  printf("|| Linked List Data Structure ||\n"); 
  printf("================================\n\n");  
  printf("The head of the list will be initialized to null for you to manipulate\n\n");

  Node* head = initiate_linked_list_node();
  LinkedList list; 
  list.head = head; 
  list.tail = NULL; 
  list.size = 0; 

  if(DEBUG) {
    perform_tests(&list); 
    printf("Freeing the list...\n\n"); 
    free_linked_list(&list); 
    printf("Freed succesfully\n\n");
    return; 
  }

  // while(true) {
  //   char text_prompt[] = "Please enter the number of the command you would like to perform: "; 
  //   int command = 11; 
  //
  //   switch(command) {
  //     case 1 : 
  //       to_string(&list);  
  //       break; 
  //     case 2 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 3 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 4 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 5 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 6 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 7 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 8 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 9 :
  //       printf("TODO!\n\n");
  //       break; 
  //     case 10 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 11 : 
  //       printf("TODO!\n\n");
  //       break; 
  //     case 12 : 
  //       printf("TODO!\n\n");
  //       break;
  //     case 0 : 
  //       printf("Thankyou for using the program\nFreeing the list nodes from memory\n"); 
  //       free_linked_list(&list);
  //       printf("Sucess!\nGoodbye...\n\n"); 
  //       exit(0); 
  //     default : 
  //       printf("Whoops unknown command - Please try again\n\n"); 
  //   }
  // }

    free_linked_list(&list); 
}

// =================================
// || Linked List Utility Methods ||
// =================================

// Get the head of the list

Node* head(LinkedList* list) {
  return list->head; 
}

// Get the tail of the list

Node* tail(LinkedList* list) {
  return list->tail;
}

// A method to tear down the linked list and free all nodes

void free_linked_list(LinkedList* list) {
  if(list->size == 0) return; 

  Iterator iter = to_iter(list);  

  while(has_current(&iter)) {
    Node* current_node = current(&iter); 

    // About to remove the current node so pre-increment the next; 
    next(&iter); 

    if(DEBUG) printf("Freeing node: %d\n", current_node->data);
    free(current_node); 
    if(DEBUG) printf("Freed node Sucessfully\n"); 
  }

  // if(DEBUG) printf("Freeing the tail\n"); 
  // if(DEBUG) printfLL;
  list->size = 0; 
}

// Initiate Linked List head to Null

Node* initiate_linked_list_node() {
  Node* node = (Node*) malloc(sizeof(Node));  

  if(node == NULL) {
    printf("Error when allocating the memory for the node"); 
    exit(EXIT_FAILURE); 
  }

  node->next = NULL; 

  return node; 
}

// Check for a valid insertion 

bool check_valid_insertion(LinkedList* list, int position) {
  int size = list->size; 
  
  // if(size == 0 && position != 1) return false;  
  // if(size != 0 && (position + 1) > size) return false; 

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

    if(list->size == 1) {
      list->tail = new_node; 
    }

    return new_node; 
  }

  int count = 1; 
  Iterator iter = to_iter(list);

  while(count < (position - 1)) {
     if(has_next(&iter)) {
       next(&iter); 
       count++; 
     }
  }

  Node* prev_node = iter.current; 
  new_node->next = prev_node->next; 
  prev_node->next = new_node; 
  list->size += 1; 

  if(list->size == position) {
    list->tail = new_node; 
    new_node->next = NULL; 
  }

  return new_node;
}

// Remove a Node from memory

bool remove_node(LinkedList* list, int data_to_remove) {
  if(list->size == 0) {
    return false; 
  }

  if(list->size == 1) {
    Node* n = list->head;  

    if(n == NULL) {
      printf("Why is the head NULL if there is one element in the list?\n\n");
      return false; 
    }

    if(n->data == data_to_remove) {
      list->head = NULL; 
      list->tail = NULL; 
      free(n); 
      list->size -= 1;
      return true; 
    }

    return false; 
  }

  Iterator iter = to_iter(list);
  bool node_has_been_removed = false; 
  Node* prev_node; 

  while(has_next(&iter) || prev_node != NULL) {
    Node* current_node = current(&iter); 
    bool is_target = current_node->data == data_to_remove;

    if(!is_target) {
      prev_node = current_node; 
      next(&iter); 
      continue; 
    }

    bool is_head = current_node == list->head;  
    bool is_tail = current_node == list->tail;
    bool error_head_removal = is_head && list->size == 1; 
    bool error_tail_removal = is_tail && prev_node == NULL; 

    if(error_head_removal) {
      printf("Trying to remove the head but within the while loop, this base case should have been checked at the start\n"); 
      printf("This should never be called\n\n"); 
      return false; 
    }

    if(error_tail_removal) {
      printf("Trying to remove the tail when the size of the list is 1, this is a base case and should be checked at the start\n");  
      printf("This will also force an error for the prev_node. The prev node will always be NULL as we are looking at the head\n"); 
      return false; 
    }

    if(is_head) {
      list->head = current_node->next; 
    }

    if(is_tail) {
      prev_node->next = NULL; 
      list->tail = prev_node;
    } 

    if(!is_head && !is_tail) {
      prev_node->next = current_node->next;
    }

    free(current_node);
    list->size -= 1;
    node_has_been_removed = true;  
    break; 
  }
 
  return node_has_been_removed; 
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

// Reverse the list

bool reverse(LinkedList* list) {
  if(list->size == 0 || list->size == 1) {
    return false; 
  }


  return true; 
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

bool has_current(Iterator* iter) {
  return iter->current != NULL;  
}

// Check if there is a next node for the current node of the iterator

bool has_next(Iterator* iter) {
  return iter->current->next != NULL;  
}

// Return the next node of the iterator; 

Node* next(Iterator* iter) {
  iter->current = iter->current->next; 
  return iter->current; 
}

// Get the current node of the iterator

Node* current(Iterator* iter) {
  return iter->current; 
}

// ===========================================
// || Below is the Start of the CLI Methods ||
// ===========================================

// Show the list as a string

void to_string(LinkedList* list) {
  if(list->head == NULL || list->size == 0) return; 

  Iterator iter = to_iter(list);

  while(has_next(&iter)) {
    Node* current_node = current(&iter);
    printf("%d => ", current_node->data);  
    next(&iter); 
  }

  Node* last = current(&iter); 
  printf("%d => END_OF_LIST\n\n", last->data); 
}

// ====================
// || Tester Methods ||
// ====================

void populate_linked_list(LinkedList* list) {
  insert_node(list, 25, 1); 
  insert_node(list, 20, 1); 
  insert_node(list, 15, 1); 
  insert_node(list, 10, 1); 
  insert_node(list, 5, 1);
  insert_node(list, 7, 2); 
  insert_node(list, 17, 5); 
  insert_node(list, 22, 7); 
  insert_node(list, 30, (list->size + 1));
  insert_node(list, 29, (list->size)); 
  insert_node(list, 13, 4); 
}

void perform_tests(LinkedList* list) {

  printf("Populating linked list from a base\n\n"); 
  populate_linked_list(list);
  to_string(list);
  printf("Removing some arbitrary nodes (10, 22)...\n\n"); 
  remove_node(list, 10); 
  remove_node(list, 22); 
  to_string(list); 
  printf("Removing head..\n\n");
  remove_node(list, 5); 
  printf("NEW_HEAD: %d; STATUS: %s\n", list->head->data, list->head->data == 7 ? "PASSED" : "FAILED"); 
  to_string(list); 
  printf("Removing tail..\n\n");
  remove_node(list, 30); 
  printf("NEW_TAIL: %d; STATUS: %s\n\n", list->tail->data, list->tail->data == 29 ? "PASSED" : "FAILED" ); 
  to_string(list);
  printf("Testing Search\n"); 
}
