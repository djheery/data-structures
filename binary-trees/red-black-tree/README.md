# Red-Black Tree 

This information consists of notes taken from: https://www.geeksforgeeks.org/introduction-to-red-black-tree/

The Red Black Tree is an expansion of the Binary Search Tree. 

The Binary Search Tree is great for sorting data however, the search function is highly dependent on the shape of the tree.

When the shape of the tree has atrophied the tree can degerate into a linear structure with a time complexity of O(n)

Red Black Trees address this problem by self-balancing on insertion and deletion. Ensuring the tree is balanced is a preventative measure 
to stop the tree degerating into a linear structure and preserving the average O(log n) search time 

## Rules and properties of a Red-Black Tree

1. Every node has a color (Red or Black) 
2. The root is always black 
3. There red nodes cannot be proceeded or preceeded by another red node 
4. Every path from a node to any of its leaf nodes has the same number of black nodes
5. Every Leaf is colored black 
6. The black height is the number of black does on a path from root to leaf

## Methods 

The implementation of red black tree is a fair amount more complex than a normal BST (discounting search as it is the same) 

## Applications

## Advantages 

## Disadvantages 

