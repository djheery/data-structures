#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define INITIAL_CAPACITY 5 

typedef struct {
  int* array; 
  size_t size; 
  size_t currentCapacity; 
} ArrayList; 

// ArrayList user operations
void show(ArrayList* arrayList); 
void find(ArrayList* arrayList); 
void get(ArrayList* arrayList); 
void insertIdx(ArrayList* arrayList); 
void removeIdx(ArrayList* arrayList); 
void push(ArrayList* arrayList); 
void pop(ArrayList* arrayList); 
void shift(ArrayList* arrayList); 
void unshift(ArrayList* arrayList); 
void size(ArrayList* arrayList); 
void loadFactor(ArrayList* arrayList); 

// Array List utility Operations 
float getLoadFactor(ArrayList* arrayList); 
bool getIsFull(ArrayList* arrayList); 
bool getIsEmpty(ArrayList* arrayList); 


// General Program Methods
void programLoop(); 
void printMenu(); 
void resize(ArrayList* arrayList); 
ArrayList initializeArrayList(); 
int getUserInput(char textPrompt[]); 
bool validateUserInput(char *pointer); 

  
int main() {
  return 0; 
}

void programLoop() {
  printf("========================\n"); 
  printf("* Queue Data Structure *\n"); 
  printf("========================\n\n"); 
  printf("Your ArrayList will be initialized with a size of 10 by default\n\n"); 
  ArrayList arrayList = initializeArrayList(); 

  while(true) {
    char commandPrompt[] = "Please enter the number of the command you would like to perform: "; 
    int command = validateUserInput(commandPrompt);
    printf("\n");

    switch(command) {
      case 1 : 
        break; 
      case 2 : 
        break; 
      case 3 : 
        break; 
      case 4 : 
        break; 
      case 5 : 
        break; 
      case 6 : 
        break; 
      case 7 : 
        break; 
      case 0 : 
        free(arrayList.array); 
        printf("Exiting the program...\n"); 
        printf("Goodbye!");
        exit(0); 
        break; 
      default : 
        printf("Whoops, it looks like your command is not in our list\n"); 
        printf("Please try again\n\n");
        break; 
    }
  }

  free(arrayList.array); 
}

void printMenu() {
  printf("Please select the operation you would like to perform\n\n"); 
  printf("[1] Show the Array List\n"); 
  printf("[2] Show the length of the Array\n"); 
  printf("[3] Push an Item to the Array\n"); 
  printf("[4] Shift an Item to the Array\n"); 
  printf("[5] Insert an Item into a given index\n"); 
  printf("[6] Pop an Item from the array\n"); 
  printf("[7] Unshift an Item from the array\n"); 
  printf("[8] Show the current size of the array\n"); 
  printf("[9] Show the current capacity of the array\n"); 
  printf("[0] Exit the program\n\n"); 
}

ArrayList initializeArrayList() {
  ArrayList arr;  
  arr.size = 0; 
  arr.currentCapacity = INITIAL_CAPACITY; 
  arr.array = (int*) malloc(INITIAL_CAPACITY * sizeof(int));

  if(arr.array == NULL) {
    printf("There was an error assinging the object to memory\n\n"); 
    exit(EXIT_FAILURE); 
  }

  return arr; 
}

int getUserInput(char textPrompt[]) {
  return 0;  
}

bool validateUserInput(char *pointer) {
  return false;  
}
