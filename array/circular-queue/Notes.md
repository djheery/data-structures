# Circular Queue 

The circular queue is a variation on the queue data type that is more efficient in a few ways. 

On dequeue a standard queue data type involves:

- Extracting the front of the queue and doing dequeuing it 
- Moving all the remaining elements in the queue to q[n - 1] position an O(n) operation.

This all makes a standard dequeue operation an O(n - 1) operation. Or O(n) if you include reading the front of the queue. 

Whereas as because of the nature of a circular queue the step just involves 

- Extracting the front of the queue and doing something with it 
- Incrementing the front index % capacity of the queue. 

Similarly enqueue operations just inolve incrementing the rear to (rear + 1) % capacity and just inserting at the rear index. 

Obviously I have ommitted checks needed to check that the queue may not be full or empty. 

This improves the effeciency and overhead that occurs when using a standard queue. 

Making dequeue operations faster in general. 

It can also help in avoiding array overflow issues. However, proper checking to the current status of the size of the queue is highly necessary for this. 

## What a queue looks like: 

A circular queue can look a variety of ways but the one I implemented looks something like this: 

```

typedef struct {
    int* queue; 
    int front; 
    int rear; 
    int size; 
    int capacity; 
} CircularQueue 


```
To break down the fields: 

- `queue` - In this circumstance it is a pointer to an allocated block of memory which will be of size (capacity * sizeof(T)) The type is arbitrary
- `front` - The front index of the queue 
- `rear` - The rear index of the queue 
- `size` - The current size or length of the queue 
- `capacity` - The max length of the queue or queue capacity 

Available methods the queue are much the same as a standard queue except maybe named a little different 

- `toString`/ `show` => Show the full queue 
- `enqueue` => Queue a new item 
- `dequeue` => dequeue the front of the queue 
- `front` => show the front of the queue 
- `rear` => show the rear of the queue 

This is just a small subset of what was implemented in the `circular-queue.c` file for brevity. 

## Applications 

Below are a few of the applications listed. For this list I used ChatGPT and checked that this seemed correct 
via a shallow depth google search. 

It may be interesting to try and implement one of the applicaitons below in a project to get to grips with 
this type of data structure a little more. 

### Buffering Data Streams 

Circular queues are often used to buffer a data stream when there is a continuous flow of data. It is advantageous
because of the efficiency in enqueue, dequeue, read and write operations. 

Buffering data streams include Audio Streaming, plain text streaming etc. 

### Network Buffers 

Circular queues are employed in networking protocols to manage incoming and outgoing packages. 

### Keyboard input buffers 

Circular queues can be employed to manage keyboard input in computer systems. Characters are enqueued when keys are pressed and dequeued when processed by the system. 

