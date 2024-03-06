# AVL Tree

Source: https://www.geeksforgeeks.org/introduction-to-avl-tree/
Source: https://en.wikipedia.org/wiki/AVL_tree

An AVL tree is another self balancing tree, much like Red-Black Trees; However, its balancing requirements are different to Red-Black Trees

Much like other BSTs any node can have at maximum two child nodes. 

The balancing requirements of an AVL tree dictate that the heights of the two subtrees from the root can differ by no more than one.

Insertion, Search and Deletion all take O(log n) in average and worst cases, where n is the number of nodes in the tree prior to the operation. 

Insertions and deletions may require rebalancing operations, and as the requirements are more strict AVL trees suit situations with less frequent write and delete operations. 

Lookups are on average faster in AVL trees due to the tree being generally more balanced than red-black trees when a large amount of data is inserted. 

AVL stands for "Adelson-Velsky and Landis" who are/were (probably aint alive anymore) two Soviet inventors who published the 1962 paper "An algorithm for the organization of information" in which the data structure is proposed.

AVL trees are the oldest self-balancing BST data structure to be invented. 

Its a common misconception that AVL trees are more complex to implement than Red-Black trees. It is my opinion that AVL trees are simpler by an order of magnitude to implement than Red Black trees. 

I've come to this conclusion due to 2 factors:

1. Whilst the balancing requirements are stricter - There is only one rule - Balance factor is in set { 1, 0, -1 } whereas Red Black Trees have more rules to obey
2. Due to the simpler balancing requirements there is much less boiler plate in the final code base due to no fixup methods and RED-RED/BLACK-BLACK conflict checks

Due to this I would recommend people implement an AVL tree before implementing a Red-Black tree

## Balancing Factor 

In a binary tree the balance factor of node `x` is defined to be the height difference of its two child sub-trees rooted at node-x. 

A representation of the balance factor can be viewed below:

`BF(x) = Height(x->right) - Height(x->left)`

A binary tree is defined to be an AVL tree if the invariant holds for every node `x` in the tree

*Note: [An invariant is a property of a mathematical object which remains unchanged after operations or transofrmations](https://en.wikipedia.org/wiki/Invariant_(mathematics)#Invariants_in_computer_science)*

The invariant in this scenario is that the `BF(x) <= 1 && BF(x) >= -1`  

A `BF(x) > 0` is called right heavy and the opposite (`BF(x) > 0`) is called left heavy where equal to 0 is generally called balanced. 

## Operations 

### Rebalancing 

When modifying the tree with an Insertion or Deletion occurs there will be situations when an AVL tree does not fit to the rules/invariants of the tree. 

In this circumstance a rotation/ number of rotations will be needed to restore the balance within the tree such that there is no violation of the AVL tree invariants 

Rotations work to satisfy the constraints of an AVL tree as they move the nodes vertically such that the in-order sequence of keys is fully preserved and the general properties of a BST are not violated. 

There are four possible variants of the violation of the invariants of an AVL tree:

`X = current_node`
`Z = child_node_of_X`
`Y = child_node_of_Z`

1. Right Right -> `Z` is a right child of `X` and `Y` is a right child of `Z`
2. Left Left -> `Z` is a left child of `X` and `Y` is a left child of `Z`
3. Right Left -> `Z` is a right child of `X` and `Y` is a left child of `Z`
4. Left Right -> `Z` is a left child of `X` and `Y` is a right child of `Z`

To Solve These violations we would do the following:

#### Rotations 

There are two main types of rotation:

1. Left Rotation 
2. Right Rotation 

Then as an addition there are two subtypes for right-left and left-right violations:

3. Right-Left Rotation
4. Left-Right Rotation 

Point 3 and 4 are simply a combination of left rotation and right rotaton depending on where the violation occurs in the rooted nodes subtree 

Take the diagram below to see how the mechanics of a rotation work:

```
    X       Left Rotate         Z
   / \      ---------->        / \
  T1  Z     <----------       X  T3
     / \    Right rotate     / \
    T2 T3                   T1 T2

```

As you can see a left rotate are simply inverted versions of each other. In code (without any AVL specific code) it may look something like this:

```

Node* left_rotate(Node* x) {
   Node* z = x->right;  
   Node* t2 = z->left; 
   x->right = t2;
   z->left = x; 

   return z; 
}

Node* right_rotate(Node* z) {
    Node* x = z->left; 
    Node* t2 = x->right;
    z->left = t2; 
    x->right = z; 

    return x; 
}

```

To reiteratee this is without any code for resetting the heights which is needed for AVL trees

When rotating subtrees with an AVL tree we need to set the new height of node `z` and node `x` after the rotation is performed

Below is an example of this using `left_rotate`

```

Node* left_rotate(Node* x) {
    Node* z = x->right; 
    Node* t2 = z->left; 
    x->right = t2;
    z->left = x; 

    z->height = 1 + get_max(height(z->left), height(z->right)); 
    x->height = 1 + get_max(height(x->left), height(x->right)); 

    return z;
}

```

Depending on the violation found either a single rotation will be performed or a stacked rotation of both `left_rotate` and `right_rotate` with the order they are called in dependent on the specific violation. 

#### Rotation Scenario Examples 

Lets do a few examples to demonstrate: 

##### Right-Right Rotation

Take the tree below where 30 is the inserted node:

```
    10
      \
      20
        \
        30
```

In this tree eventually the balance factor `bf` of 10 would evaluate to -2:

`bf(10) = height(10->right(20=2)) - height(10->left(Null)=0)`

Given this information we review the table and see which violation is met:

`bf(10) < -1 && insertion_data(30) > 10->right`

The above means that the node inserted `Y` is the right child of node `Z` - This would conform to a right-right rotate.

What seems to be confusing is that a right right rotate actually does a left_roation on the tree. This is because a left rotate raises up the Right child. 

Below demonstrates the rotation:

```
    10                  20
      \                /  \
      20  --RR-->    10   30
        \
        30
```

##### Left Left Rotation



### Search 

Search is much the same in any balanced or unbalanced BST where a `search(x, data)` will check a given nodes data against the data that is being searched for. 
If the data matches `x->data` then this node will be returned (or a true statement will be returned). If not a NULL or other falsey value will be returned. 

The code looks something like this: 

```
Node* search(Node* x, int data) {
    if (x == NULL) return NULL;

    if (data == x->data) return x; 

    Node* found_node; 

    if (data < x->data) found_node = search(x->left, data); 
    if (data > x->data) found_node = search(x->right, data); 

    return found_node; 
}

```

Of course this could also be done iteratively if that is the preffered method using a while loop and incrementing x until it is either null or matches that data parameter 

### Insertion 

Inserting a node into an AVL tree initially follows the same process as a standard Binary Search Tree. 

If the tree is empty you simply insert the new node as the root - if not you recursively go down the tree until you find an empty space to insert the new node

After insertion you must check the ancestors of the new node to see if the tree has become unbalanced. 

Only the ancestors will be subject to becoming unbalanced because only their nodes subtrees have been altered. 

This means that it is necessary to check each of the node's ancestors for consistency with the invariants of the AVL trees.

The process of checking the consistency of the nodes ancestors is called retracing and is accomplished by considering the balance factor of each node. 

Since a single insertion cannot cause an AVLs subtree to vary more than 1, the temporary balance factor of a node after insertion will range from [-2, +2]. 

If the Balance Factor remains within the tree invariants then only an update of the balance factor and no rotation is necessary

However, if the tempory balance factor falls outside the range of the tree invariantes (-2 or +2) the subtree rooted at the current node is seen as AVL unbanlanced.

To solve this lack of balance a rotation is needed. 


### Deletion 

