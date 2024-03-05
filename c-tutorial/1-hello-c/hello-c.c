#include <stdio.h>
#include <stdbool.h>

int addNums(int x, int y) {
  return x + y; 
}

void typeWeirdity() {
  float sum =  5 / 2; // Should be 2.5
  printf("%f\n", sum); // This will be odd

  // To fix the wierdity
  sum = 5.0 / 2.0; 
  printf("%f\n", sum); // This won't be weird anymore
}

void typeConversion() {
  float myFloat = (float) 15; 
  printf("%f\n", myFloat); // This will convert the output to decimal places 
  int myInt = (int) 9.99;
  printf("%d\n", myInt); // This will convert the output to a rounded integer (9)
}

void constants() {
  const int SOMETHING = 14; // This defines a constant 
}

void booleans() {
  printf("Booleans are their own type included in <stdbool.h> from C99 onwards\n");  
  bool isTrue = true; 

  printf("Is true? => %b\n", isTrue); // Expected output is 1 for true 0 for false 
}

void conditionals() {
  const int MY_NUM = 10;

  if (MY_NUM < 10) {
    printf("My Num is Less than 10: %d\n", MY_NUM); 
  } else {
    printf("My Num is Greater than or equal to 10 => MY_NUM: %d\n", MY_NUM); 
  }
}

void loopMeDaddy() {
  printf("For Loops\n");
  int i; 
  for (i = 0; i < 5; i++) {
    printf("i == %d\n", i);  
  }

  printf("while loop\n"); 
  bool isTrue = false; 
  int loopCounter = 0;
  while (loopCounter < 5) {
    loopCounter % 2 == 0 
      ? printf("%d is divisible by 2\n", loopCounter) 
      : printf("%d is not divisible by 2\n", loopCounter); 

    loopCounter += 1; 
  }

  printf("Loop ended at counter %d\n", loopCounter); 
}

void arrays() {
  int myArr[] = {14, 20, 25, 55, 200, 123, 1234, 123, 123, 12312, 12331}; 
  long arrLenSizeOf = (long) sizeof(myArr) / sizeof(myArr[0]); 
  long arrLenPointer = (long) (*(&myArr + 1) - myArr); 
  printf("Array size = %ld\n", arrLenPointer); 
  int i; 
  for (i = 0; i < arrLenSizeOf; i++) {
    printf("Item at index %d => %d\n", i, myArr[i]);  
  }
}


int main() {
  int myNum = 15; 
  printf("My num => %d\n", myNum); 
  printf("Hello World!i\n"); 
  printf("You are a bitch!\n"); 
  printf("A can add numbers = %d\n", addNums(2, 4)); 
  printf("---Type conversion---\n"); 
  typeConversion(); 
  printf("---Type Weirdity---\n");
  typeWeirdity();
  printf("---Booleans---\n"); 
  booleans();
  printf("---Conditionals---\n"); 
  conditionals(); 
  printf("---Loops---\n"); 
  loopMeDaddy();
  printf("---Arrays---\n"); 
  arrays();
  return 0; 
}

