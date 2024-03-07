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
.cpp

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

Operations
- `.push_back(...);` adds a new item to the end of a vector
- `.front();` reads the first element in the vector
- `.back();` reads the last element in the vector
- `vals[i]` accesses the ith elment of the vector (can only be used to access existing elements...cannot be used to add new items to the end)
- `.popback()` removes an item from the back of the vector
- `.size()` get the current number of elements in a vector (remember this function does not work for arrays!)
- `.empty()` determine if the vector is empty

```
.cpp

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
