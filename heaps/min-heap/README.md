# Min Heap 

I will forgoe much of the explanation in this README for the sake of brevity - If you want a more indepth breakdown please look at:

`/heaps/max-heap/README.md` 

The max heap and the min-heap are simply inverted thus the methods are more or less the same aside for the checking of the heap property. 

The heap property for a min heap is:

`value(node) < value(node->left) && value(node->right)`;

With that knowledge and the knowledge of how to build a `max-heap` you should be able to understand the code in `min-heap.c` or create a min heap yourself. 

Maybe one day I'll come back to this file and write it out as a test of my memory. 
