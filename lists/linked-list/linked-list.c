#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define RUN_TESTS false
#define DEBUG 

#ifdef DEBUG 
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__);
#else 
#define DEBUG_PRINT(fmt, ...);
#endif

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
int remove_tail(LinkedList* list); 
int remove_head(LinkedList* list); 
LinkedList initialize_linked_list();

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
void cli_insert_at_head(LinkedList* list); 
void cli_insert_at_tail(LinkedList* list); 
void cli_remove_node(LinkedList* list); 
void cli_insert_at_position(LinkedList* list); 
void cli_search_for_node(LinkedList* list);
void cli_reverse(LinkedList* list); 
void cli_remove_at_head(LinkedList* list); 
void cli_remove_at_tail(LinkedList* list); 

// TO IMPLEMENT
void cli_iterate(LinkedList* list); 

// Program Specific Methods
void print_menu();
void program_loop(); 
int  get_user_input(char text_prompt[]);
bool validate_user_input(char* p); 

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
  printf("[5] Insert an item to the beginning of the Linked List\n"); 
  printf("[6] Insert an item to the end of the Linked List\n"); 
  printf("[7] Insert an item at a given position of the Linked List\n"); 
  printf("[8] Remove an item from the beginning of the linked list\n"); 
  printf("[9] Remove an item from the end of the linked list\n"); 
  printf("[10] Remove an item from a given postion of the linked list\n"); 
  printf("[11] Search for an item in the linked list\n"); 
  printf("[12] Reverse the linked list\n"); 
  printf("[0] Exit the program\n\n"); 
}

// The main Program loop

void program_loop() {
  printf("================================\n");  
  printf("|| Linked List Data Structure ||\n"); 
  printf("================================\n\n");  
  printf("The head of the list will be initialized to null for you to manipulate\n\n");

  LinkedList list = initialize_linked_list();

   if(RUN_TESTS) {
    LinkedList test_list = initialize_linked_list(); 
    perform_tests(&test_list); 
    printf("Freeing the test list...\n\n"); 
    free_linked_list(&test_list); 
    printf("Freed test list succesfully\n\n");
    return; 
  }

  while(true && !RUN_TESTS) {
    char text_prompt[] = "Please enter the number of the command you would like to perform: "; 
    int command = get_user_input(text_prompt); 

    switch(command) {
      case 1 : 
        to_string(&list);  
        break; 
      case 2 : 
        printf("The current size of the linked list is: %d\n\n", list.size); 
        break; 
      case 3 : 
        cli_head(&list);
        break; 
      case 4 : 
        cli_tail(&list);
        break; 
      case 5 : 
        cli_insert_at_head(&list);
        break; 
      case 6 : 
        cli_insert_at_tail(&list); 
        break; 
      case 7 : 
        cli_insert_at_position(&list);
        break; 
      case 8 : 
        cli_remove_at_head(&list);
        break; 
      case 9 :
        cli_remove_at_tail(&list);
        break; 
      case 10 : 
        cli_remove_node(&list);
        break; 
      case 11 : 
        cli_search_for_node(&list);
        break; 
      case 12 : 
        cli_reverse(&list);
        break;
      case 0 : 
        printf("Thankyou for using the program\nFreeing the list nodes from memory\n"); 
        free_linked_list(&list);
        printf("Sucess!\nGoodbye...\n\n"); 
        exit(0); 
      default : 
        printf("Whoops unknown command - Please try again\n\n"); 
    }
  }

    free_linked_list(&list); 
}

// =================================
// || Linked List Utility Methods ||
// =================================

// Initialize the Linked List 

LinkedList initialize_linked_list() {
  LinkedList list; 
  list.head = NULL; 
  list.tail = NULL; 
  list.size = 0; 
  return list; 
}

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

    DEBUG_PRINT("Freeing node: %d\n", current_node->data);
    free(current_node); 
    DEBUG_PRINT("Freed node Sucessfully\n", NULL); 
  }

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
  
  if(size == 0 && position != 1) return false;  
  if(size != 0 && position > (size + 1)) return false; 

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

  while(has_current(&iter)) {
    Node* current_node = current(&iter); 
    DEBUG_PRINT("%d NODE, %d DATA\n", current_node->data, data_to_search); 

    if(current_node->data == data_to_search) {
      return true; 
    }

    next(&iter); 
  }


  return false;
}

// NOT USED JUST TO SEE HOW TO REVERSE WITH ITERATOR

bool reverse_with_iter(LinkedList* list) {
  Iterator iter = to_iter(list);  
  Node* current_node = current(&iter); 
  Node* next_node = NULL; 
  Node* prev_node = NULL; 

  while(has_current(&iter)) {
    next_node = next(&iter); 
    current_node->next = prev_node; 
    prev_node = current_node; 
    current_node = next_node; 
  }

  Node* tmp_tail = list->tail; 
  list->tail = list->head; 
  list->head = tmp_tail; 

  return true; 
}

// Reverse the list

bool reverse(LinkedList* list) {
  if(list->size == 0 || list->size == 1) {
    return false; 
  }

  Node* current_node = list->head; 
  Node* next_node; 
  Node* prev_node = NULL; 

  while(current_node != NULL) {
    next_node = current_node->next;  
    current_node->next = prev_node; 
    prev_node = current_node; 
    current_node = next_node; 
  }
  
  // Swap The head and tail
  Node* tmp_tail = list->tail;
  list->tail = list->head; 
  list->head = tmp_tail; 

  return true; 
}

// Remove the head of the list

int remove_head(LinkedList* list) {
  int prev_head_data = list->head->data; 
  Node* prev_head = list->head; 

  list->head = prev_head->next; 

  free(prev_head); 

  list->size -= 1;

  if(list->head == NULL) {
    list->tail = NULL;
    list->size = 0; 
  }

  return prev_head_data;  
}

// Remove the tail of the list

int remove_tail(LinkedList* list) {
  Iterator iter = to_iter(list); 
  Node* prev_node;
  int tail_data = list->tail->data;

  while(has_current(&iter)) {
    Node* current_node = current(&iter); 

    if(current_node != list->tail) {
      prev_node = current_node;  
      next(&iter); 
      continue; 
    }

    // If the head and tail point to the same item then just initialize both to NULL and reset the list
    if(current_node == list->tail && current_node == list->head) {

      // This should never bbe called
      if(list->size != 1) {
        printf("There is a major logical error -> if both the head and tail point to the same item the list length can only be one, However it was not\n"); 
        printf("Freeing the list and exiting the program\n\n"); 
        free_linked_list(list);         
        exit(EXIT_FAILURE); 
      }

      list->tail = NULL; 
      list->head = NULL; 
      list->size = 0; 
    } else {
      list->tail = prev_node; 
      list->tail->next = NULL; 
      list->size -= 1; 
    }

    free(current_node); 
    break; 
  }

  return tail_data; 
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

// Cli Method for getting the head of the list 

void cli_head(LinkedList* list) {
  if(list->size == 0) {
     printf("Your list is currently empty, thus there is nothing too print\n\n");    
     return;
   }

  if(list->head == NULL) {
    printf("Your list head currently NULL, this means there must be an error in your program as your list size is not 1\n\n"); 
    return; 
  }

  Node* l_head = head(list);  

  printf("List Head Information:\n"); 
  printf("> Pointer: %p\n", l_head); 
  printf("> Data: %d\n", l_head->data); 
  printf("> Has Next: %s\n\n", l_head->next == NULL ? "TRUE" : "FALSE"); 
}

// CLI method for printing the list tail information

void cli_tail(LinkedList* list) {
  if(list->size == 0) {
     printf("Your list is currently empty, thus there is nothing too print\n\n");    
     return;
  }

  if(list->tail == NULL) {
    printf("Your list tail is currently NULL, this means you done messed up somewhere\n\n");
    return; 
  }

  Node* l_tail = tail(list); 

  printf("List Tail Information:\n");
  printf("> Pointer: %p\n", l_tail); 
  printf("> Data: %d\n\n", l_tail->data); 
}

// CLI Method for reversing the linked list 

void cli_reverse(LinkedList* list) {
  printf("Reversing the list...\n\n"); 

  printf("Before:\n"); 
  to_string(list); 
  
  reverse(list); 

  printf("After:\n"); 
  to_string(list); 
}

// CLI Method for inserting at the head 

void cli_insert_at_head(LinkedList* list) {
  int user_input = get_user_input("Please enter the integer you would like to insert: "); 

  if(user_input == -1) {
    return; 
  }

  insert_node(list, user_input, 1); 
  printf("Node inserted at head: %d\n\n", list->head->data); 
}

// CLI Method for inserting at the head 

void cli_insert_at_tail(LinkedList* list) {
  int user_input = get_user_input("Please enter the integer you would like to insert: "); 

  if(user_input == -1) {
    return; 
  }

  insert_node(list, user_input, (list->size + 1)); 
  printf("Node inserted at head: %d\n\n", list->tail->data); 
}

// CLI Method for Inserting a node at a given position
void cli_insert_at_position(LinkedList* list) {
  int position_to_insert = get_user_input("Please enter the position you would like to insert at: ");  

  if(position_to_insert == -1) return; 

  if(position_to_insert > (list->size + 1)) {
    printf("You're position is out of bounds or invalid\n\n");  
    return; 
  }

  int num_to_insert = get_user_input("Please enter the integer you would like to insert: ");

  if(num_to_insert == -1) return; 

  Node* node = insert_node(list, num_to_insert, position_to_insert); 
  printf("Node inserted: %d\n\n", node->data); 
}

// CLI Remove Node
void cli_remove_node(LinkedList* list) {
  int user_input = get_user_input("Please enter the integer you would like to insert: "); 

  if(user_input == -1) {
    return; 
  }

  bool removed = remove_node(list, user_input); 

  if(!removed) {
    printf("Unfortunately the node, %d,  has not been found within the list\n\n", user_input);
    return;
  }

  printf("Node %d, sucessfully removed\n\n", user_input);
}

// Remove at tail

void cli_remove_at_head(LinkedList* list) {
  int size = list->size; 

  if(size == 0) {
    printf("The list is empty, thus cannot remove an element\n\n"); 
    return; 
  }

  if(list->head == NULL) {
    printf("Something went wrong, the lists size is greater than zero but there is no head, please check the code base\n\n"); 
    return; 
  }

  int prev_head = remove_head(list);

  printf("The previous head was: %d\n", prev_head); 
  printf("The new head is: %d\n\n", list->head->data); 

}

// Remove at head

void cli_remove_at_tail(LinkedList* list) {
  int size = list->size; 

  if(size == 0) {
    printf("The list is empty, thus cannot remove an element\n\n"); 
    return; 
  }

  if(list->tail == NULL) {
    printf("Something went wrong, the lists size is greater than zero but there is no tail, please check the code base\n\n"); 
    return; 
  }

  int prev_head = remove_head(list);

  printf("The previous head was: %d\n", prev_head); 
  printf("The new head is: %d\n\n", list->head->data); 

}

// CLI Search

void cli_search_for_node(LinkedList* list) {
  int node_to_search = get_user_input("Please enter the node data you wish to search for: ");  
  
  if(node_to_search == -1) {
    printf("Something went wrong\n"); 
    printf("Returning to the menu...\n\n"); 
    return; 
  }

  bool is_found = search(list, node_to_search); 

  if(is_found) {
    printf("Node, %d, has been found in the list\n\n", node_to_search); 
    return; 
  }

  printf("Node has not been found\n\n"); 
}

// =======================================
// || Below are the User Input Methods  ||
// =======================================

bool validate_user_input(char *p) {

  while(*p) {
    if(isdigit((unsigned char)* p)) {
      return false;  
    }
    p++;
  }
  
  return true; 
}

int get_user_input(char text_prompt[]) {
  bool is_valid = false; 
  const int max_retries = 3; 
  int current_retries = 0; 
  int user_input = -1;

  while(!is_valid | (current_retries < max_retries)) {
    char buffer[10]; 
    printf("> %s: ", text_prompt);
    fgets(buffer, sizeof(buffer), stdin);
    printf("\n"); 
    char* p = buffer;   
    bool is_valid = validate_user_input(p);

    if(is_valid) {
      user_input = atoi(buffer);
      break;
    }

    current_retries += 1; 
    
    if(current_retries >= max_retries) {
      printf("Unfortumately you have made too many failed attempts\n"); 
      printf("Returning to the menu\n\n");
      return -1; 
    }

    if(current_retries > 0) {
      printf("Whoops, something went wrong. Please try again...\n\n"); 
      continue;
    }
  }
  

  
  return user_input; 
}




// ====================
// || Tester Methods ||
// ====================

void populate_linked_list(LinkedList* list) {
  printf("Populating linked list from a base\n\n"); 
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
  to_string(list); 
}

// TEST ARBITRARY NODE REMOVAL
void test_node_removal(LinkedList* list) {
  printf("Removing some arbitrary nodes (10, 22)...\n\n"); 
  remove_node(list, 10); 
  remove_node(list, 22); 
  to_string(list); 
}

// TEST HEAD REMOVAL
void test_head_removal(LinkedList* list) {
  printf("Removing head..\n\n");
  remove_node(list, 5); 
  printf("NEW_HEAD: %d; STATUS: %s\n", list->head->data, list->head->data == 7 ? "PASSED" : "FAILED"); 
  to_string(list); 
}

// TEST TAIL REMOVAL
void test_tail_removal(LinkedList* list) {
  printf("Removing tail..\n\n");
  remove_node(list, 30); 
  printf("NEW_TAIL: %d; STATUS: %s\n\n", list->tail->data, list->tail->data == 29 ? "PASSED" : "FAILED" ); 
  to_string(list);
}

void test_search(LinkedList* list) {
  // TEST SEARCH
  printf("Testing Search\n"); 
  bool has_10 = search(list, 25); 
  printf("Search for 10 should be TRUE; Status: %s\n\n", has_10 ? "PASSED" : "FAILED"); 
  bool has_30 = search(list, 30); 
  printf("Search for 30 should be FALSE; Status: %s\n\n", !has_30 ? "PASSED" : "FAILED"); 
  bool has_45 = search(list, 45); 
  printf("Search for 45 should be FALSE; Status: %s\n\n", !has_45 ? "PASSED" : "FAILED"); 
  printf("ADDED 45 to retest\n");
  insert_node(list, 45, 3); 
  bool has_45_2 = search(list, 45); 
  printf("Search for 45 should be TRUE; Status: %s\n\n", has_45_2 ? "PASSED" : "FAILED"); 
}

void test_reverse(LinkedList* list) {
  printf("REVERSING THE LIST\n\n"); 
  printf("Before: \n");
  to_string(list); 

  // reverse_with_iter(list);  
  reverse(list); 
  printf("After: \n"); 
  to_string(list); 

  printf("New Head => %d\n", list->head->data);
  printf("New Tail => %d\n\n", list->tail->data);
}


// Perform the Tests
void perform_tests(LinkedList* list) {
  
  populate_linked_list(list);

  test_node_removal(list);

  test_head_removal(list);

  test_tail_removal(list);

  test_search(list);

  test_reverse(list);

}
