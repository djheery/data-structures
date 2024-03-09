# Max Heap 

A Max Heap is a variation of a binary heap where the root note is the maximum node in the tree. 

A heap is a compete binary tree where each nodes obeys the heap property. 
In this circumstance the heap property is:

`node->value > node->left->value && node->value > node->right->value` 

Under the hood, heaps are simply vectors thus the psuedo code above does not apply but for visualization and conceptual purposes it fits

## Computing the Left, Right and Parent indexes of a Node 

As briefly mentioned above, under the hood a heap is a fixed size array or Vector. 

This means inherintly that there is no `node->left`, `node->right` and `node->parent` as there is in a normal `binary tree` 

Rather the `node->left`, `node->right` and `node->parent` are calculated mathematically

To do this is rather trivial: 

### Node left calculation 

To calculate the left child we simply do the following calculation:

`left_child(uint16_t current_idx) = (current_idx * 2) + 1` 

There are a few checks you should probably include to indicate that it has returned an out of bounds index:

```

int16_t left_child_idx(MaxHeap* heap, uint16_t current_idx) {
   uint16_t l_idx = (current_idx * 2) + 1;  

   if (l_idx >= heap->size) {
       return -1; 
   }

   return l_idx; 
}
```

Notice how we check the `heap->size` attribute of the heap to see if we are out of bounds and then return `-1` if it is. 

This is not necessary, the check could be done within the calling method; this is just my implementation

Also notice the `r_idx >= heap->size` this is only valid if we are using `0 indexing`. If you choose to implement a `1 indexed` array/vector you will forgoe the `>=` comparison operation for a `>` operation

### Right Child Index Calculation 

This is very similar to the above, apart from rather than `(current_idx * 2) + 1` we instead do `(current_idx * 2) + 2` to get the right child:

```
int16_t right_child_idx(MaxHeap* heap, uint16_t current_idx) {
    uint16_t r_idx = (current_idx * 2) + 2; 

    if (r_idx >= heap->size) {
        return -1;
    }

    return r_idx; 
}

```

### Parent Index Calculation 

To calculate the parent index it works slightly different:

`(current_idx / 2)`

```
int16_t parent_idx(uint16_t current_idx) {
    int16_t p_idx = current_idx / 2; 

    if (p_idx < 0) return - 1; // This will probably never happen

    return p_idx; 
}
```

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

To insert into a heap we insert at the right most empty leaf in the tree - This will evaluate to the end of the heap vector/array if setup properly 

We then trace up the tree by looking at the parent of the inserted node. Then check the inserted node against the heap property. 

if the inserted node is greater than the parent then we swap these nodes and keep going until the inserted node is not greater than its parent:

```
void insert(MaxHeap* heap, uint16_t node_data) {
  // Check that the heap is not null and that it is not at capacity/ take action if the load factor is reached to resize 

  heap->heap[heap->size] = initialize_node(node_data); 
  uint16_t c_idx = heap->size; 
  int16_t p_idx = parent_index(heap, c_idx); 

  Node* current = heap->heap[c_idx];
  Node* parent = heap->heap[p_idx];

  while (current->data > parent->data) {
      swap(heap->heap, c_idx, p_idx);
      c_idx = p_idx; 
      p_idx = parent_index(p_idx); 

      if (p_idx == -1) break; 

      current = parent;
      parent = heap->heap[p_idx];
  }


  tree->size += 1; 

}
```

### Extract Max

Extracting the max element of a Max Heap is the core operation one will perform when using a max heap outside of insertion. 

This method can be thought of as the delete function in a BST (Although I have implemented delete for a heap)

1. First we get the Node at the root/ index 0 of the heap 
2. We then swap index 0 and the last node in the tree 
    - 2a) Optional: Handle memory dealocation of the max node if needed in your language and you only need the data (otherwise dealocate elsewhere)
3. We then decrement the size of the heap
4. Finally we call max_heapify on the root to sift the node downward into the next position

There is some extra code that handles memory dealocation of the node we have extracted which would generally be done outside of the extract max function as it would be better to return the full node. 
But for the purpose of this example I simply return the node_data

```
uint16_t extract_max(MaxHeap* heap) {
    // Check that the heap is not null and the heap size is not 0

    // 1
    Node* max = heap->heap[0];
    uint16_t node_data = max->data; 
    
    // 2
    swap(heap->heap, 0, heap->size - 1); 

    // 2a memory dealocation
    free(max); 
    heap->heap[heap->size - 1] = NULL; // Make sure there isn't a dangling pointer 
    
    // 3 decrement heap size
    heap->size -= 1; 
    
    // Heapify the array 
    max_heapify(heap, 0); 

    return node_data;
}

```


### Deletion 

To delete an arbitrary node from the heap, the process is sub optimal. 
If you want to perform an operation like this regularly it is likely that you want to use another data structure. 

To do so you need to traverse the tree in a breadth-first manner due to the fact that a node could be anywhere in the tree as apart from the max and the min node there is no way of knowing what branch of the tree they will be in 

To accomplish this we will need a `non-priority queue` and enqueue the child nodes of the current node if the current node is not the node we are looking for. 

We will also need to store the target_node and it's index to be used later. 

When found we replace the `target_node` with `heap->heap[heap->size - 1]` and free the `target_node` as we did in the `extract_max(...)` method

After this we call `max_heapify(heap, target_index)` to make sure the tree obeys the heap property from the index of the `target_node` downwards

An example of how this may look is below: 

```
void delete_node(MaxHeap* heap, uint16_t node_data) {
    // Check the heap is not null and that the heap size is not 0

    Queue queue = initialize_queue(); 
    enqueue(&q, 0); 

    Node* target_node = NULL;
    int target_node_idx = -1; 

    while(queue.size != 0 && target_node == NULL) {
        uint16_t current_idx = dequeue(&queue);

        // Check current idx is not out of bounds

        Node* current = heap->heap[current_idx]; 

        // Check current is not NULL

        if (current->data == node_data) {
            target_index = current_idx; 
            target_node = current; 
            break;
        }

        int16_t l_idx = left_child_idx(heap, current_idx); 
        int16_t r_idx = right_child_idx(heap, current_idx); 

        if (l_idx != -1) enqueue(&queue, l_idx);
        if (r_idx != -1) enqueue(&queue, r_idx); 

    }

    if (target_node == NULL || target_node_idx == -1) return;

    swap(heap->heap, target_node_idx, heap->size - 1); 
    free(heap->heap[heap->size - 1]); 
    heap->heap[heap->size - 1] = NULL; // Address potential dangling pointer 
    heap->size -= 1; 

    max_heapify(heap, target_node_idx); 

}
```

## Use Cases 

- When you need a priority queue to be configured to give the maximum value first

## Sources

- https://www.codecademy.com/article/max-heaps-conceptual
- https://www.geeksforgeeks.org/insertion-and-deletion-in-heaps/?ref=ml_lbp
- Introduction to Algorithms (Cormen, T. *et al*) 
- A common-sense guide to Data Structures and Algorithms (Wengrow, J)
