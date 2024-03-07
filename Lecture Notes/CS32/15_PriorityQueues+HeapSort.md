# Priority Queues
Priority Queues are a special type of queue. 

They are used to prioritize different types of data for processing based on their importance.

**Quick Facts**:
- They allow us to keep a prioritized list of items
- Each item you insert into the queue has a "priority rating", specified by the creator of the queue, to indicate its importance
- Each item is ordered primarily by its priority rating, and secondarily by the order of insertion

**Operations with a Priority Queue**:
- Insert a new item
- Peek at the value of the highest priority item
- Remove the highest priority item from the queue

Now that what we know what a priority queue does, how do we implement it? First we need to learn about...

# Heaps
Imagine a giant dump in a landfill. That's basically a heap. 

A heap is a tree-based data structure that is used to implement priority queues and do efficient sorting.

There's two types of heaps: Minheaps and Maxheaps. In a minheap, the smallest item is always at the tree's root. Everytime you extract or insert an item, you have to update the tree to maintain this property (This is an O(log(n)) operation). Maxheaps are the same but they keep the largest item at the root. 

The type of tree that a heap uses is called a **"Complete"** Binary Tree:
- The top N-1 levels of the tree are completely filled (no empty nodes). That means every level except the deepest level must contain as many nodes as it possibly can.
- All nodes on the bottom-most/deepest level must be as far left in the tree as possible (with no empty slots between them). 

Based on the heap that we are implementing we want to be able to quickly insert a new item into the heap and quickly extract the root/top item from the heap. In order to do this for the two different heaps, we have to follow these rules...

For Maxheaps:
- The value in every node must be >= the value of its children
- The tree is a COMPLETE binary tree

For Minheaps:
- The value in every node must be <= the value of its children
- The tree is a COMPLETE binary tree

Notice how easy this makes it to access the highest priority item in the tree!

## Operating on a Maxheap

**Extracting the Largest Item**

If you follow the steps below, when you're done, the heap's organization should stay consistent. (Largest value is on the top again and still a complete tree)
1. If the tree is empty, return error.
2. Otherwise, the top item in the tree is the largest value. Remember it for later.
3. If the heap only has one node, then delete it and return the saved value.
4. Copy the value from the right-most node in the bottom-most row to the root node.
5. Delete the right-most node in the bottom-most row.
6. Repeatedly swap the just-moved value with the larger of its two children until the value is greater than or equal to both of its children ("sifting DOWN").
7. Return the saved value to the user.

**Adding a Node**
1. If the tree is empty, create a new root node & return.
2. Otherwise, insert the new node in the bottom-most, left-most open spot of the tree (so it stays complete)
3. Compare the new value with its parent's value.
4. If the new value is greater than its parent's value, swap them.
5. Repeat steps 3-4 until the new value rises to its proper place. ("Reheapification")

## How to Implement a Heap

Trying to implement a heap using classic binary tree nodes can be hard cause
- It's not easy to locate the bottom-most, right-most node during extraction
- It's not easy to locate the bottom-most, left-most node for insertion
- It's not easy to locate a node's parent to do reheapification swaps

So something we can do instead is implement it by using an array! We can do this because we know that each level of the tree has 2x the number of nodes of the previous level (except for the bottom-most level). So we can just copy our nodes a level at a time into an array. This means the root node value goes into the first slot of the array (heap[0]), the next two node values go into the second and third slots of the array, the next four values go into the next four slots and so on...

This gives us a few useful properties:
- We can always find the root value in `heap[0]`
- We can always find the bottom-most, right-most node in `heap[count-1]`
- We can always find the bottom-most, right-most node in `heap[count]`
- We can add or remove a node by simply setting `heap[count] = value;` or updating `count`

Furthermore, if a parent is in slot j of the array, we can locate their childrens' slots by...
- Left Child: `heap[(2 * j) + 1]`
- Right Child: `heap[(2 * j) + 2]`

And if we want to locate the slot for a parent node from its child node (in slot k) then we can do...
- Parent: `heap[(k-1) / 2]`

### The Actual Implementation

Extracting top node from a maxheap
```
cpp

int extractFromMaxHeap(int heap[], int& count) {
  if (count == 0)
    return(-1); // return error

  int largestVal = heap[0];

  if (count == 1) {
    count = 0;
  } else {
    heap[0] = heap[count-1];
    count--;

    // repeatedly swap
  }

  return largestVal;
}
```

Adding a node to a maxheap
```
cpp

void insertToMaxHeap(int val, int heap[], int& count) {
  heap[count] = val;
  count++;

  // compare the new value with values in the map to find the correct position for it
}
```

## Big-O Complexity of the Heap

Cost of inserting/extracting an item: O(log2(N))

_Calculation: If you have complete binary tree with N entries, it's guaranteed to be exactly log2(N) levels deep. So in the worst case we have to do log2(N) comparisons and swaps of our new value (regardless of whether it is stored in an array)._

## Heapsort
Heapsort is O(Nlog2(N)) that uses a maxheap in a super clever way to sort a bunch of values. 

This is how Heapsort goes:

**STEP 1: Convert our input array into a maxheap**. Basically you are are just going to shuffle the values around in the input array so they become a maxheap. As we heapify higher
subtrees, they rely upon the lower sub-trees that were heapified earlier! Once we have finishde heapifying from out root node, our entire array will hole a valid maxheap! This takes O(N) steps.
```
// PSUEDOCODE:
// startNode = N/2 - 1
//  for (curNode == lastNode thru rootNode)
//    Focus on the subtree rooted at curNode
//    Think of this subtree as a maxheap
//    Keep shifting the top value down until your subtree becomes a valid maxheap
```
STEP 2: While there are numbers left in the heap: repeatedly extract the ith largest item from the max heap and place that item back into the array, j slots from the end. This takes O(Nlog2*N) steps.
1. Remove the biggest value from the heap and reheapify (repeat step 1) to free up the last slot in the array.
2. Place it in the last open slot of the array

Big-O Explanation: O(N) + O(Nlog2(N)) = O(Nlog2(N))

