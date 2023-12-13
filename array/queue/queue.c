#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct {
  int* queue; 
  int size;
  int capacity; 
} Queue;

void show(Queue* queue); 
void enqueue(Queue* queue); 
void dequeue(Queue* queue); 
void peek(Queue* queue); 
void isFull(Queue* queue); 
void isEmpty(Queue* queue); 
void programLoop(); 
void printMenu(); 
Queue initializeQueue(int capacity); 
int validateUserInput(char text[]); 
bool getIsEmpty(Queue* queue); 
bool getIsFull(Queue* queue); 

int main() {
  programLoop(); 
  return 0; 
}

void printMenu() {
  printf("Please select the operation you would like to perform\n\n"); 
  printf("[1] Show the queue\n"); 
  printf("[2] Show the length of the queue\n"); 
  printf("[3] Enqueue item\n"); 
  printf("[4] Dequeue Item\n"); 
  printf("[5] Show Queue Capacity\n"); 
  printf("[0] Exit the program\n\n"); 

}

void programLoop() {
  printf("========================\n"); 
  printf("* Queue Data Structure *\n"); 
  printf("========================\n\n"); 
  char text[] = "Please enter the size of the queue you want to intialize: "; 
  int capacity = validateUserInput(text); 

  if(capacity == -1) {
    printf("Unable to initialize the array so exiting the program...\n\n"); 
    usleep(50000);
    printf("Goodbye\n\n");
    return; 
  }

  Queue queue = initializeQueue(capacity);

  while(true) {
    printMenu();  
    char commandPrompt[] = "Enter the number of the command you would like to perform: "; 
    int command = validateUserInput(commandPrompt); 
    printf("\n"); 

    switch(command) {
      case 1 : 
        show(&queue);  
        break; 
      case 2 : 
        printf("Current queue length is: %d items\n\n", queue.size); 
        break; 
      case 3 : 
        enqueue(&queue); 
        break; 
      case 4 : 
        dequeue(&queue);
        break; 
      case 5 : 
        printf("Your queue capacity is: %d items\n\n", queue.capacity);
        break; 
      case 0 : 
        exit(0); 
        break;
      default: 
        printf("Unknown command, please try again\n\n"); 
    }
  }

  free(queue.queue); 
}

void show(Queue* queue) {

  if(getIsEmpty(queue)) {
    printf("Your queue is currently empty you doilem\n\n"); 
    return; 
  }

  if(queue->size == 1) {
    printf("[%d]\n\n", queue->queue[0]); 
    return; 
  }

  int i;
  printf("["); 

  for(i = 0; i < queue->size - 1; i++) {
    printf("%d, ", queue->queue[i]);  
  }

  printf("%d]\n\n", queue->queue[queue->size - 1]); 
  
}

void enqueue(Queue* queue) {
  if(getIsFull(queue)) {
    printf("You cannot enqueue any more items as the queue is full. Dickhead!\n\n");  
    return; 
  }

  char textPrompt[] = "Enter the number you would like to add to the queue"; 
  int numToAdd = validateUserInput(textPrompt); 

  if(numToAdd == -1) {
    printf("Invalid number tried to be added. We need positive Integers\n\n");   
    return;
  }

  int size = queue->size; 
  queue->queue[size] = numToAdd; 
  queue->size += 1;

  printf("Item added at the back of the queue, loser. Item: %d\n\n", numToAdd); 
}

void dequeue(Queue* queue) {

  if(getIsEmpty(queue)) {
    printf("Cannot dequeue any more items, your queue is empty\n\n");  
    return; 
  }

  int i; 
  int frontItem = queue->queue[0]; 

  printf("Dequeuing the item at the front of the queue: %d\n\n", frontItem); 

  for(i = 0; i < queue->size; i++) {
    queue->queue[i] = queue->queue[i + 1]; 
  }

  queue-> size -= 1;

  printf("Item sucessully dequeued, your current queue size is %d\n\n", queue->size); 
}

void peek(Queue* queue) {
   bool queueIsEmpty = getIsEmpty(queue); 

   if(queueIsEmpty) {
     printf("Your queue is empty, there is nothing to peek at. You pervert\n\n"); 
     return; 
   }

   printf("The front of your queue is: %d\n\n", queue->queue[0]); 
}

void isFull(Queue* queue) {
  bool queueIsFull = getIsFull(queue);  

  if(!queueIsFull) {
    printf("Your queue is not full. There are %d items in your queue!\n\n", queue->size); 
    return;  
  }

  printf("Your queue is completley full, stop trying to put more items in dickhead\n\n"); 
}

void isEmpty(Queue* queue) {
  bool queueIsEmpty = getIsEmpty(queue);  

  if(!queueIsEmpty) {
    printf("Your queue is not empty, there are %d items in your queue!\n\n", queue->size); 
    return; 
  }

  printf("Your queue is infact empty. Why not add some items? Idiot.\n\n");
}

bool getIsEmpty(Queue* queue) {
  return queue->size <= 0; 
}

bool getIsFull(Queue* queue) {
  return queue->size == queue->capacity; 
}

void printError() {
  printf("Too many incorrect entries - We are expecting an integer\n\n");  
}

Queue initializeQueue(int capacity) {
  Queue queue; 
  queue.size = 0; 
  queue.capacity = capacity; 
  queue.queue = (int*) malloc(capacity * sizeof(int)); 
  
  return queue; 
}

bool stringIsValid(char* p) {
    bool isValid = false; 
    while(*p) {
      if(!isdigit((unsigned char)* p)) {
        printf("%s", p); 
        return isValid;  
      }

      p++;
    }

    return true; 
}

int validateUserInput(char text[]) {
  bool isValid = false; 
  int maxIncorrectEntries = 3; 
  int userInput; 

  while(!isValid) {
    if(maxIncorrectEntries == 0) {
      printError();
      return -1; 
    }

    char buffer[7]; 
    printf("> %s ", text); 
    fgets(buffer, sizeof(buffer), stdin); 
    
    buffer[strcspn(buffer, "\n")] = 0; 

    char *p = buffer;
    isValid = stringIsValid(p);
    
    if(isValid) {
      userInput = strtol(buffer, NULL, 10); 
      break; 
    }
    
    maxIncorrectEntries -= 1;
    printf("\n"); 
  }

  return userInput; 
}

