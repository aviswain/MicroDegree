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

If you want to write a function like this but for a non-standard data type (like coordinates for a shape, an array of n numbers, contents of a file) your best bet is to 
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

| | Hash Tables | Binary Search Trees |
|:---|:---:|:---:|
| Speed | O(1) regardless of # of items | O(log2(N)) |
| Simplicity | Easy to implement | More complex to implement |
| Max Size | Not limited, but high load impacts peformance* | Unlimited Size |
| Space Efficiency | Wastes a lot of space if you have a large hash table holding few items | Only uses as much memory as needed (one node per item) |
| Ordering | No ordering (random) | Alphabetical ordering |

\*If you end up needing to expand your hash table's size you have to...
1. Allocate a whole new array with more buckets
2. Rehash every value from the original table into the new table
3. Free the original table

# Tables
Here is some terms to understand before we move forward...

- **Record**: a group of related data 
- **Table**: a bunch of records put together
- **Key Field**: a field that is unique across all records

An example for a record could be someone's name, phone number, along with their birthday, etc. A key field for this type of record could be their social security number, because while some people have the same name or birthday, nobody has the same SSN.

## How would you create a record and a table of records in C++?

You could just use a struct or class to represent a record of data and then you can simply create a vector or array of your struct for the table!

Here is an example of a record and table with some functions you might implement for them:
```
cpp

// RECORD

struct Student {
  string name;
  int ID;
  float GPA;
  string phone;
};

// TABLE (made as a class, so we can make some special functions for it...
class TableOfStudents {
  public:
    TableOfStudents();                                          // Constructor
    ~TableOfStudents();                                         // Destructor
    void addStudent(Student &stud);                             // add a new Student
    Student getStudent(int s);                                  // retrieve Students from slot s

    int SearchByName(vector<Student> &table, string &findName)  // algorithm to search by the "name" field
    {
      for (int s = 0; s < table.size(); s++) {
        if (findName == table[s].name)
          return(s); // the student you're looking for is in slot s
      }
      return(-1);    // didn't find that student in your table
    }

    int SearchByPhone(vector<Student> &table, string &findPhone) // algorithm to search by the "phone" field
    {
      for (int s = 0; s < table.size(); s++) {
        if (findPhone == table[s].phone)
          return(s); // the student you're looking for is in slot s
      }
      return(-1);    // didn't find that student in your table
    }

  private:
    vector<Student> m_students;
};
```

Our searching seems to be highly inefficient though. If we have a lot of student records, linear searching through them might not be very optimal...

## How can we make our table more efficient?

**Not So Great Solution**

Alphabetically sort our vector by the "name" field and then use binary search to quickly locate a record based on a student's name. The problem with this
is that we have to re-sort the whole table everytime we add a new record. Also if we sort by name, we can't search our efficiently by any other field like phone number or ID number.

**Slightly Better Solution** 

Store our records in a binary search tree organized by name. Now we can search the table efficiently by name without having to re-sort everytime we add a record. But we still can't search efficiently by any other field.

**Good Solution**

Create two binary search trees, ordering the first by name and the second by ID number. This works and we can finally find people by their name or ID number. But now we have two copies of every record, one in each tree...if the records are big, that's a waste of space.

**Best Solution for Making an Efficient Table**
1. Still use a vector to store all of our records (so don't change to binary search tree)
2. Add another data structure to associate each person's name with their slot number in the vector
3. Add another data structure to associate each person's ID number with their slot number in the vector

This should look like...
```
cpp

class TableOfStudents {
  public:
    TableOfStudents();
    ~TableOfStudents();
    void addStudent(Student &stud);
    Student getStudent(int s);
    int searchByName(string &name);
    int searchByPhone(int phone);
  private:
    vector<Student> m_students;
    map<string, int> m_nameToSlot;
    map<int, int> m_idToSlot;
    map<int, int> m_phoneToSlot;
}
```

These secondary data structures are called "indexes". They let us quickly find a record by using a particular field to locate which slot its in. We may have as many indexes as we need for our application. So how does this change our code?

Here's what `addStudent()` might look like now...
```
void addStudent(Student &stud) {
  m_students.push_back(stud);
  int slot = m_students.size()-1; // get slot# of new record
  m_nameToSlot[stud.name] = slot; // maps name to slot number
  m_idToSlot[stud.ID] = slot;     // maps ID number to slot number
}
```
Also keep in mind that any time you delete a record or update a record's searchable fields, you also have to update your indexes!

## Making Smart Choices
In the above example, we used binary search trees to index our table's fields. But you can use any efficient data structure you like. Even a hash table! This might be super nice because then you can always have O(1) searches by name! 

But what if you want to print out at all students alphabetically by their name?

In this case a binary search tree would make it look easy, while a hash table would require a lot more work to do the same thing. 

To make the best choice here, it is important to understand how your table is going to be used. For example, a binary search tree for names would be smart (cause of alphabetical order) and a hash table for phone numbers would be good (cause ordering doesn't help much when searching for a phone number).


