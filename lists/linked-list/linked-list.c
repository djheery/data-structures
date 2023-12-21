#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Node Struct
typedef struct {
 void* next;  
 int data;
} Node; 

// Linked List Utility Methods
void reverse(); 
void head(); 
void tail(); 
void insert_node(); 
void remove_node(); 
void next(); 
void to_string(Node* node);
Node* initialize_linked_list(); 

// Program Specific Methods
void print_menu();
void program_loop(); 

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

  Node* head = initialize_linked_list();
}

// A method to tear down the linked list and free all nodes

void free_linked_list() {
  
}

// Initiate Linked List head to Null

Node* initiate_linked_list() {
  Node* head = (Node*) malloc(sizeof(Node));  
  return head; 
}

// Insert a node

void insert_node() {
   
}

// Show the list as a string

void to_string(Node* node) {
  if(node == NULL) return; 
}


