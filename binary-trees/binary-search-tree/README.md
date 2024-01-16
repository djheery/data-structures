# Binary Search Tree 

A Binary Search Tree is a common tree like data structure. 
You can read a bit more about the more general binary tree data structure in the `/binary-trees/binary-tree/README.md`. 

The main difference between a Binary Tree and a Binary Search Tree is in it's insertion, deletion and node searching. 

The reason for the difference is that there is an added check for whether a node to insert, delete or search for is greater than or less than its predecessor. 

When searching a tree the steps are generally as follows: 

- If the `insertion_data < current_node->data` then you will search the left subtree  
- If the `insertion_data > current_node->data` then you will search the right subtree 

It is worth noting that you can change `insertion_data` for `deletion_data` or `node_to_search_for` the same rules still apply. 

In the cases of deletion and searching you simply check if the `node_data_to_search_for == current_node->data` then perform some action based on this. 

## Deletion 

Deletion is a fair amount more complex than in a regular binary tree there are a few cases you need to check for: 

- Is the node to delete a leaf node? 
- Does the node to delete have 1 child? 
- Does the node to delete have 2 children? 

### The Node to delete is a leaf node or there is 1 child 

If the node to delete is a leaf node then it's pretty simple (You can just free the node) 

However, in practice you often write it recursively so for the sake of brevity you can do this in the same way as if the node has one child: 

`if node->left == NULL then parent->left/right = node->right`
`if node->right == NULL then parent->left/right = node->left` 

It may not be obvious but this handles both when there is only one child node and no child nodes. 

This is becasue in the situation that either node left or right is null we are just assigning the parents left/right node to the other 

And in the circustance both are null we are already handling this as the first if check will be true so we assign the parent to node->right 

node->right in this circumstance is also null so we are simply assigning the parent->left/right to null 

Obiously this will be written differently because of the use of recursion for example. 

### When both children are present 

In this circumstance the complexity begins to emerge. How do we know what to do. 

To do this you need to find the inorder successor of the right child of the current node. Generally this will be the minimum value in the 
left subtree of the right child of the node to delete. 

To find the inorder successor the code will look like this: 

```
Node* replace_root_data_with_inorder_successor_data(Node* root) {
    Node* parent = root; 
    Node* successor = root->right; 

    while(successor->left) {
        parent = successor; 
        successor = parent->left; 
    }

    // More code to follow
}
```

In this circumstance the successor will eventually evaluate to the minimum value in the left subtree. 

So what do we do with this successor node? 

Well we want to replace the `root->data` with the `successor->data` and then free that node. 

But we do have to be careful. We don't want to lose any leaf nodes down the right subtree of these successor nodes.  

To accomodate for this we have to perform a check before we swap the data and free the successor. 

The code might look something like this: 

```
Node* replace_root_data_with_inorder_successor_data(Node* root) {
    Node* parent = root; 
    Node* successor = root->right; 

    while(successor->left) {
        parent = successor; 
        successor = parent->left; 
    }
    
    // NEW CODE 

    if(parent != root) {
        parent->left = successor->right; 
    } else {
        parent->right = successor->right; 
    }

    root->data = successor->data;
    free(successor); 

    return root; 
}

```

I spent a lot of time getting confused about the code above so I will attempt to document it here: 

If the parent is not equal to the root then we can assign the parents left node to the successors right node as we know that the successors
right node will be less than the parent or will simply be null. 

However, if the parent is still the root (this means there was no left subtree of the successor) then we must set the right node of the 
root to the right node of the node of the successor. 

This is because we are about to replace the root->data wih the successor->data and thus the successor->right is will be greater than 
the root->data after the data transfer. 

After this we simply make the data swap and free the successor 






