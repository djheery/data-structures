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
Node* insert_node(DoublyLinkedList* list, int node_data); 
int remove_node(DoublyLinkedList* list, int node_data); 
int remove_head(DoublyLinkedList* list); 
int remove_tail(DoublyLinkedList* list); 
bool search(DoublyLinkedList* list, int data_to_search); 
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

DoublyLinkedList initialize_list() {
  DoublyLinkedList list; 
  list.head = NULL; 
  list.tail = NULL; 
  list.size = 0; 
  return list; 
}

Node* initalize_node(int data) {
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

// =====================
// || CLI Methods     ||
// =====================



// =====================
// || Testing Methods ||
// =====================

