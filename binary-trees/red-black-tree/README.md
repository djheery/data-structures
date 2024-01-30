# Red-Black Tree 

This information consists of notes taken from the following sources: 

1. Geeks for Geeks: 
    - https//www.geeksforgeeks.org/introduction-to-red-BLACK-tree/
2. Rob Edwards (YT): 
    - https://www.youtube.com/watch?v=nMExd4DthdA
    - https://www.youtube.com/watch?v=v6eDztNiJwo&t=302s

The Red Black Tree is an expansion of the Binary Search Tree. 

The Binary Search Tree is great for sorting data however, the search function is highly dependent on the shape of the tree.

When the shape of the tree has atrophied the tree can degerate into a linear structure with a time complexity of O(n)

Red Black Trees address this problem by self-balancing on insertion and deletion. Ensuring the tree is balanced is a preventative measure 
to stop the tree degerating into a linear structure and preserving the average O(log n) search time 

## Rules and properties of a Red-Black Tree

1. Every node has a color (Red or Black) 2. The root is always BLACK 3. Red nodes cannot be proceeded or preceeded by another red node 4. Every path from a node to any of its leaf nodes has the same number of black nodes 5. Every Leaf is colored black 6. The black height is the number of black does on a path from root to leaf ## Methods 

The implementation of red BLACK tree is a fair amount more complex than a normal BST (discounting search as it is the same) 

## Insertion 

When inserting into a RBT there are two balancing tools used after the initial insertion: 

1. Recoloring
2. Rotation 

### Recoloring 

Recolring is fairly self-explanitory, Relcoloring is the changing of a nodes color i.e. if a node is red 
change it to BLACK. The Color of a NULL node is always black. 

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

Remember that rotations are used to try to balance the tree and mitigate search time degredation due to an imbalanced tree

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

Note below We are not concerened with colors as you would be when implementing a RBT, rather just the rotations
The colors may be referenced but just as an aside
#### Left Rotation  

A left rotation is done when the current node is in the right subtree if the uncle is BLACK (or NULL by proxy)  

The left rotation algorithm goes something like this: 

```
Node* left_rotate(Node* root) { 
    Node x = root->right; // 15 
    Node y = x->left; // 12 
    x->left = root;  // 12 -> 10 
    root->right = y; // 10 -> 12 
    root->parent = x; // 15

    if(y != NULL) y->parent = root; 

    return x; // X is in the place that the root used to be 
}
```

Take the following tree for example: 

```
        20 
       /  \
      10   45
     /  \   \ 
     5  15  59
        / \ 
       12 19
```

Lets say we want to perform a rotate where the current node is 10

After rotation the tree would end up somethign like this: 

```
    
        20              20
       /  \            /  \
      10   45         15  45 
     /  \   \  ====> /  \   \
     5  15  59      10  19  59
        / \        /  \
       12 19      5    12
```

#### Right Rotation 

A right rotation is basically the opposite of a left Rotation

The code for a right rotation look something like this: 

```
Node* right_rotate(Node* root) {
    Node* x = root->left; 
    Node* y = x->right; 
    x->right = root; 
    root->left = y; 
    root->parent = x; 

    if(y != NULL) y->parent = root; 

    return x; 
}
```

Again let's use an example for the right rotate: 

```
        20 
       /  \
      10   45
     /  \   \ 
     5  15  59
    / \
   3   9
```

Lets say we want to perform a rotation where the current node is 10 again: 

```
        20                    20
       /  \                  /  \
      10   45               5   45
     /  \   \              / \    \
     5  15  59   ====>    3  10   59
    / \                      / \
   3   9                    9  15
```

Whilst the trees structure may be slightly differnt it should be fairly clear that the LEFT & RIGHT rotation operatons are just the reverse of each other 

After we do a rotation we should fix the color of the nodes so that the parents are BLACK and the children are red

#### Left-Right Rotation  

With a LEFT-RIGHT rotation the prcess works slightly different whilst the logic for both the left and the right rotation work the same.

A Left Right rotation indicates that the colision has occured in the Left Subtrees right Subtree. 
This sounds confusing but take the following example given that the root node is currently 10: 

```
        20 
       /  \
      10   45
     /  \   \ 
     5  15  59
    / \
   3   9
```

In this circumstance an LEFT-RIGHT colision would indicate that the colision has occured with the 5 (Left) and the 9 (Right) hence 
left right.

To handle this the following outer logic is used: 

```
root->left = rotate_left(root->left); 
root->left->parent = root; 
root = rotate_right(root); 
root->color = BLACK; 
root->right->color = RED; 
tree->lr = false; 
```

So to break this down: 

1. We perform a rotation using the left nodes subtree as a base 
2. We assign the parent of the left node to the current node (root) 
3. we then perform a right rotation on the current node (root)
4. We assign the current nodes (roots) color to BLACK
5. We assign the current nodes right child to the color of RED
6. We indicate that there is no need to perform a LEFT-RIGHT rotation again at this point

*NOTE: the current node will change after step 3 of the above algorithm as the rotate algorithm returns the new node that should be in that place*

To see how this works in action lets do it step by step where *10* represents the root

```
        20                          20                             20
       /  \                        /  \                           /  \
      10   45                     10  45                         9   45
     /  \   \  left rotation     /  \   \    right rotation     / \    \
     5  15  59 ============>    9   15  59   ==============>   5  10   59
      \                        /                                    \ 
       9                      5                                     15
```

Whilst the tree is fairly skewed the demonstration still works and you should be able to see the way the rotation works
The skewed nature is just because of a bad choice to perform the rotation on 

#### Right-Left Rotation 

This algorithm is the equivalent to a LEFT-RIGHT rotation just inverted 

To handle these rotations the following outer logic is used (calling upon the core rotation algorithms) 

```
root->right = rotate_right(root->right); 
root->right->parent = root; 
root = rotate_left(root);
root->color = BLACK; 
root->left->color = RED; 
tree->rl = false; 
```

The steps are: 

1. We perform a rotation using the right nodes subtree as a base 
2. We assign the parent of the right node to the current node (root) 
3. We perform a left rotation on the current node (the root) 
4. We assign the current nodes (roots) color to BLACK 
5. We assign the node left childs color to RED
6. We indicate that there is no need to perform a RIGHT-LEFT rotation again at this point

*NOTE: the current node will change after step 3 of the above algorithm as the rotate algorithm returns the new node that should be in that place*

Again I will include an example of what the rotation looks like using 45 as the base: 


```
          20                            20                                   20         
       /     \                        /     \                             /     \      
      10      45                     10      45                          10      52    
     /  \    /  \  right rotation   /  \    /  \    right rotation      /  \    /  \   
    5   15  30  59 ============>   9   15  30  52    ==============>   9   15  45  59  
                /                                \                            /      
               52                                59                          30        
```

### The Insertion Algorithm (Conceptual)

The algorithm has two main cases depending on the colour of the uncle. 

- If the unlce is Red we do a recolour. 
- If the Uncle is BLACK we do a rotation and/or Recolouring

When Inserting into a Red Black Tree you first use the standard insertion algorithm in a BST and initialize the node to RED. 

If the node is the root node of the tree then you should change the color to BLACK. 

If the node is not the root then you will start the balancing algorithm 

- If the color of the parent node is BLACK then do not change the colour 
- If the color of the parent node is RED then you need to: 
    - Check  the colour of the nodes uncle 
        - If the nodes uncle is RED 
            - Change the color of the uncle and parent to BLACK & change the grandfather to red 
                - Then repeat the relcoloring for the grandparent 
                - However if the grandfather is the root, do not change the grandfather to a red color
        - If the uncle is BLACK (or NULL as NULL is BLACK) then decide which rotation to do
            - if the current is the right child of the parent and the uncle is BLACK 
               - If the left child of the current node is RED (i.e not NULL or BLACK)  
                  - Set a flag that a RIGHT-LEFT rotation and Recolor needs to be performed 
               - If the right child of the current node is RED (i.e not NULL or BLACK) 
                  - Set that a Left Rotation and Recolour should be perfomed
            - If the current is the left child of the parent and the uncle is BLACK
                - IF the left child of the current node is RED (i.e not NULL or BLACK) 
                    - Set a flag that a RIGHT rotation should be performed
                - If the right child of the current node is RED (i.e not NULL or BLACK) 
                    - Set a flag that a LEFT RIGHT rotation should be performed
        
This is all very confusing and I can't say I am fully on top of it, but that is what seems to be the basis of the algorithm 

In practice it is written slightly differently: 

```
insert(RBT tree, Node* root, int node_data) {
    if(root == NULL) return new_node(node_data); 

    bool red_red_conflict_flag = false; 

    if(node_data < root->data) {
        root->left = insert(tree, root->left, node_data); 
        root->left->parent = root; 
        if(root->color == RED && root->left->color == RED) {
            red_red_conflict_flag = true; 
        }
    } else if(node_data > root->data) {
        root->right = insert(tree, root->right, node_data);
        root->right->parent = root; 
        if(root->color == RED && root->right->color == RED) {
            red_red_conflict_flag = true; 
        }
    }

    if(tree->ll) {
        root = rotate_left(root); 
        root->color = BLACK; 
        root->left->color = RED; 
        tree->ll = false; 
    } else if(tree->rr) {
        root = rotate_right(root); 
        root->color = BLACK; 
        root->right->color = RED; 
        tree->rr = false; 
    } else if (tree->rl) {
        root->right = rotate_right(root->right); 
        root->right->parent = root; 
        root = rotate_left(root); 
        root->color = BLACK; 
        root->left->color = RED; 
        root->rl = false; 
    } else if(tree->lr) {
        root->left = rotate_left(root->left); 
        root->left->parent = root; 
        root = rotate_right(root);
        root->color = BLACK; 
        root->right->color = RED; 
        tree->lr = false; 
    }

    if(!red_red_conflict_flag) return root; 

    bool in_left_subtree = root->parent->left == root; 
    bool in_right_subtree = root->parent->right == root; 

    if(in_right_subtree) {
      bool uncle_left_is_black = root->parent->left == NULL || root->parent->left->color = BLACK; 

      if(uncle_left_is_black) {
        if(root->left != NULL && root->left->color == RED) {
            tree->rl = true; 
        } else if(root->right != NULL && root->right->color == RED) {
            tree->ll = true; 
        }
      } else {
         root->parent->left->color = BLACK; 
         root->color = BLACK; 

         if(root->parent != tree->root) root->color = BLACK; 
      }

      return root; 
    } 
    
    if(in_left_subtree) {
        bool uncle_right_is_black = root->parent->right == NULL || root->parent->right->color = BLACK;

        if(uncle_right_is_black) {
            if(root->left != NULL && root->left->color == RED) {
                tree->rr = true; 
            } else if (root->right != NULL && root->right->color == RED) {
                tree->lr = true; 
            }
        } else {
            root->parent->right->color = BLACK; 
            root->color = BLACK; 

            if(root->parent != tree->root) root->parent->color = RED; 
        }
    }

    return root; 
}
```

### Some Notes about the code above 

A few notes about the code above: 

It can look very confusing, and to some extent it is; however, There is a lot of repetition in the code base as generally there are only four pathways for rotation and 2 pathways for recoloring (not including the recoloring done on rotation) 

The code in the `red-black-tree.c` is formated differently to above in an attempt to make it more legiable and break each section out into a helper method to allow focus on just that part of the method 

Some of the else if parts can be skipped for example: 

- within `if(uncle_right_is_black) {...}` 
    - We aready know that a conflict has occured so once the first sub if check: `if(root->left != NULL && ...)` it stands to reason that the second case must be true

The rotations always occur within the new_node->parent->parent. Lets lay it out a little bit: 

Say a new node (N) has been added in a left subtree somewhere in the recursive call stack 

N will return itself to the parent: 

`root->left =  insert(tree, root->left, node_data) // N will return here`

At this point we check if a RED-RED conflict has occured in N->parent and if it has we set it true.

At this point we bypass all of the rotation checks because if we have coded the program right, none of these will be true at this point
This is due to the formatting of the code. Remember the `if` checks that set the `red_red_conflict_flag` do not occur until after the rotation checks. 
Thus `N->parent` will perform these checks and set a given rotation to true if it is necessary (in this case lets assume it is) 

Then its vital to remember the `N->parent` will return itself to its own parent `N->parent->parent` due to the way recursive code works. 

At this point a rotation flag will have been set to true on the tree struct itself and thus a rotation will be performed. 

The confusion generally occurs because of the recursive nature of this method. But writing it out iteratively would likely be a lot longer winded and more confusing than this

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



