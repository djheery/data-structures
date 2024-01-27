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
3. Red nodes cannot be proceeded or preceeded by another red node 
4. Every path from a node to any of its leaf nodes has the same number of black nodes
5. Every Leaf is colored black 
6. The black height is the number of black does on a path from root to leaf

## Methods 

The implementation of red black tree is a fair amount more complex than a normal BST (discounting search as it is the same) 



## Applications

1. Most of the self-balancing BST library functions in languages like Java (java.util.TreeMap & java.util.TreeSet) an implementation of a red Black Trees
2. They are used to implement CPU scheduling in Linux (Perhaps I could build something like this) 
3. Use in the K-Mean clustering algorithm for Reducing the Time Complexity 
4. MySQL uses RBTs for indexing on tables 
5. RBTs are used in graph algorithms like Dijkstras and Prims Min Spanning Tree 

## Advantages 

1. A guarneteed time complexity of O(log n) in basic operations - Insertions, Deletions and Searching 
2. They are Self Balancing which helps preserve the O(log n) time complexity #

## Disadvantages 

1. RBTs require a little bit more storage for each node, thus Memory usage is larger 
2. The complexity of the implementation can be a turn off 
3. They may not be the best choice for usecases where Insertions and Deletions are not frequent (for this maybe an AVL tree is better) 



