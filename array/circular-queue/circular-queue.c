#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  int* queue; 
  int size; 
  int capacity; 
  int front; 
  int rear;
} CircularQueue;

void show(CircularQueue* queue); 
void enqueue(CircularQueue* queue); 
void dequeue(CircularQueue* queue); 
void peek(CircularQueue* queue); 
void showIsEmpty(CircularQueue* queue); 
void showIsFull(CircularQueue* queue); 
void programLoop(); 
void printMenu(); 
void printError(); 
bool validateUserInput(char* bufferPointer);
bool getIsFull(CircularQueue* queue); 
bool getIsEmpty(CircularQueue* queue); 
int getUserInput(char promptText[]); 
CircularQueue initializeQueue(int capacity); 

int main() {
  return 0; 
}

void printMenu() {
  printf("Please select the operation you would like to perform\n\n"); 
  printf("[1] Show the queue\n"); 
  printf("[2] Show the length of the queue\n"); 
  printf("[3] Enqueue item\n"); 
  printf("[4] Dequeue Item\n"); 
  printf("[5] Show Queue Capacity\n"); 
  printf("[6] Show the real front\n"); 
  printf("[7] Show the real rear\n"); 
  printf("[0] Exit the program\n\n"); 
}

void programLoop() {
  printf("=================================\n"); 
  printf("* Circular Queue Data Structure *"); 
  printf("=================================\n\n"); 
  
  char initializationPrompt[] = "Please enter the size of the queue you would like to initialize: "; 
  int queueCapacity = getUserInput(initializationPrompt); 

  if(queueCapacity == -1) {
    printf("Unable to initialize the queue thus the program is exiting...\n\n"); 
    printf("Goodbye...\n"); 
    return; 
  }

  CircularQueue queue = initializeQueue(queueCapacity); 

}

void printError() {
  printf("Too many incorrect entries - We are expecting an integer\n\n"); 
}

int getUserInput(char textPrompt[]) {
  bool isValid = false; 
  int remainingInputs = 3; 
  int userInput;

  while(!isValid) {

    char buffer[7]; 
    printf("> %s", textPrompt); 
    fgets(buffer, sizeof(buffer), stdin);
    printf("\n");

    buffer[strcspn(buffer, "\n")] = 0; 

    char *bufferPointer = buffer; 
    isValid = validateUserInput(bufferPointer);

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
      printError();
      return -1;  
    }
  }

  return userInput;  
}

bool validateUserInput(char *bufferPointer) {
  while(*bufferPointer) {
    if(!isdigit((unsigned char)* bufferPointer)) {
       return false;       
    }

    bufferPointer++;
  }
  return true; 
}

CircularQueue initializeQueue(int capacity) {
  CircularQueue queue; 
  queue.size = 0; 
  queue.capacity = capacity; 
  queue.front = 0; 
  queue.rear = -1; 
  queue.queue = (int*) malloc(capacity * sizeof(int)); 

  return queue; 
}
