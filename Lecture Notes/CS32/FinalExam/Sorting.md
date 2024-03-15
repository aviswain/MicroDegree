# SORTING 
Everything is used to sort from least to greatest

**Stable vs Unstable Sort**
- An “unstable” sorting algorithm re-orders the items without taking into account their initial ordering.
```
ORIGINAL LINE:                          UNSTABLE LINE
Ebeneezer - 8 days                      Steve – 8 days
Carey – 5 days                          Vicki – 8 days
David – 2 days                          Ebeneezer - 8 days
Michael – 4 days                        Andrea – 5 days // ANDREA IS NOW AHEAD OF CAREY FOR SOME REASON!
Steve – 8 days                          Carey – 5 days
Vicki – 8 days                          Michael – 4 days
Andrea – 5 days                         David – 2 days
```
- A “stable” sorting algorithm does take into account the initial ordering when sorting, maintaining the order of similar-valued items.
```
ORIGINAL LINE:                          STABLE LINE
Ebeneezer - 8 days                      Steve – 8 days
Carey – 5 days                          Vicki – 8 days
David – 2 days                          Ebeneezer - 8 days
Michael – 4 days                        Carey – 5 days // carey stays ahead of andrea
Steve – 8 days                          Andrea – 5 days
Vicki – 8 days                          Michael – 4 days
Andrea – 5 days                         David – 2 days
```

## Inefficient Sorting
Basic Facts:
- All slow algorithms generally require O(N^2) steps to order N values. 
- They compare every item to every other item, swapping out-of-order items.

### Selection Sort
- How to recognize?
  - It will always look like a sorted part, then an unsorted part. If the algorithm has ran for some iterations, no unsorted elements should appear before sorted ones.
- One line summary?
  - Take the smallest item and move it to the first slot. Take the 2nd smallest item and move it to the second slot. Repeat until everything is sorted.
- When should I use?
  -  In scenarios where simplicity and ease of implementation are prioritized over performance, especially when dealing with small datasets or educational purposes.
     It can be beneficial in situations where memory efficiency is crucial, as it is an in-place sorting algorithm that does not require additional memory beyond the input array. 
- More or less efficient on specific data?
  - NOPE!
- Other details...
  - Can be easily adapted to linked lists because all you have to do is swap the links between nodes.

1. Look at all items, select the smallest item
2. Swap this with the first item
3. Look at the remaining N-1 items, and select the next smallest item
4. Swap this with the second item
5. Look at the remaining N-2 items, and select the next smallest item
6. Swap this with the third item and so on...

```
void selectionSort(int A[], int n) {
  for (int i = 0; i < n; i++) {
    int minIndex = i;
    for (int j = i+1; j < n; j++) {
      if (A[j] < A[minIndex])
        minIndex = j;
    }
    swap(A[i], A[minIndex]);
  }
}
```
### Insertion Sort
- More or less efficient on specific data?
  - Yes, if all the items are already roughly in order, insertion sort never needs to do any shifting! In this case, it is rougly O(N) steps to sort.
    Conversely, a perfectly mis-ordered set of items (sorted backwards) is the worst case. Since every round requires the maximum shifts!

PSUEDOCODE
```
Start with set size s = 2
  While there are still books to sort:
    Focus on the first s books
    If the last book in this set is in the wrong order
      Remove it from the shelf
      Shift the books before it to the right, as necessary
      Insert our book into the proper slot
```
```
void insertionSort(int A[], int n) {
  for(int s = 2; s <= n; s++) {                 // Focus on successively larger prefixes of the array.
                                                   Start with the first s=2 elements, then the first
                                                   s=3 elements...

    int sortMe = A[s - 1];                      // Make a copy of the last val in the current set –
                                                   this opens up a slot in the array for us
                                                   to shift items!

    int i = s - 2;
    while (i >= 0 && sortMe < A[i]) {           // Shift the values in the focus region right until
      A[i+1] = A[i];                               we find the proper slot for sortMe.
      --i;
    }

    A[i+1] = sortMe;                            // Store the sortMe value into the vacated slot.
  }
}
```
### Bubble Sort
