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

// ArrayList user operations UI
void uiShow(ArrayList* arrayList); 
void uiGet(ArrayList* arrayList); 
void uiInsertAtIndex(ArrayList* arrayList); 
void uiRemoveAtIdx(ArrayList* arrayList); 
void uiPush(ArrayList* arrayList); 
void uiPop(ArrayList* arrayList); 
void uiShift(ArrayList* arrayList); 
void uiUnshift(ArrayList* arrayList); 
void uiSize(ArrayList* arrayList); 
void uiCapacity(ArrayList* arrayList);
void loadFactor(ArrayList* arrayList); 
void isEmpty(ArrayList* arrayList); 
void indexOf(ArrayList* arrayList); 
void trimToSize(ArrayList* arrayList); 
void reverse(ArrayList* arrayList); 
void contains(ArrayList* arrayList); 
void uiIsEmpty(ArrayList* arrayList); 
void uiSublist(ArrayList* arrayList); 
ArrayList clear(ArrayList arrayList); 

// Array List utility Operations 
float getLoadFactor(ArrayList* arrayList); 
bool getIsFull(ArrayList* arrayList); 
bool getIsEmpty(ArrayList* arrayList); 
bool getContains(ArrayList* arrayList, int numToCheck); 
void swap(ArrayList* arrayList, int idx1, int idx2); 
int getAtIdx(ArrayList* arrayList, int idx); 
bool listInsert(ArrayList* arrayList, int idx, int numToInsert); 
bool listRemove(ArrayList* arrayList, int idx); 
bool arrayPush(ArrayList* arrayList, int numToPush); 
bool arrayPop(ArrayList* arrayList); 
bool arrayUnshift(ArrayList* arrayList, int numToUnshift); 
bool arrayShift(ArrayList* arrayList); 
bool resize(ArrayList* arrayList); 
bool shouldResize(ArrayList* arrayList);

// General Program Methods
void programLoop(); 
void printMenu(); 
void printSubListOptions(); 
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

    if(shouldResize(&arrayList)) {
      resize(&arrayList); 
    }

    printMenu();
    char commandPrompt[] = "Please enter the number of the command you would like to perform: "; 
    int command = validateUserInput(commandPrompt);
    printf("\n");

    switch(command) {
      case 1 : 
        uiShow(&arrayList); 
        break; 
      case 2 : 
        uiGet(&arrayList); 
        break; 
      case 3 : 
        uiPush(&arrayList);
        break; 
      case 4 : 
        uiUnshift(&arrayList);
        break; 
      case 5 : 
        uiInsertAtIndex(&arrayList);
        break; 
      case 6 : 
        uiPop(&arrayList);
        break; 
      case 7 : 
        uiShift(&arrayList); 
        break; 
      case 8 : 
        printf("The current size of your array is %zu items\n\n", arrayList.size);
        break; 
      case 9 : 
        printf("The current capacity of the array is %zu items\n\n", arrayList.currentCapacity); 
        break; 
      case 10 : 
        printf("The current load factor of the array is %2.f\n\n", getLoadFactor(&arrayList));
        break;
      case 11 : 
        uiIsEmpty(&arrayList);
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
  printf("[2] Get an Item from a given index of the array\n"); 
  printf("[3] Push an Item to the Array\n"); 
  printf("[4] Unshift an Item to the array\n"); 
  printf("[5] Insert an Item into a given index\n"); 
  printf("[6] Pop an Item from the array\n"); 
  printf("[7] Shift an Item from the Array\n"); 
  printf("[8] Show the current size of the array\n"); 
  printf("[9] Show the current capacity of the array\n"); 
  printf("[10] Show the current load factor of the array\n"); 
  printf("[11] Show if the array is empty\n"); 
  printf("[12] Show the index of an item\n"); 
  printf("[13] Reverse the array\n"); 
  printf("[14] See if the array contains an item\n"); 
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
  bool isValid = false; 
  int remainingInputs = 3; 
  int userInput; 

  while(!isValid) {
    char buffer[8]; 
    printf("> %s: ", textPrompt); 
    fgets(buffer, sizeof(buffer), stdin);
    printf("\n");

    buffer[strcspn(buffer, "\n")] = 0; 

    char *p = buffer; 
    isValid = true; 

    if(isValid) {
      userInput = atoi(buffer); 
      break;
    }

    remainingInputs -= 1; 

    if(remainingInputs > 0) {
      printf("Whoops, it seems like you entered an incorrect input\n");       
      printf("We expect the input to only consist of one valid integer\n\n");
      continue;
    }

    if(remainingInputs == 0) {
      printf("Too many incorrect entries... Returning to the menu\n\n"); 
      return -1; 
    }
    
  }

  return userInput;  
}

// Validate the User input

bool validateUserInput(char* pointer) {
  while(*pointer) {
    if(!isdigit((unsigned char)* pointer)) {
      return false;
    }
    pointer++; 
  }

  return true;  
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
  bool isOutOfBounds = (idx > (arrayList->size - 1)) || (idx < 0); 
  bool isEmpty = getIsEmpty(arrayList); 
  
  if(isOutOfBounds) {
    printf("The index selected is out of bounds.\n"); 
    printf("Althought ArrayLists/Vectors can grow in size, the insertion must still be contiguous\n\n"); 
    return false; 
  }

  if(isEmpty) {
    printf("The array is currently empty, thus you cannot remove any items from it\n\n");  
    return false; 
  }

  if((arrayList->size - 1) == idx) {
    arrayList->size -= 1;  
    return true; 
  }

  int i; 
  for(i = idx; i < (arrayList->size - 1); i++) {
    int num = arrayList->array[i + 1]; 
    arrayList->array[i] = num; 
  }

  arrayList->size -= 1; 

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

  printf("Your array has been resized, the new capacity is: %zu", arrayList->currentCapacity);

  return true;  
}

// All items in the array list

void uiShow(ArrayList* arrayList) {
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

// Get the number at a given idx

int getAtIdx(ArrayList* arrayList, int idx) {
  bool isEmpty = getIsEmpty(arrayList);  
  bool isOutOfBounds = idx > (arrayList->size - 1); 

  if(isEmpty) {
    printf("Your array is empty, thus there is nothing to get\n\n");  
    return -1; 
  }

  if(isOutOfBounds) {
    printf("The index selected is out of bounds of the current array\n\n"); 
    return -1; 
  }

  int numAtIdx = arrayList->array[idx];

  return numAtIdx; 
}

// get the current capacity of the ArrayList 

int getCapacity(ArrayList* arrayList) {
  return arrayList->currentCapacity;
}

// Swap method

void swap(ArrayList* arrayList, int idx1, int idx2) {
  int temp = arrayList->array[idx1]; 
  arrayList->array[idx1] = arrayList->array[idx2]; 
  arrayList->array[idx2] = temp;
}

// Clear/ Reset the array to its initialization form

ArrayList clear(ArrayList arrayList) {
  free(arrayList.array);  
  return initializeArrayList();
}

// Reverse the Array -> This reverals persists and is not a temporary clone

void reverse(ArrayList* arrayList) {
  if(getIsEmpty(arrayList)) {
    printf("Your array is currently empty\n\n"); 
    return;
  }

  int end = arrayList->size - 1; 
  int start = 0; 

  if(start == end) {
    printf("Your array is only one item in length\n\n"); 
    return; 
  }

  printf("Before:\n"); 
  uiShow(arrayList);

  while(start < end) {
    swap(arrayList, start, end);
    start++; 
    end--;
  }

  printf("After\n"); 
  uiShow(arrayList); 
}

// Array Push

bool arrayPush(ArrayList* arrayList, int numToPush) {
  arrayList->array[arrayList->size] = numToPush; 
  arrayList->size += 1; 
  return true;  
}

// Pop from the array 
// This works by simply decrementing the size and allowing the rear of the array to be written too 
// Other methods could be used such as assigning the array at the rear index to a value that indicates null if you wish to remove the item completley
// I did not feel it was necessary in this circumstance

bool arrayPop(ArrayList* arrayList) {
  arrayList->size -= 1; 
  return true;  
}

// Unshift to the array (Add an element to the start) 

bool arrayUnshift(ArrayList* arrayList, int numToUnshift) {
  bool isEmpty = getIsEmpty(arrayList); 

  if(isEmpty) {
    arrayList->array[0] = numToUnshift; 
    arrayList->size += 1; 
    return true; 
  }

  int i; 
  int nextNum = arrayList->array[0];

  for(i = 0; i < arrayList->size - 1; i++) {
    if(i == 0) {
      arrayList->array[i] = numToUnshift;
    } else {
      arrayList->array[i] = nextNum; 
      nextNum = arrayList->array[i + 1]; 
    }
  }

  arrayList->size += 1; 

  return true;  
}

// Shift the 0 idx item from the array

bool arrayShift(ArrayList* arrayList) {
  bool isEmpty = getIsEmpty(arrayList); 

  if(isEmpty) {
    printf("Your array is Empty thus no items can be removed\n\n");  
    return false; 
  }

  int i; 
  for(i = 1; i < arrayList->size; i++) {
    arrayList->array[i - 1] = arrayList->array[i];  
  }

  return true;  
}

// Get an item at a given index

void uiGet(ArrayList* arrayList) {
  bool isEmpty = getIsEmpty(arrayList); 

  char textPrompt[] = "What index of the array would you like to get?: ";
  int idx = getUserInput(textPrompt);

  if(idx == -1) {
    return;  
  }

  int num = getAtIdx(arrayList, idx);

  if(num == -1) return;

  printf("Index selected: %d\n", idx); 
  printf("The number at index %d, is: %d\n\n", idx, num); 
}

// Insert a given number at an index

void uiInsertAtIndex(ArrayList* arrayList) {
  char textPrompt[] = "What index would you like to insert at?: ";  
  int idx = getUserInput(textPrompt);

  char textPrompt2[] = "What number would you like to insert?: "; 
  int numToInsert = getUserInput(textPrompt2);

  if(idx == -1 || numToInsert == -1) {
    printf("Unfortunately you entered some shit incorrectly\n\n"); 
    return; 
  }

  bool hasInserted = listInsert(arrayList, idx, numToInsert);  

  if(!hasInserted) printf("The number you entered has failed to be inserted\n\n"); 
  if(hasInserted) printf("%d has been successfully inserted at index %d\n\n", numToInsert, idx);
}

// Remove an item at a given index

void uiRemoveAtIdx(ArrayList* arrayList) {
  char textPrompt[] = "What index would you like to remove?: ";  
  int idx = getUserInput(textPrompt);

  if(idx == -1) {
    printf("soz i dnt kno wat iz happenin\n\n"); 
    return; 
  }

  bool hasInserted = listRemove(arrayList, idx);
  
  if(!hasInserted) printf("The index you entered has failed to be removed\n\n");
  if(hasInserted) printf("Index %d has been removed and the list has been resized\n\n", idx);
}

void uiPush(ArrayList* arrayList) {
  
}

void uiPop(ArrayList* arrayList) {
  
}

void uiShift(ArrayList* arrayList) {
  
}

void uiUnshift(ArrayList* arrayList) {
  
}

void uiSize(ArrayList* arrayList) {
  
}

void uiCapacity(ArrayList* arrayList) {
  
}

void uiSublist(ArrayList* arrayList) {
  
}

void uiIsEmpty(ArrayList* arrayList) {
  if(getIsEmpty(arrayList)) {
    printf("Your array is empty\n\n"); 
  } else {
    printf("Your array is not empty\n\n"); 
  }
}

bool getIsEmpty(ArrayList* arrayList) {
  return arrayList->size == 0;  
}

bool getIsFull(ArrayList* arrayList) {
  return arrayList->size == arrayList->currentCapacity;  
}
