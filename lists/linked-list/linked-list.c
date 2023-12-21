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
void insertNode(); 
void removeNode(); 
void next(); 

// Program Specific Methods
void printMenu();
void programLoop(); 

int main() {
  Node* head = NULL;  
  return 0;
}

void programLoop() {
  
}

void printMenu() {
  
}
