# Big-O 
- Whenever adding terms of the same variable together, make sure to only keep the highest order term (Lowest to Highest order: 1, logn, n, nlogn, n^2, 2^n, n!)
- If Big-O calculation relies on multiple inputs, keep them as long as they are independent. Reduce them if one relies on another.
- Terms are multiplied when their relationship involves nesting, and are added when not.

**Saved Questions**

O(n^2)
```
for ( int i = 0; i < n; i++ ) { 
  Circ arr[n]; // Constructor is called n times during every for-loop iteration                               
  arr[i].setRadius(i);
}
```
