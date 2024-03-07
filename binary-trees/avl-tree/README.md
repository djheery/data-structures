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

This example below is the inverted version of the above where the balance factor of 30 is +2 which does not meet the invariants of a red black tree

This as the `bf(30) = +2` we know that the tree is left heavy. We also know that the inserted data (10) is less than 30->left(20). This means a `LEFT-LEFT` rotation should be performed. 

```
   30                20
   /                /  \
  20 ----LL--->    10  30
  / 
 10
```

Remember that a left-left rotation is actually just a singular `right_rotate(X)` where X is 30 thus 30->left will move up in the tree forcing 30 down in the tree to 20->right and the heights of the respective nodes will be reset

##### Right Left Rotation

A right left rotation is two rotations stacked. In the case of a right - left rotation it occurs when the `bf(x) < -1 && insert_data < x->right->data`

Take the tree below: 

```
  20
 /  \
10  40
    / \
   30 50
    \
    25
```

Given the following:

```
x = 20
y = 40
z = 25
```

The above dictates that x is the current node
y is the the right child of x 
z is the new node inserted 

Eventually as the recursive calls bubble up the chain of balance factors would look like this:

```
bf(30) = -1
bf(40) = 1
bf(20) = -2 
```

Remember the `bf(x)` is calculated as `height(x->left) - height(x->right)`. Where a given node (left or right of x) is NULL height will return 0

Given that `z->data` is less than `y->data` we meet the criteria for a right left rotate. 

With a right-left rotate first a `right_rotate` is performed on `x->right` which is `y` in this circumstance

This rotation replaces `y` with `y->left` and moves the current `y` down into `y->right` position

Then a final `left_rotate` is performed on node `x` 

In this scenario first 30 will be pulled up into 40s place pushing 40 down after the right rotate 

Then the left rotation would force 20 down into 10s place and pull 30 up to the root node position with all other nodes being replaced with it. 

You can see this in the diagram below: 


```
  20                     20                     30
 /  \                   /  \                   /  \
10  40 -----RR----->   10  30 ----LL----->    20  40
    / \                    / \               /  \   \
   30 50                  25  40            10  25  50
   /                           \ 
  25                           50
```

##### Left Right Rotate 

The Left Right Rotate is the inversion of a right left rotation so rather than retreading old ground I will simply provide a diagram.

The main difference to note is that the critera is that `bf(x) > 1 && inserted_data > x->left->data`

```
    40                       40                         30
   /  \                     /  \                       /  \
  20  50  -----LL---->     30  50   ------RR---->     20  40
 / \                       / \                       /    / \
10  30                    20 35                     10   35 50
     \                    /
     35                  10
```

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

If you scroll up to the Rebalancing section of these notes you will see the subsequent critera for rotations 

Due to the recursive nature of the insertion function the steps of insertion generally look like this:

1. Search for the First Null node using BST search 
2. Insert the new node in the space of this new node and return it to the relevant node to be assigned as either left or right of that node 
3. Bubble up the recursive stack, reassign the height of the new node (`1 + max(height(node->left), height(node->right))`)
4. Check the `balance_factor(node)` satisfy the AVL tree invariants -> { -1, 0, 1 } 
4a. If the `bf(node) is not in set(avl_tree_invariants)` take the following actions:
    - `bf > 1 && inserted_data < node->left->data` : `Left Left Rotation` 
    - `bf < -1 && inserted_data > node->right->data` : `Right Right Rotation` 
    - `bf > 1 && inserted_data > node->left->data` : `Left Right Rotation`
    - `bf < -1 && inserted_data < node->right->data` : `Right Left Rotation` 
5. Return the root node (This may be changed depending on step 4/4a 

*Note:* In this variation of the AVL Tree we are not allowing duplicates 

With this structure we ensure that any violation of the AVL Tree invariants is retraced and fixed as we bubble up the recursive stack. 


### Deletion 


