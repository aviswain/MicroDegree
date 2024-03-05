# Hash Tables

Hash tables are used for faster insertion, deletion, and searching (on average when compared to a binary search tree). They don't keep their elements in order though.

**Quick Facts**
- They are Implemented as an array of linked lists
- To search, insert, and delete items in our hash table we use the modulo function (%) to pick our "bucket" in the array. We then add/find/erase the item in that bucket's linked list
- They have roughly O(1) performance for adding, finding, and erasing items

## How is the efficiency of a Hash Table measured?

By the Load Factor. The load of a hash table is defined as L = (Max number of values to insert) / (Total buckets in the array). 
For example, L = 0.1 means your items fill 10% of the buckets. Ideally, we want L < 1.0 (have some open space left after inserting all items), but its not required.

Given a particular load, L, we can compute the number of steps it will take to add/find/erase the average item in you hash table by peforming (# of steps) = 1 + L/2.

If we want to find any item in roughly 1.25 steps and we have 1000 items to store, then we set the equation up by 1.25 = 1 + L/2 and solve for L. 
Then we use the L formula to solve for the "total buckets".

**Tradeoff**: If you make a really big has table you can ensure really fast searches but you'll end up wasting lots of memory. 
On the other hand, if you make a really small hash table, it'll be slower to operate on.

## Hashing

This all makes sense until we want to create a hash table for strings (or other things that don't really have remainders). 
How are we supposed to compute the remainder for strings using %? This is where a **hash function** comes into play. It is basically a function that takes some sort of input, such as a string,
and generates a unique integer from it as an output.

We can use the hashing function written by C++ to make our own mapping function:

```
cpp

#include <functional>

unsigned int yourMapFunction(const std::string &hashMe) {
  std::hash<std::string> str_hash;            // creates a string hasher!
  unsigned int hashValue = str_hash(hashMe);  // now has our string!

  // then just add your own modulo
  unsigned int bucketNum = hashValue % NUM_BUCKETS;
  return bucketNum;
}

```

If you want to write a function like this but for a non-standard data type (like coordinates for shape, an array of n numbers, contents of a file) your best bet is to 
first convert the data into a string and then use it in the same hashing function above.

**When choosing a hashing function...**

- The hash function must always give the same output for a given input. In other words, It should not change based on any other circumstances other than the input.
- The hash function should disperse items throughout the array as randomly as possible. hash("abc") should not be the same as hash("cba").
- When coming up with a new hash function, always measure how well it disperses items. (don't want any peaks in your graph of items per bucket)

## Traversing a Hash Table

"TRAVERSAL?! Why would I ever want to traverse unordered data?" 

Maybe because you want to check if something in your table exists or not.

But keep in mind, if we just looped through all the buckets and traversed its linked list whenever its not empty, it would be highly inefficient. So what we do is create a secondary linked list that
links all the nodes. This allows us to traverse in O(N) time by going through the larger linked list. This does mean that while inserting and deleting items in our hash table, we will
have to set extra pointers...but these are just O(1) operations.

## Can you make an O(N) ordered traversal of the values?
Hell No. Else this shit would be too good. 

Seriously though, this is the big downside of hash tables. You get O(1) operation, but no ordering like with trees.

## Hash Tables vs. Binary Search Trees

**Hash Tables**

Speed: O(1) regardless of the number of items

Simplicity: Easy

Max Size: Not limited, but high load ends up impacting performance

Space Efficiency: Wastes a lot of space if you have a large hash table holding a few items

Ordering: None

**Binary Search Trees**

Speed: O(log2(n))

Simplicity: Complex

Max Size: Unlimited

Space Efficiency: Only uses as much as needed (one node per item)

Ordering: Alphabetical


