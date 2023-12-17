#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define INITIAL_CAPACITY 5 
#define LOAD_FACTOR_THRESHOLD 0.7
#define GROWTH_FACTOR 0.5 

typedef struct {
  int* array; 
  size_t size; 
  size_t currentCapacity; 
} ArrayList; 

// ArrayList user operations
void show(ArrayList* arrayList); 
void get(ArrayList* arrayList); 
void insertAtIdx(ArrayList* arrayList); 
void removeAtIdx(ArrayList* arrayList); 
void push(ArrayList* arrayList); 
void pop(ArrayList* arrayList); 
void shift(ArrayList* arrayList); 
void unshift(ArrayList* arrayList); 
void size(ArrayList* arrayList); 
void capacity(ArrayList* arrayList);
void loadFactor(ArrayList* arrayList); 
void clear(ArrayList* arrayList); 
void isEmpty(ArrayList* arrayList); 
void indexOf(ArrayList* arrayList); 
void trimToSize(ArrayList* arrayList); 
void reverse(ArrayList* arrayList); 
void contains(ArrayList* arrayList); 
void subList(ArrayList* arrayList); 

// Array List utility Operations 
float getLoadFactor(ArrayList* arrayList); 
bool getIsFull(ArrayList* arrayList); 
bool getIsEmpty(ArrayList* arrayList); 
bool getContains(ArrayList* arrayList, int numToCheck); 
void swap(ArrayList* arrayList, int idx1, int idx2); 
int getIdx(ArrayList* arrayList, int idx); 
bool listInsert(ArrayList* arrayList, int idx, int numToInsert); 
bool listRemove(ArrayList* arrayList, int idx); 

// General Program Methods
void programLoop(); 
void printMenu(); 
void printSubListOptions(); 
bool resize(ArrayList* arrayList); 
ArrayList initializeArrayList(); 
int getUserInput(char textPrompt[]); 
bool validateUserInput(char *pointer); 

  
int main() {
  programLoop(); 
  return 0; 
}

// The main program loop

void programLoop() {
  printf("========================\n"); 
  printf("* Queue Data Structure *\n"); 
  printf("========================\n\n"); 
  printf("Your ArrayList will be initialized with a size of 10 by default\n\n"); 
  ArrayList arrayList = initializeArrayList(); 

  while(true) {
    printMenu();
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
      case 8 : 
        break; 
      case 9 : 
        break; 
      case 10 : 
        break;
      case 11 : 
        break; 
      case 12 : 
        break; 
      case 13 : 
        break; 
      case 14 : 
        break; 
      case 15 : 
        break; 
      case 16 : 
        break; 
      case 17 : 
        break; 
      case 18: 
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

// Print the menu to the UI 

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
  printf("[10] Show the current load factor of the array\n"); 
  printf("[11] Show if the array is empty\n"); 
  printf("[12] Show if the array is Full\n"); 
  printf("[13] Show the index of an item\n"); 
  printf("[14] Trim array to size\n"); 
  printf("[15] Reverse the array\n"); 
  printf("[16] See if the array contains an item\n"); 
  printf("[17] Create a see a sublist from provided options\n");
  printf("[18] Populate the array with random elements\n"); 
  printf("[0] Exit the program\n\n"); 
}

// Initialize the ArrayList on program load

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

// Get the user input 
// Side effect - Validate the input also

int getUserInput(char textPrompt[]) {
  return 0;  
}

// Validate the User input

bool validateUserInput(char* pointer) {
  return false;  
}

// Get the load factor of the current ArrayList

float getLoadFactor(ArrayList* arrayList) {
  float size = (float) arrayList->size; 
  float capacity = (float) arrayList->currentCapacity;
  return size / capacity; 
}

// Utility for index of method

int getIdx(ArrayList* arrayList, int idx) {
  if(idx > (arrayList->size - 1)) {
    return -1; 
  }

  return arrayList->array[idx];
}

// Insert an integer at a given index

bool listInsert(ArrayList* arrayList, int idx, int numToInsert) {
  bool isOutOfBounds = (idx > (arrayList->size - 1)) || (idx < 0); 
  bool isFull = getIsFull(arrayList); 

  if(isFull) {
    printf("The array should not be full, it should have been resized before it reaches this point\n\n"); 
    printf("Closing program\n\n");
    exit(EXIT_FAILURE);
  }

  if(isOutOfBounds) {
    printf("The index selected is out of bounds.\n"); 
    printf("Althought ArrayLists/Vectors can grow in size, the insertion must still be contiguous\n\n"); 
    return false; 
  }

  if(idx == arrayList->size - 1) {
    arrayList->array[idx] = numToInsert;
    arrayList->size += 1; 
    return true;  
  }

  int i; 
  int prevNum = arrayList->array[idx];
  for(i = idx; i < arrayList->size - 1; i++) {
    if(i == idx) {
      arrayList->array[idx] = numToInsert;  
      continue; 
    }

    int tmp = arrayList->array[i + 1]; 
    arrayList->array[idx + 1] = prevNum; 
    prevNum = tmp;
  }

  arrayList->size += 1; 

  return true;  
}

// Remove an index from the array

bool listRemove(ArrayList* arrayList, int idx) {
  return true; 
}

// Get if the array contains a given integer

bool getContains(ArrayList* arrayList, int numToCheck) {
  bool isEmpty = getIsEmpty(arrayList); 
  if(isEmpty) {
    return false; 
  }

  int i; 
  for(i = 0; i < arrayList->size; i++) {
    int current = arrayList->array[i]; 
    if(current == numToCheck) {
      return true; 
    }
  }

  return false; 
}

// Should an Array Resize be performed

bool shouldResize(ArrayList * arrayList) {
  return getLoadFactor(arrayList) >= LOAD_FACTOR_THRESHOLD;  
}

// Resizing array method

bool resize(ArrayList* arrayList) {
  float currentCapacity = (float) arrayList->currentCapacity; 
  float growth = currentCapacity + (currentCapacity * GROWTH_FACTOR); 
  size_t newCapacity = arrayList->currentCapacity + ((size_t) growth); 

  int* newArr = (int*) malloc(newCapacity * sizeof(int));

  if(newArr == NULL) {
    printf("Error assigning the new arr to memory, as this is unexpected the program will exit\n\n");  
    exit(EXIT_FAILURE); 
  }

  memcpy(newArr, arrayList->array, arrayList->size * sizeof(int)); 


  free(arrayList->array); 
  arrayList->array = newArr; 
  arrayList->currentCapacity = newCapacity;

  return true;  
}

// All items in the array list

void show(ArrayList* arrayList) {
  bool isEmpty = getIsEmpty(arrayList);
  int size = arrayList->size; 

  if(isEmpty) {
    printf("Your array is currently empty. Perhaps add some items\n\n"); 
    return; 
  }

  if(size == 1) {
    printf("[%d]\n\n", arrayList->array[0]); 
    return; 
  }

  int i; 
  printf("["); 
  for(i = 0; i < size - 1; i++) {
    printf("%d, ", arrayList->array[i]); 
  }

  printf("%d]\n\n", arrayList->array[size - 1]);
}

void get(ArrayList* arrayList) {
  
}

void insertAtIdx(ArrayList* arrayList) {
  
}

void removeAtIdx(ArrayList* arrayList) {
  
}

void push(ArrayList* arrayList) {
  
}

void pop(ArrayList* arrayList) {
  
}

void shift(ArrayList* arrayList) {
  
}

void unshift(ArrayList* arrayList) {
  
}

void size(ArrayList* arrayList) {
  
}

void capacity(ArrayList* arrayList) {
  
}

void subList(ArrayList* arrayList) {
  
}
