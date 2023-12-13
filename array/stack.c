#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
  int* stack; 
  int size; 
  int capacity;
} Stack; 

void length(Stack* stack); 
void capacity(Stack* stack); 
void push(Stack* stack);  
void pop(Stack* stack);
void show(Stack* stack);
void programLoop(); 
int initializeStack(); 
void printMenu();

int main() {
  programLoop(); 
  return 0; 
}

void programLoop() {
  printf("========================\n"); 
  printf("* Stack Data Structure *\n"); 
  printf("========================\n\n"); 
  printf("Note: There is currently no error handling for input that is not an integer\n\n"); 

  int stackSize = initializeStack();  
  Stack stack; 
  stack.size = 0; 
  stack.capacity = stackSize; 
  stack.stack = (int*) malloc(stack.capacity * sizeof(int)); 

  while(true) {
    int command;
    printMenu(); 
    scanf("%d", &command);  
    printf("\n"); 

    switch(command) {
      case 0 :
        exit(0);
        break; 
      case 1 : 
        show(&stack); 
        break;
      case 2 : 
        length(&stack); 
        break; 
      case 3 : 
        push(&stack); 
        break; 
      case 4 : 
        pop(&stack);
        break; 
      case 5 : 
        capacity(&stack);
        break;
      default : 
        printf("Unknown Command! Please try again\n\n"); 
    }

    usleep(10000);

  }

  free(stack.stack); 
}

int initializeStack() {
  printf("The stack will be limited to integers only\n\n"); 
  printf("> Please initialize your stack with a size: "); 
  long stackSize; 
  scanf("%ld", &stackSize);
  printf("\n\n"); 

  return stackSize;
}

void printMenu() {
  printf("Please select the operation you would like to perform\n\n"); 
  printf("[1] Show the stack\n"); 
  printf("[2] Show the length of the stack\n"); 
  printf("[3] Push to the stack\n"); 
  printf("[4] Pop from the stack\n"); 
  printf("[5] Show Stack Capacity\n"); 
  printf("[0] Exit the program\n\n"); 

  printf("Command number: "); 
}

void show(Stack* stack) {
  int size = stack->size;
  if(size == 0) {
    printf("There is nothing in your stack to show!\n\n"); 
  } else if (stack->size > 1) {
    int i; 
    printf("Showing Stack Contents\n\n"); 
    printf("[");
    for (i = 0; i < stack->size - 1; i++) {
      printf("%d, ", stack->stack[i]); 
    }

    printf("%d]\n\n", stack->stack[stack->size - 1]); 
  } else {
    // There is only one element in the stack
    printf("[%d]\n\n", stack->stack[0]);
  }
}

void length(Stack* stack) {
  int size = stack->size;
  if(size == 0) {
    printf("There is nothing in your stack!\n\n"); 
  } else {
    printf("Stack contains: %d items\n\n", stack->size); 
  }
}

void capacity(Stack* stack) {
  float size = (float) stack->size; 
  float capacity = (float) stack->capacity;
  float fullPercentage = (float) (size / capacity) * 100; 

  printf("The total capacity of your stack is %d items\n", stack->capacity); 
  printf("The percentage your stack is full is %.2f%%\n\n", fullPercentage); 
}

void push(Stack* stack) {
  if(stack->size == stack->capacity) {
    printf("Any more items will overflow the stack!i\n");
  } else {
    int newNum; 
    printf("> Enter the number you want to add to the stack: ");
    scanf("%d", &newNum); 
    printf("\nAdding Number...\n\n");
    stack->stack[stack->size] = newNum; 
    stack->size += 1;
    printf("%d sucessfully added to the stack\n\n", newNum);
  }
}

void pop(Stack* stack) {
  if((stack->size - 1) < 0) {
    printf("Cannot remove any more items from the stack as it is already empty\n\n"); 
    return; 
  }

  stack->size -= 1;
  printf("Stack size decremented meaning that the next element pushed will overwrite the previous element\n\n"); 
  
}
