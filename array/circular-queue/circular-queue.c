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
void front(CircularQueue* queue); 
void rear(CircularQueue* queue);
void programLoop(); 
void printMenu(); 
void printError(); 
bool validateUserInput(char* bufferPointer);
bool getIsFull(CircularQueue* queue); 
bool getIsEmpty(CircularQueue* queue); 
int getUserInput(char promptText[]); 
CircularQueue initializeQueue(int capacity); 

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
  printf("[6] Show the real front\n"); 
  printf("[7] Show the real rear\n"); 
  printf("[0] Exit the program\n\n"); 
}

void programLoop() {
  printf("=================================\n"); 
  printf("* Circular Queue Data Structure *\n"); 
  printf("=================================\n\n"); 
  
  char initializationPrompt[] = "Please enter the size of the queue you would like to initialize: "; 
  int queueCapacity = getUserInput(initializationPrompt); 

  if(queueCapacity == -1) {
    printf("Unable to initialize the queue thus the program is exiting...\n\n"); 
    printf("Goodbye...\n"); 
    return; 
  }

  CircularQueue queue = initializeQueue(queueCapacity); 

  while(true) {
    printMenu(); 
    char commandPrompt[] = "Please enter the number of the command you would like to execute: "; 
    int command = getUserInput(commandPrompt);
    printf("\n"); 

    switch(command) {
      case 1 : 
        show(&queue);
        break; 
      case 2 : 
        printf("The current size of your queue is %d\n\n", queue.size);
        break;
      case 3 : 
        enqueue(&queue);
        break; 
      case 4 :
        dequeue(&queue);
        break; 
      case 5 : 
        printf("The capacity of yoru queue is %d\n\n", queue.capacity);
        break; 
      case 6 : 
        front(&queue);
        break; 
      case 7 : 
        rear(&queue);
        break;
      case 0 : 
        printf("Ending the program...\n"); 
        printf("Goodbye!\n\n"); 
        exit(0);
        break;
      default : 
        printf("Whoops unknown command! Please try again...\n\n");
        break;
    }

  }

  free(queue.queue); 

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

void show(CircularQueue* queue) {
  bool isEmpty = getIsEmpty(queue); 

  if(isEmpty) {
    printf("Your queue is empty... why do you want to do this to me?\n\n"); 
    return; 
  }

  if(queue->size == 1) {
    printf("[%d]\n\n", queue->queue[queue->front]); 
    return; 
  }


  int currentIdx = queue->front; 
  int i; 
  printf("["); 
  for(i = 0; i < queue->size - 1; i++) {
    printf("%d, ", queue->queue[currentIdx]);
    currentIdx = (currentIdx + 1) % queue->capacity; 
  }

  printf("%d]\n\n", queue->queue[queue->rear]);
}

void enqueue(CircularQueue* queue) {
  bool isFull = getIsFull(queue); 

  if(isFull) {
    printf("Cannot enqueue any more items as your queue is full\n\n"); 
    return; 
  }
  
  queue->rear = queue->rear == (queue->capacity - 1) ? 0 : queue->rear + 1; 

  char textPrompt[] = "Please enter the number you would like to add to the queue: "; 
  int numToAdd = getUserInput(textPrompt);

  if(numToAdd == -1) {
    printf("Returning to the menu because of too many incorrect entries\n\n");  
    return;
  }

  queue->queue[queue->rear] = numToAdd; 
  queue->size += 1; 

  printf("%d added to the queue\n", numToAdd); 
  printf("Your queue now consists of %d items\n", queue->size); 
  printf("The actual front of your queue is at index: %d\n", queue->front); 
  printf("The actual rear of your queue is at index: %d\n\n", queue->rear);
}

void dequeue(CircularQueue* queue) {
  bool isEmpty = getIsEmpty(queue);

  if(isEmpty) {
    printf("Your queue is already empty so there is nothing to dequeue\n"); 
    printf("Returning to the menu...\n\n"); 
    return; 
  }

  int prevFront = queue->queue[queue->front];
  printf("The item removed is %d\n", prevFront);
  queue->size -= 1; 
  
  if(queue->size == 0) {
    queue->front = 0; 
    queue->rear = -1;

    printf("Your queue is now empty\n\n");
    return;
  }

  queue->front = queue->front == (queue->capacity - 1) ? 0 : queue->front + 1; 
  printf("Your new queue size is now %d\n", queue->size);
  printf("The actual front of your queue is at index: %d\n", queue->front); 
  printf("The actual rear of your queue is at index: %d\n\n", queue->rear);
}

void isEmpty(CircularQueue* queue) {
  bool queueIsEmpty = getIsEmpty(queue); 

  if(queueIsEmpty) {
    printf("Your queue is empty... add some items?\n\n");
    return; 
  }

  printf("Your queue is not empty, there are %d items in your queue\n\n", queue->size); 
}

void isFull(CircularQueue* queue) {
  bool queueIsFull = getIsFull(queue);  

  if(queueIsFull) {
    printf("Your queue is at capacity\n\n"); 
    return; 
  }

  printf("Your queue is not full...\n\n");
}

void front(CircularQueue* queue) {
  bool queueIsEmpty = getIsEmpty(queue); 

  if(queueIsEmpty) {
    printf("Your queue is empty, there is no front\n\n"); 
    return; 
  }

  int front = queue->queue[queue->front];
  printf("The front item of this queue is %d\n", front);
  printf("The front index of the queue is %d\n\n", queue->front); 
}

void rear(CircularQueue* queue) {
  bool queueIsEmpty = getIsEmpty(queue); 

  if(queueIsEmpty) {
    printf("Your queue is empty, there is no rear\n\n"); 
    return; 
  }

  int rear = queue->queue[queue->rear];
  printf("The rear item of this queue is %d\n", rear);
  printf("The rear index of the queue is %d\n\n", queue->rear); 
}

bool getIsEmpty(CircularQueue* queue) {
  return queue->size == 0; 
}

bool getIsFull(CircularQueue* queue) {
  return queue->size == queue->capacity;  
}
