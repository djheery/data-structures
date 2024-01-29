# Red-Black Tree 

This information consists of notes taken from: https://www.geeksforgeeks.org/introduction-to-red-black-tree/

The Red Black Tree is an expansion of the Binary Search Tree. 

The Binary Search Tree is great for sorting data however, the search function is highly dependent on the shape of the tree.

When the shape of the tree has atrophied the tree can degerate into a linear structure with a time complexity of O(n)

Red Black Trees address this problem by self-balancing on insertion and deletion. Ensuring the tree is balanced is a preventative measure 
to stop the tree degerating into a linear structure and preserving the average O(log n) search time 

## Rules and properties of a Red-Black Tree

1. Every node has a color (Red or Black) 2. The root is always black 3. Red nodes cannot be proceeded or preceeded by another red node 4. Every path from a node to any of its leaf nodes has the same number of black nodes 5. Every Leaf is colored black 6. The black height is the number of black does on a path from root to leaf ## Methods 

The implementation of red black tree is a fair amount more complex than a normal BST (discounting search as it is the same) 

## Insertion 

When inserting into a RBT there are two balancing tools used after the initial insertion: 

1. Recoloring
2. Rotation 

### Recoloring 

Recolring is fairly self-explanitory, Relcoloring is the changing of a nodes color i.e. if a node is red 
change it to black. The Color of a NULL node is always black. 

Recoloring is always tried before anything elses. Then if that does not work we go to rotation.

### Rotation 

A rotation is an operation on the Tree that changes the structure of the tree [without interfering with the overall ordering of nodes in the tree](https://en.wikipedia.org/wiki/Tree_rotation)

In a tree rotation one node is moved up, and one node is moved down in the tree.

#### Rules for Rotation when a Rotation is Necessary in RBT insertion

Rotation should occur when there is a RED-RED conflict in the tree 

There are two main pathways when this is true 

1. If the current node is the right child of the parent 
2. If the current node is the left child of the parent 

##### Pathway 1. 

- If the current nodes parent has a left child that is NULL or the parents left child is BLACK then: 
    - if the current nodes left child is not NULL AND its color is RED then: 
        - A Right-Left rotation should be perfomed 
    - If the current nodes right child is not NULL AND the color of the right child is RED 
        - A Left-Left rotation should be perfomed
- Otherwise (ELSE)  
    - You should let the parents left child to BLACK 
    - You should set the current nodes color to BLACK 
    - If the current nodes parent is not the ROOT THEN: 
        - Set the parents color to red 

##### Pathway 2 

- If the current nodes parent has a right child that is NULL or the parents right child is BLACK 
    - If the current nodes left child is not NULL and its color is REDthen: 
        - A Right-Right rotation should be performed 
    - If the current nodes right child is not NULL and the color of said node is RED then: 
        - A LEFT RIGHT rotation should be performed 
- Otherwise 
    - Set the parents right child to BLACK 
    - Set the current node to BLACK 
    - If the current nodes parent is not the trees ROOT then: 
        - Set the current nodes parent to RED 

#### The Different Types of Rotation

From doing some reading there are 2 Major types of rotation which can be combined to total 4 types of rotation that can be performed. 

The major types are: 

1. Left Rotation 
2. Right Rotation

The sub types are: 

1. Left-Right rotation
2. Right-Left rotation 

This leaves 4 types of rotation that can be performed: 

1. Left Rotation 
2. Right Rotation 
3. Left-Right Rotation 
4. Right-Left Rotation 

The sub-type rotation simply combine both a Left and a Right rotation 

#### Left Rotation  

A left rotation is done when the current node is in the right subtree if the uncle is black (or NULL by proxy)  

The left rotation algorithm goes something like this: 

```
left_rotate(Node root) { 
    Node x = root.parent; 
    Node y = root.left; 
    x.right = y; 
    x.parent = root; 
    root.left = x; 
}
```

tax the following tree for example: 

```
        20 
       /  \
      10   45
     /  \   \ 
     5  15  59
        / \ 
       12 19
```

Lets say we want to perform a rotate where the current node is 15

After rotation the tree would end up somethign like this: 

```
        20 
       /  \
      15   45
     /  \   \ 
    10  19  59
    / \
   5  12
```

#### Right Rotation 

#### Left-Right Rotation  

#### Right-Left Rotation 

### The Insertion Algorithm (Conceptual)

The algorithm has two main cases depending on the colour of the uncle. 

- If the unlce is Red we do a recolour. 
- If the Uncle is black we do a rotation and/or Recolouring

When Inserting into a Red Black Tree you first use the standard insertion algorithm in a BST and initialize the node to RED. 

If the node is the root node of the tree then you should change the color to BLACK. 

If the node is not the root then you will start the balancing algorithm 

- If the color of the parent node is BLACK then do not change the colour 
- If the color of the parent node is RED then you need to: 
    - Check  the colour of the nodes uncle 
        - If the nodes uncle is RED 
            - Change the color of the uncle and parent to black & change the grandfather to red 
                - Then repeat the relcoloring for the grandparent 
                - However if the grandfather is the root, do not change the grandfather to a red color
- If the color of the unlce is red then we begin to check the rotation case 


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



