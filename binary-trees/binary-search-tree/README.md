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


