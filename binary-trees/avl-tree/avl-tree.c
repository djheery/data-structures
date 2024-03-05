#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node; 

typedef struct Node {
  int32_t data; 
  Node* left; 
  Node* right; 
} Node; 

typedef struct {
  Node* root; 
  uint16_t size; 
} AVLTree; 

typedef struct {
  uint16_t front; 
  uint16_t rear;
  uint16_t capacity; 
  uint16_t length; 
} CircularQueue; 

int main() {
  return 0; 
}
