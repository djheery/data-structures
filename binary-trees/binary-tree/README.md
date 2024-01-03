# Binary Tree 

Binary trees are tree like data structures. 
They can be visually represented like below: 

```
       10 
      /  \
     20  12 
    /  \  
   15  10
```

As should be clear by the diagram above a tree consists of Nodes which have a left and a right pointer. 

The top of the tree is generally referred to as the root where the nodes with no children are reffered too as leaves. 

The basic type of binary tree (which we are creating here) is not to be confused with something like a Binary search tree. 

A Binary Search Tree is more commonly used as their are ordering constraints on the node of the tree. For this section we are not focusing on this rather just the general binary tree. 

Each node in a binary tree will generally have a left and a right child. When there is no left or right child these unassigned nodes will be initialized to NULL. 

Nodes are assigned to the Heap and have the following general structure: 

```
Node {
  <T> data 
  Node* left 
  Node* right 
}
```

The as you can see the left and right sub nodes act as pointers to the next node and the data of type `<T>` is the data stored within the node. 

You may also have a wrapper class for the Binary Tree that could look something like this: 

```
Binary Tree {
    Node* root,
    i32 height 
    i32 size 
} 
```

The structure above contains a pointer too the root or head of the tree. Then there are a couple of other attributes being `height` and `size` 

## Attributes 

Below are some of the attributes of a Binary Tree

### Height 

Height refers to the number of edges, levels or verticies from the root node to the deepest node. For example the height of the tree in the topmost diagram is 2. 
The root is considered 0. Thus the traversal to the deepest node would be: 10 => 20 => 15 (it could also be 10) 
The height can also be refered to as depth. 

### Size 

The size of a binary tree is very simply the number of nodes in the binary tree.
For example the size of the binary tree in the topmost example is: 5

### Level 

The level of the binary tree refers to the current level (For example node 20 is at level 1, node 15 is at level 2) The root is normally considered to be of level 0 

## Properties of a Binary Tree

This information has been taken and reworded from: https://www.geeksforgeeks.org/properties-of-binary-tree/

1. The maximum number of nodes at level (L) of a binary tree is 2^L
    - For example: (L = 3) thus maximum nodes at the final level would be = 8 (2 * 2 * 2 == 2^3);
    - for the root assume l = 0, and the number of nodes for 2^0 = 1; 
2. The maximum number of nodes of a binary tree of height (H) is (2^H - 1) 
    - For example: (H = 5) thus the maximum nodes given H = 31 ((2 * 2 * 2 * 2 * 2) - 1) 
3. In a Binary Tree with N nodes, the minimum possible height/ levels is Log2(N+1)
    - For example: (N = 13), the minimum height/levels = 4
    - I need to do more research on the math behind Log2 
4. A binary tree with L leaves has at least | Log2L | + 1 levels 
    - For example (L = 4) this means the least number of levels is 2

## Use Cases 

This information has been taken and reworded from: https://www.geeksforgeeks.org/properties-of-binary-tree/

Some applications of Binary Trees (Mainly their sub types) include: 

- Search algorithms 
- Sorting Algorithms 
  - Binary Search Tree sort 
  - Heap Sort 
- Database systems 
  - Each node in the tree can represent a record, and utilizing search operations to find said records 
- File Systems 
  - Binary trees can be used to implement file systems where each node represents a directory or file
- Compression Algorithms 
  - Huffman encoding trees to compress and assign variable-length codes to characters based on their frequency of occurence in the input data 
- Decision Trees 
  - A type of Machine learning algorithms used for classification and regression analysis 
- Game AI 
  - Each node can represent a possible move in the game, where the tree will be used to find the bbest possible move. 

### Advantages 

This mainly applies to their sub types (BST, AVL Tree, Red Black tree etc) 

- Efficient searching: Binary trees are particularly efficient when searching for a specific element, as each node has at most two child nodes, allowing for bbinary search algorithms to be used.  
  - This means that search operations can be performed in O(log n) time
- Ordered Treaversal 
  - The structure of binary trees enables them to be traversed in a specific order
- Memory Efficient 
  - Compared to other tree structures they are relatively memory efficient because they only require two child pointers per node. 
  - This allows for large amount of data storage whilst maintaining efficient search 
- Fast Insertion and Deletion 
  - This is the same with Search O(log n) 
- Easy to implement 

### Disadvantages 

- Limited Structure 
    - Due to the limitation of two child nodes per node, their usecase can be limited for certain applications
- Unbalanced Trees
    - Unbalanced trees, where one subbtree is significantly larger than the other can lead to inefficient search operations
- Space Inefficency
    - BBinary trees can be space inefficient because each node requires two child pointers, which can be significant amount of memory overhead for particularly large trees 
- Slow Performance in worst case scenarios 
    - The worst case can be O(n) if the tree structure is not correctly balanced 
- Complex Balancing algorithms 
    - To ensure a tree remains balanced, various algorithms can be used such as AVL Trees and Red Black trees bbut these alogrithms can be more complex to implement and require additional overhead, making them less suitable for some applications. 

## Methods 

Below are the methods used in the `binary-tree.c` file
It is worth noting that this file is just for a very basic implementation of a bianry tree with no balancing 

### Insert 

Simply insert a node when it finds a node with a left or right child as NULL 
The priority is to insert at the left most node first

### Delete 

1. Find the right most node 
2. Find the target node 
3. Replace the data in the target node with the data found from the right most node 
4. Remove the right most node (Set it to NULL and free from memory) 

### Search 

1. Use a tree walk to keep searching until it finds the first occurence of a node 
2. If found return true else return false 

### Pre Order Tree Walk 

### In Order Tree Walk 

### Post Order Tree Walk 

## Other Types of Trees 

- Degenerate Binary Tree 
- Full Binary Tree 
- Skewed Binary Tree 
- Complete Binary Tree 
- Perfect Binary Tree 
- Balanced Binary Tree 

The below items will be created within this section of the project at some point 

- Binary Search Tree 
- AVL Tree 
- Red Black Tree 
- B+ Tree 
- B Tree 
- Segment Tree 

