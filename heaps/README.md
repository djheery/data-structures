# Heaps 

Heaps are a complete binary tree data structure.

The property of a heap is: 

For every node `x` the value of `x` is either: 

- less or equal to its children (min-heap) 
- greater than or equal to its children (max-heap)

To represent this using psuedo-code: 

- `min_heap = value(x) <= x->right && value(x) <= x->left` 
- `max_heap = value(x) >= x->right && value(x) >= x->left` 

Heaps are often used to implement prority queues, where the smallest (or larges) element is always at the root of the tree

## Properties of a Heap

Below are some of the properties of a heap:

1. The heap is a complete binary tree 
2. The heap property is maintained such that the minimum or maximum element is always at the root of the tree depending on the heap type 
3. Efficient Insertion and Removal
    - Insertion and removal operation in heap trees are efficient. New elements are inserted at the next available positon in the bottom-rigthmost level
    - The heap property is then restored by comparison of the inserted node with it's parent and swapping when necessary
4. Removal of the root element involves replacing it with the last element and heapifying downward through the tree
5. Efficient Access to Extremal elements: The minimum or maximum element is always the root of the heap allowing for constant time access. 

## Complete Binary Tree 

A complete binary tree is a type of binary tree where all of the tree levels are completley filled - apart from the lowest level which are filled as much as possible.

When filling the tree a queue will be used procedurally implementing elements from left to right 

It may look something like this when implementing *WITHOUT HEAP CONSTRAINTS*: 
```

    void insert(CompleteTree* tree, int node_data) {
        Node* new_node = initialze_node(node_data); 
        Queue q = initialize_queue(); 
        enqueue(&q, tree->root); 

        while(q.size != 0) {
            Node* current = dequeue(&q);

            if (current->left == NULL) {
                current->left = new_node; 
                break; 
            }

            enqueue(&q, current->left); 

            if (current->right == NULL) {
                current->right = new_node; 
                break;
            }

            enqueue(&q, current->right); 
        }

        free(q.queue); 
    }

```

## Varying types of Heap 

There are varying versions of the heap Data Structure which suit differing scenarios.

Some examples of other types of heap data structures are:

- Min Heap
- Max Heap
- Min-Max Heap
- Priority Queue 
- Binomial Heap
- Fibonacci Heap 

## Advantages and Disadvantages of Heaps 

Below are some advantages and disadvantages that I have seen on GeeksForGeeks (Source at the bottom) 

### Advantages 

- Fast access to extremal elements O(1) 
- Efficient Insertion and Deletion Operations O(log n)
- Can be efficiently implemented as an Array 
- Suitable for Real-time Applications

### Disadvantages 

- Not suitable for searching non-extremeal elements - Can be O(n) in worst cases)
- There is extra memory overhead for maintainance of the heap data structure 
- Slower than alternative data structures when not used in the right circumstance like arrays, linked lists & non-priority queue operations. 

## Sources

- https://en.wikipedia.org/wiki/Heap_(data_structure)
- https://www.geeksforgeeks.org/heap-data-structure/
- https://www.geeksforgeeks.org/complete-binary-tree/




