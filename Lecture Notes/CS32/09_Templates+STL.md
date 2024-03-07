# Generic Programming
Generic Programming is when you write a function or class in a way that allows it process different data types. Think of a sorting function that can sort an array that holds any
type of value (string, int, double, whatever). Or a linked list class that can hold any type of variable. Generic Programming is often used in programs to speed up the development since
it increases reusability and can be used to solve many different problems.

## Concept #1 : Custom Comparison Operators
We have always been able to compare variables like integers and doubles with >, <, >=, <=, ==, != . But what if we wanted a way to compare objects (two instances of a class)
that we have created? Can we do that?

Of course we can!

Things to note before reading the code below:
- All comparison operators must return a boolean value and take **const reference** parameters
- If you are defining your comparison operator outside your class, then you need two parameters, one for each of the two operands
- If you are defining inside your class make sure it is a **const** member function and takes in a single "other" parameter. This will be used to refer to the object that is on the right side of the operator.
  (If a < b, b is on the right side and should be the one referred to by "other"). Also when defining inside your class, you are able to access private member variables for your comparisons.
  You cannot do this if defining outside your class and will need to use getter functions to access certain values.

```
.cpp

class Dog {
  public:
    bool operator<(const Dog &other) const {
      if (m_weight < other.m_weight)
        return true;
      return false; // otherwise
    }

    int getWeight() const {
      return m_weight;
    }
    ...
  private:
    int m_weight;
}

bool operator>=(const Dog &a, const Dog &b) {
  if (a.getWeight() >= b.getWeight())
    return true;
  return false; // otherwise
}
```
Other details to keep note of:
- If your comparison operator is a const member function of your class, it can only call other **const** functions in Dog. So make sure to make your getter functions,
  like getWeight(), **"const"**.
- Defining an operator like == does not automatically define other operators like != for you. You have to define each one explicity. (But you can be smart about it! For example, if you
  implemented the < operator, then to do an operation involving > all you have to do is flip the operands around and still use the < operator. No need to make define another operator!)

## Concept #2: Templates
Lets say you are making a bunch of different classes, and for each class you want a way of swapping two instances of the class. But you don't want to keep having to implement the swap
function for each class if it looks the same!

The Problem:
```
.cpp

void SwapCircle(Circ &a, Circ &b) {
  Circle temp;
  temp = a;
  a = b;
  b = temp;
}

void SwapDog(Dog &d1, Dog &d2) {
  Dog temp;
  temp = d1;
  d1 = d2;
  d2 = temp;
}

int main() {
  Circle a(5), b(6);
  Dog c(100), d(750);

  SwapCircle(a,b);
  SwapDog(c,d);
}
```
Wouldn't it be so much better if we could do this?
```
.cpp

int main() {
  Circle a(5), b(6);
  Dog c(100), d(750);
  int e = 5, f = 10;

  OurGenericSwap(a,b);
  OurGenericSwap(c,d);
  OurGenericSwap(e,f);
}
```

Well we can! And this is how...
- STEP 1: Add the following line to your function (xxx can be called anything you want): template \<typename xxx>
- STEP 2: Use "xxx" as your data type throughout the function
```
.h

template <typename xxx> 
void swap(xxx &a, xxx &b) { 
  xxx temp;
  temp = a;
  a = b;
  b = temp;
}
```
Keep the following in mind when "templatizing":
- Always place your templated functions in a header file! This means the ENTIRE template function body (not just the prototype) should be in the .h file
- Templates do not reduce the size of your program. Instead they work more like a "copy and paste". A new version is generated everytime you use the template function on a
  different type of variable
- If a function has two or more templated parameters, with the same type (e.g. xxx) you must pass in the same type of variable for both. You cannot pass in an int for "a" and a float
  for "b" in the swap function above
- The template data type ("xxx" in our example) should be define at least one variable in the **parameter list** of your functions. You cannot for example make a function that
  returns a template data type but takes in only integers
BAD/NON-EXAMPLE:
```
template <typeName xxx>
xxx getRandomItem(int a) { 
  // CANNOT DO THIS!
}
```
- If your program passes objects of a specific data type into a templated function that uses <, >, <=, >=, ==, !=, then make sure that those objects have the comparison operator        already implemented for them. (or else the objects will have no way of comparing themselves to each other)

### Multi-type Templates
You can also do this too!
```
.h
template <typename T, typename U>
void passTwoTypes(const T& first, const U& second) {
  cout << "First: " << first << "Second: " << second << endl;
}
```
```
.cpp

int main() {
  passTwoTypes(123, "Hello World!");
  passTwoTypes(3.14, 42);
}
```

### Template Classes
You can make generic classes too. This allows your class to hold any data type just like the C++ stack and queue classes.
```
.h

template <typename xxx>
class HoldOneValue {
  public:
    void setVal(xxx a) {
      m_a = a;
    }
    void printTenTimes() {
      for (int i = 0; i < 10; i++) {
        cout << m_a << endl;
      }
    }
  private:
    xxx m_a;
}
```
In another file...this works
```
.cpp

int main() {
  HoldOneValue<int> v1;
  v1.setVal(10);
  v1.printTenTimes();

  HoldOneValue<string> v2;
  v2.setVal("ouch");
  v2.printTenTimes();
}
```

If your class has externally defined functions, things can get really ugly. But its still possible. (Can you believe that this is doing the same work as the template class above?!)
```
.h

template <typename xxx>
class Foo {
  public:
    void setVal(xxx a);
    void printVal();
  private:
    xxx m_a;
};

template <typename xxx>
void Foo<xxx>::setVal(xxx a) {
  m_a = a;
}

template <typename xxx>
void Foo<xxx>::printVal() {
  cout << m_a << endl;
}
```
The process of doing the above, if you really want to know...
- Add the prefix `template <typename xxx>` before the class definition and each function definition outside the class.
- Update the types to use your templated type
- Place the suffix `<xxx>` between the class name and the `::` in all the function definitions.

Template classes are super useful when we are building container objects like linked lists!

## Professor Nachenberg's Template Cheat Sheet
_This is yet another god-gifted infinity stone handed to us by the rock-climbing, illenium-listening, programming god himself, Carey Nachenberg. Use this one to turn anything into a template!_
- To templatize a non-class function called bar:
  1. Update the function header: `int bar(int a)` -> `template<typename ItemType> ItemType bar(ItemType a);`
  2. Replace the appropriate types in the function to the new ItemType: `{int a; float b; ...}` -> `{ItemType a; float b; ...}`
- To templatize a class called foo:
  1. Put this in front of the class declaration: `class foo {...};` -> `template <typename ItemType> class foo{...};`
  2. Update appropriate types in the class to the new `ItemType`
  3. Update internally-define methods:
     a. For normal methods

## The Standard Template Library (STL)
The STL is a collection of pre-written, tested classes by the authors of C++. The classes are built using templates, meaning they can be used with many different data types.
They can be used to save hours of programming!

We have already seen a couple STL containers such as Stacks and Queues...
```
#include <stack>
#include <queue>
using namespace std;

int main() {
  stack<int> is;
  queue<string> sq;

  is.push(5);
  is.push(10);
  ...
  sq.push("goober");
  ...
}
```
Here are some other cool containers...
### Vector
Quick Facts
- Just think of it as an array that can grow and shrink automatically when you add/remove items
- All initial elements are automatically initialized and constructed (for example, a vector of ints will start out with its values initialized to zero)
- Internally, vectors are implemented using dynamically allocated arrays. This means once you add enough elements, the vector will object will need a bigger allocated array. So when
  it does, it will allocate a larger array, copy over all the values, and delete the old smaller array. So once in a while, it might take a long time to just "add" an element to the
  vector.

Operations
- `.push_back(...);` adds a new item to the end of a vector
- `.front();` reads the first element in the vector
- `.back();` reads the last element in the vector
- `vals[i]` accesses the ith elment of the vector (can only be used to access existing elements...cannot be used to add new items to the end)
- `.popback()` removes an item from the back of the vector
- `.size()` gets the current number of elements in a vector (remember this function does not work for arrays!)
- `.empty()` determines if the vector is empty

**When to choose a vector**: Since vectors are based on dynamic arrays, they allow fast access to any element (via brackets) but adding new items is often slower.

```
#include <vector>
using namespace std;

int main() {
  vector<string> strs;
  vector<int> nums;
  vector<Robot> robots;
  vector<int> geeks(950); // starts out with 950 integers, all initialized to zero

  vector<string> strs;
  strs.push_back("Carey");
  strs.push_back("Scott");
}
```
### List
- `.push_back(...);` adds a new item to the end of a list
- `.front();` reads the first item in the list
- `.back();` reads the last item in the list
- `.popback()` removes an item from the back of the list
- `.size()` gets the current number of items in a list
- `.empty()` determines if the list is empty
- `.push_front(...)` adds a new item to the front of a list
- `.pop_front()` removes the front item of the list

Notice that you cannot use brackets to access elements of a list!

**When to Choose**: Since the STL list is based on a linked list, it offers fast insertion/deletion, but slow access to middle elements

```
#include <list>
using namespace std;

int main() {
  list<float> lf;

  lf.push_back(1.1);
  lf.push_back(2.2);
  lf.push_front(3.3);
}
```

### Map
- Maps allow us to associate two related values. For example, a map can associate a string to an int. But if you do make one in this way, you cannot then use the same map to
  associate int to string. You must make a second map.
- A map class works by storing each association into a struct variable.
- Maps are maintained in alphabetical order based on the keys (no sorting required!)... so if your "first" data type is an object/class variable, you must define the < operator for
  it so that the STL code knows how to maintain the map's order. 
```
#include <map>
#include <string>
using namespace std;

int main() {
  map<string,int> name2Age;
  name2Age["Carey"] = 49;
  name2Age["Dan"] = 22;
  name2Age["David"] = 53;

  name2Age["Carey"] = 39; // updates Carey's associated int from 49 -> 39
}
```

### Set
A set is a container that keeps track of unique items. Like a map, it is also alphabetically sorted! So if you make a set of objects/class variables, you need to also define the 
< operator for that class.
- `set<int> a;` defines the container
- `.insert(...);` inserts an item into the set (if you try to insert a duplicate, it gets ignored)
- `.size();` gets the size of the set
- `erase(...);` erases a specific member of the set
```
#include <set>
using namespace std;

int main() {
  set<int> a;
  a.insert(2);
  a.insert(3);
  a.insert(4);
  a.insert(2); // duplicate, so gets ignored
  cout << a.size();

  a.erase(2);
}
```
## Passing Containers to Functions
When passing STL containers to functions, pass them by **const reference** when you don't want them to be modified and **reference** when you want to modify them. Don't pass them by value though because it will just create a copy of the whole container to operate on, which is slow.
```
void printVec(const vector<int>& v) {
  for (int i = 0; i < v.size(); i++)
    cout << v[i] << endl;
}
```
Also, when you pass a container into a function as a const reference parameter, you can't use a regular iterator on it. You have to use a const iterator like this...
```
void tickleNerds(const list<string>& nerds) {
  list<string>::const_iterator it;
  for(it = nerds.begin(); it != nerds.end(); it++) {
    cout << *it << " says teehee!\n";
}
```

## Iterating Through STL Containers
Except for the vector, none of the STL containers have an easy way of iterating through items (vector can use brackets `[]` to access elements). So what do we do?

### Use an Iterator variable
An iterator variable is like pointer but just for STL containers. You start by pointing it to some item in your container and then you increment and decrement it to move it up/down
through a container's items. You can also use it to read/write each value it points to.

Iterator example code:
```
.cpp

int main() {
  vector<int> myVec;
  myVec.push_back(1234);
  myVec.push_back(5);
  myVec.push_back(7);

  vector<int>::iterator it;

  it = myVec.begin();
  while (it != myVec.end()) {
    cout << (*it);
    it++;
  }

}
```
Keep in mind:
- `myVec.end()` points just **past** the last item. If `.end();` pointed at the last item, then loops would miss the last item! If you want to point your iterator to the last item,
  first do `it = myVec.end();` and then decrement it once by `it--;`.

### Searching an STL map or set (not iterating)
- `.find(...)` locates the pair in the map/set based on the value (looks at key-value for maps). If it cannot be found, it returns an iterator that points to the end of the map/set.
- `first` refers to the key in the key-value pair
- `second` refers to value in the key-value pair
```
#include <map>
#include <string>
using namespace std;

int main() {
  map<string,int> name2Age;
  ...
  map<string,int>::iterator it;

  it = name2Age.find("Dan");

  cout << it->first;
  cout << it->second;

  it = name2Age.find("Ziggy");
  if (it == name2Age.end()) {
    cout << "Not found!\n";
    return;
  }

}
```
If you are using an iterator on a STL container holding classes or structs:
```
int main() {
  list<Nerd> nerds;
  Nerd d;

  nerds.push_back(d);
  list<Nerd>::iterator it;
  it = nerds.begin();

  (*it).beNerdy(); // either of these options work!
  it->beNerdy();   // (*it).function() OR it->function()
}
```

What exactly is an **iterator** anyways?
Although an iterator sort of works like a pointer, it's not one. An iterator is an object (class variable) that knows the following three things...
1. What element it points to
2. How to find the previous element in the container
3. How to find the next element in the container
Depending on the container its operating on, these actions will be implemented in different ways.

## Invalidated Iterators (after Deleting/Adding to an STL container)
Most STL containers have an `erase()` method you can use to delete an item. First search for the item you want to delete and get an iterator to it. Then, if you found the item, use the `erase()` method to remove the item pointed to by the iterator. If you remove items with an iterator, it will be invalidated (because the container's size has been changed). To fix that, make sure to set your iterator equal to the erase statement, because your erase statement actual returns an iterator to the new variable in that spot!

Here are two ways of fixing the invalidated pointer of erasing an item with it:
```
void removeOdd(list<int>& li) {
    
    list<int>::iterator it;
    
    for(it = li.begin(); it != li.end();){
        if (*it % 2 == 1)
            it = li.erase(it);
        else
            it++;
    }
}
```
```
void removeOdd(vector<int>& v) {
    vector<int>::iterator it;
    it = v.begin();
    
    while (it != v.end()) {
        if (*it % 2 == 1)
            it = v.erase(it);
        else
            it++;
    }
}
```
If you add an item to the container after creating an iterator for it, then that iterator is invalidated and cannot be used after. This is because adding item might cause the container, such as a vector, to need to move all of items to a new part in memory for more space.
## STL Algorithms
STL also provides some additional functions (not all are mentioned here) that you can access by `#include <algorithm>`:
- `find()` can search most STL containers and arrays for a value
- `sort(...,...)` can sort arrays/vectors/lists for you! To use it, you pass in two iterators: one that points to the first item, and one that points just past the last item. This
  can also be used on arrays (just pass in the address values for the first item and just past the last item). You can even have the function sort the container in a specific way for
  you (see below).
```
#include <algorithm>

class Dog {
  public:
    int getBark() { return m_barkVolume; }
    int getBite() { return m_bitePain; }
};

// Make a function that returns...
// TRUE if dog A should go BEFORE dog B
// FALSE if dog A should go AFTER dog B
bool customCompare(const Dog &a, const Dog &b) {
  return a.getBark() > b.getBark();
}

int main() {
  Dog arr[4] = {...};

  // pass in the address of customCompare function as the 3rd parameter to sort
  sort(arr, arr+4, &customCompare); 
}
}
```
## Compound STL Data Structures
You can combine multiple STL containers to represent all sorts of complex associations. For example, let's say you want to maintain a list of courses for each UCLA student. How could you do this with STL? You could create a map between a student's name and their list of courses!
```
#include <map>
#include <list>

class Course {
  public:
    ...
};

int main() {
  map<string, list<Course>> crsmap;

  Course c1("cs","32"), c2("math","3b"), c3("english","1");

  crsmap["carey"].push_back(c1);
  crsmap["carey"].push_back(c2);
  crsmap["david"].push_back(c1);
  crsmap["david"].push_back(c3);
}
```



