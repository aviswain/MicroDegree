# Big-O 
- Whenever adding terms of the same variable together, make sure to only keep the highest order term (Lowest to Highest order: 1, logn, n, nlogn, n^2, 2^n, n!)
- If Big-O calculation relies on multiple inputs, keep them as long as they are independent. Reduce them if one relies on another.
- Terms are multiplied when their relationship involves nesting, and are added when not.

## STL Big-O Cheat Sheet
### List (aka Linked list)
- Inserting an item (top, middle*, or bottom): `O(1)`
- Deleting an item (top, middle*, or bottom): `O(1)`
- Accessing an item (top or bottom): `O(1)`
- Accessing an item (middle): `O(n)`
- Finding an item: `O(n)`

\*But to get to the middle, you may have to first iterate through X items, at cost `O(x)`

### Vector
- Inserting an item (top, or middle): `O(n)`
- Inserting an item (bottom): `O(1)`
- Deleting an item (top, or middle): `O(n)`
- Deleting an item (bottom): `O(1)`
- Accessing an item (top, middle, or bottom): `O(1)`
- Finding an item: `O(n)`

### Map
- Inserting a new item: `O(log2n)`
- Finding an item: `O(log2n)`
- Deleting an item: `O(log2n)`

### Queue and Stack
- Inserting a new item: `O(1)`
- Popping an item: `O(1)`
- Examining the top: `O(1)`

### Set
- Inserting a new item: `O(log2n)`
- Finding an item: `O(log2n)`
- Deleting an item: `O(log2n)`


**Example Problems**

O(n^2)
```
for ( int i = 0; i < n; i++ ) { 
  Circ arr[n]; // Constructor called n times during each for-loop iteration                               
  arr[i].setRadius(i);
}
```

Q: "If I have a vector of sets of ints: vector< set<int> > v; You may assume vector v has N total sets in it. You may assume that each set has an avg of Q items. What is the Big-O of finding the first set with a value of 7 and then counting the number of even values in that set?"

A: `O(Nlog2Q + Q)`

## Big-O Space Complexity
Space complexity is the Big-O of how much storage your algorithm uses, as a function of the data input size, n.

**Example Problems**
O(n)
```
void reverse(int array[], int n) {
  int *tmparr = new int[n];
  for (int i = 0; i < n; ++i)
    tmparr[n-i-1] = array[i];
  for (int i = 0; i < n; ++i)
    array[i] = tmparr[i];
  delete [] tmparr;
}
```

O(n)
```
void printNums(int n) {
  if (n < 0)
    return;

  cout << n << “\n”;
  printNums(n-1);
}
```
