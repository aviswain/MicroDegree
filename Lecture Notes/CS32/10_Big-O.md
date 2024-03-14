# Big-O
Big-O is a technique programmers use to quickly understand an algorithm's efficiency. It is not exact - instead it gives rough estimates in terms of log(N), N, Nlog(N) or N^2. It is
often used to pick the best algorithm in a given scenario.

**Q**: _So any factor of N will always be preferred over a factor of N^2?_

**A**: _**NOPE!**_ _Take the following example...._

_Let's say I am trying to sort N numbers. Algorithm A takes 5N^2 steps while Algorithm B takes 37000N steps. Which one is better?_
- _If we are sorting 1,000 numbers..._
  - _Algorithm A takes 5M instructions (WINNER!)_
  - _Algorithm B takes 37M instructions_
- _If we are sorting 10,000 numbers..._
  - _Algorithm A takes 500M instructions_
  - _Algorithm B takes 370M instructions (WINNER!)_
- _If we are sorting 1 million numbers..._
  - _Algorithm A takes 5 trillion instructions_
  - _Algorithm B takes 37 billion instructions (WINNER!)_
 
_So it depends on the scenario! But on average we will use the operation that has the lowest order because more often than not we'd like to be able to scale up our system later on to 
handle more items._

Big-O measures an algorithm by the gross number of steps that it requires to process an input of size N in the WORST CASE scenario. This means we will never be so specific as to say,
"This algorithm requires 5N^2 + 3N + 20 steps to process N items". Instead, when using Big-O, we will ignore the coefficients and lower order terms of the expression and say 
"This algorithm takes roughly N^2 steps to process N items". While less specific, this approach keeps the overall impression of the algorithm's worst-case efficiency.


## Finding the Big-O
In order to quickly find the Big-O, focus on the most frequently occuring operations. Let's workthrough an example.

Look at the following few lines of code:
```
int arr[n][n];

for (int i = 0; i < n; i++)
  for (int j = 0; j < n; j++)
    arr[i][j] = 0;
```
This algorithm is O(n^2). Here's how I thought about it
- The outer for-loop will be iterated over n times (max number in the loop condition)
- The inner for-loop will be iterated over n times (max number again)
- Since the inner for-loop is hitting its max during ever iteration of the outer for loop, we multiply their max number of iterations n x n to get n^2

## Challenge Problems
Find the Big-O of the following pieces of code (Answers are below each one)
______________________________________________________
```
for (int i = 0; i < n i += 2)
  sum++;
```
O(n)
______________________________________________________
```
for (int i = 0; i < q; i++)
  for (int j = 0; j < q; j++)
    sum++;
```
O(q^2)
______________________________________________________
```
for (int i = 0; i < n; i++)
  for (int j = 0; j < n*n; j++)
    sum++;
```
O(n^3)
______________________________________________________
```
k = n;
while (k > 1) {
  sum++;
  k = k/2;
}
```
O(logn)
______________________________________________________
```
for(int i = 0; i < n; i++) {
  int k = n;
  while (k > 1) {
    sum++;
    k = k/3;
  }
}
```
O(nlog3(n))...this should be read as "O of n times log base-3 n"
______________________________________________________
```
int i, sum = 0;

for (i = 0; i < n*n; i++)
  sum += i;

for (i = 0; i < n*n*n; i++)
  sum += i;
```
O(n^3)... if you think its n^2 + n^3 then you are interpreting it right! but remember that we do not care for lower order terms, so we always say O(n^3) in this case.
______________________________________________________
```
int searchArray(int arr[], int n, int forValue)
{
  for (int i = 0; i < n; i++ ) {
    if (arr[i] == forValue)
      return i;
  }
  
  return -1; // not found
}
```
O(n) 
______________________________________________________
```
void addItemToEndOfArray(int arr[], int &n, int addMe) {
  arr[n] = addMe;
  n = n + 1;
}
```
O(1)
______________________________________________________
```
void mystery(int n)
{
  for ( int q = 0; q < n; q++ )
    for (int x = 0 ; x < q ; x++)
      cout << “Waahoo!”;
}
```
O(n^2)

### If you had some trouble, here's an easy method to find the answer!
- STEP 1: Locate all the loops that DON'T run for a fixed number of iterations and determine the maximum number of iterations each loop could run for
- STEP 2: Turn these loops into loops with a fixed number of iterations, using their maximum possible iteration count
- STEP 3: Finally do your Big-O analysis

For example...
```
func(int n) {                                         func(int n) {
  for (int x = 0; x < n; x++) <--- STEP 1               for (int x = 0; x < n; x++)
    for (int j = 0; j < x*x; j++) <--- STEP 1             for (int j = 0; j < n*n; j++) // <--- STEP 2                O(n^3) //<--- STEP 3
      cout << "Burp!";                                      cout << "Burp!";
}                                                     }
```
## More Challenge Problems
```
for (int j = 0; j < n; j++)
  for (int k = 0; k < j; k++)
    sum++;
```
O(n^2)
______________________________________________________
```
for (int i = 0; i < q*q; i++)
  for (int j = 0; j < i; j++)
    sum++;
```
O(q^4)
______________________________________________________
```
for ( int i = 0; i < n; i++ )
  for ( int j = 0; j < i*i; j++ )
    for ( int k = 0; k < j; k++)
      sum++;
```
O(n^5)
______________________________________________________
```
for (int i = 0; i < p; i++)
  for (int j = 0; j < i*i; j++)
    for (int k = 0; k < i; k++)
      sum++;
```
O(p^4)
______________________________________________________
```
for ( int i = 0; i < n; i++ ) {
  Circ arr[n];
  arr[i].setRadius(i);
}
```
O(n^2)... don't forget that constructing an array of N items calls the constructor N times, once per item!
______________________________________________________
```
for (int i = 0; i < n; i++) {
  int k = i;
  while (k > 1) {
    sum++;
    k = k/2;
  }
}
```
O(nlogn)
## Big-O for Multi-Input Algorithms
When an algorithm relies on the input of two different variables, you have to account for both of them in your Big-O analysis. This is because either variable may end up dominating the other depending on how large they were to start. You still must eliminate the lower-order terms for each independent variable though.

For example, this function is O(c^2 + e)
```
void tinder(string csmajors[], int c, string eemajors[], int e) {
  for (int i=0; i < c ;i++)
    for (int j=0; j < c ;j++)
      cout << csmajors[i] << “ dates “ << csmajors[j] << endl;

  for (int m=0; m < c ; m++)
    cout << csmajors[m] << “ is still a nerd”;

  for (int k=0; k < e ;k++)
    cout << eemajors[k] << “ sits at home“
}
```

## Even more challenge problems
```
void bar( int n, int q ) {
  for (int i=0 ; i < n*n ; i++) {
    for (int j = 0; j < q; j++)
      cout << “I love CS!”;
  }
}
```
O(n^2 * q)
______________________________________________________
```
void bletch( int n, int q ) {
  for (int i=0 ; i < n ; i++)
    cout << “Muahahaha!”;

  for (int i=0 ; i < q*q ; i++)
    cout << “Vomit!”;
}
```
O(n + q^2)
______________________________________________________
```
void burp( int n )
{
  for (int i=0 ; i < n ; i++)
    cout << “Muahahaha!”;
  for (int i=0 ; i < n*n ; i++)
    cout << “Vomit!”;
}
```
O(n^2)
______________________________________________________
```
void barf( int n, int q ) {
  for (int i=0 ; i < n ; i++) {
    if (i == n/2) {
      for ( int k = 0; k < q; k++ )
        cout << “Muahahaha!”;
    } else {
        cout << “Burp!”;
    }
}
```
O(n + q)...we only run the inner loop just once, when "i" is equal to (n/2). We do not run the inner loop on all of the N items!
## STL Big-O Cheat Sheet
### Vector
- Inserting an item (top, or middle): `O(n)`
- Inserting an item (bottom): `O(1)`
- Deleting an item (top, or middle): `O(n)`
- Deleting an item (bottom): `O(1)`
- Accessing an item (top, middle, or bottom): `O(1)`
- Finding an item: `O(n)`

### List (aka Linked Lists)
- Inserting an item (top, middle*, or bottom): `O(1)`
- Deleting an item (top, middle* or bottom): `O(1)`
- Accessing an item (top, or bottom): `O(1)`
- Accessing an item (middle): `O(n)`
- Finding an item: `O(n)`

\* But to get to the middle, you may have to first iterate through X items, at cost O(x)

### Map
- Inserting a new item: `O(logn)`
- Finding an item:  `O(logn)`
- Deleting an item: `O(logn)`

### Queue and Stack
- Inserting a new item: `O(1)`
- Popping an item: `O(1)`
- Examining the top: `O(1)`

### Set
- Inserting a new item: `O(logn)`
- Finding an item: `O(logn)`
- Deleting an item: `O(logn)`



