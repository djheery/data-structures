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

### Rotations 

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


### Deletion 

