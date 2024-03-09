# Max Heap 

A Max Heap is a variation of a binary heap where the root note is the maximum node in the tree. 

A heap is a compete binary tree where each nodes obeys the heap property. 
In this circumstance the heap property is:

`node->value > node->left->value && node->value > node->right->value` 

Under the hood, heaps are simply vectors thus the psuedo code above does not apply but for visualization and conceptual purposes it fits

## Computing the Left, Right and Parent indexes of a Node 

## Operations 

Below are some of the operations that are implemented in the coresponding `max-heap.c` file

### Max Heapify 

Max heapify aims to take a heap and a given index and make sure that the max heap property is satisfied. 

Starting at idx `n` we compare the `heap[n]->value` to `heap[n]->left` and `heap[n]->right`. 

The largest value at { `heap[n]`, `heap[n]->left`, `heap[n]->right` } gets their index stored in a `largest_index` variable. 

If `index != n` then we use a utility method called `swap(MaxHeap* heap, uint i, uint j)` to swap the nodes in place

Also if `index != n` as above we continue to recurse down the tree by calling `max_heapify(heap, largest_idx)` until the node finds its place in the tree/vector 

Remember the `largest_index` at this point will represent where node `n` has been swapped too

Below is an example of the code involved: 

```

void max_heapify(MaxHeap* heap, uint16_t current_idx) {
    // Check the heap for the circumstance the heap is null

    int16_t l_idx = left_idx(MaxHeap* heap, current_idx); 
    int16_t r_idx = right_idx(MaxHeap* heap, current_idx); 
    uint16_t largest_idx = current_idx; 
    
    Node* largest = heap->heap[largest_idx]; 
    Node* left = l_idx == -1 ? NULL : heap->heap[l_idx]; 
    Node* right = r_idx == -1 ? NULL : heap->heap[r_idx];

    if (left != NULL && left->data > largest->data) {
        largest_idx = l_idx; 
        largest = heap->heap[largest_idx];
    }

    if (right != NULL && right->data > largest->data) {
        largest_idx = r_idx; 
        largest = heap->heap[largest_idx];
    } 

    if (current_idx != largest_idx) {
        swap(heap->heap, current_idx, largest_idx); 
        max_heapify(heap, largest_idx); 
    } 

}

void swap(Node** heap, uint16_t i, uint16_t j) {
    Node* temp = heap[i]; 
    heap[i] = heap[j]; 
    heap[j] = temp; 
}

```

A note on the swap method:

This method is a very standard swap method used as a utility function in many algorithms. 
If it is not obvious, this swap is done in place and it does not need to return a new heap as it manipulates the passed in heap implicitly due to the pass by reference nature of vectors/arrays  

### Insertion 

### Extract Max

### Deletion 

### Peek 

### Build Heap 

## Use Cases 

## Sources

- https://www.codecademy.com/article/max-heaps-conceptual
