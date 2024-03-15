# Templates
- To templatize a non-class function called bar:
  1. Update the function header: `int bar(int a)` -> `template<typename ItemType> ItemType bar(ItemType a);`
  2. Replace the appropriate types in the function to the new ItemType: `{int a; float b; ...}` -> `{ItemType a; float b; ...}`
- To templatize a class called foo:
  1. Put this in front of the class declaration: `class foo {...};` -> `template <typename ItemType> class foo{...};`
  2. Update appropriate types in the class to the new `ItemType`
  3. Update internally-define methods:
      - For normal methods, just update all types to ItemType: `int bar(int a){...}` -> `Itemtype bar(ItemType a){...}`
      - Assignment operator: `foo &operator=(const foo &other)` -> `foo<ItemType>& operator=(const foo<ItemType>& other)`
      - Copy constructor: `foo(const foo &other)` -> `foo(const foo<ItemType> &other)`
  4. For each externally defined method:
      - For non inline methods: `int foo::bar(int a)` -> `template <typename ItemType> ItemType foo<ItemType>::bar(ItemType a)`
      - For inline methods: `inline int foo::bar(int a)` -> `template <typename ItemType> inline ItemType foo<ItemType>::bar(ItemType a)`
      - For copy constructors: `foo::foo(const foo &other)` -> `foo<ItemType>::foo(const foo<ItemType> &other)`
      - For assignment operators: `foo &foo::operator=(const foo &other)` -> `foo<ItemType>& foo<ItemType>::operator=(const foo<ItemType>& other)`
  5. If you have an internally defined struct blah in a class: `class foo {...struct blah {int val;};...}`:
     a. Simply replace appropriate internal variables in your struct (e.g. `int val;`) with your ItemType (e.g. `ItemType val;`)
  6. If an internal method in a class is trying to return an internal struct (or a pointer to an internal struct):
     a. You don't need to change the function's declaration at all insde the class declaration; just update variables to your `ItemType`
  7. If an externally-defined method in a class is trying to return an internal struct (or a pointer to an internal struct):
     a. Assuming your internal structure is called "blah", update your external function bar definitions as follows:
      - `blah foo::bar(...){...}` -> `template<typename ItemType>typename foo<ItemType>::blah foo<ItemType>::bar(...) {...}`
      - `blah *foo::bar(...){...}` -> `template<typename ItemType>typename foo<ItemType>::blah *foo<ItemType>::bar(...) {...}`
- Try to pass templated items by const reference if you can (to improve performance):
  - Bad: `template <typename ItemType> void foo(ItemType x)`
  – Good: `template <typename ItemType> void foo(const ItemType &x)`

## Custom Comparison Operators
- All comparison operators must return a boolean value and take **const reference** parameters
- If you are defining your comparison operator outside your class, then you need two parameters, one for each of the two operands
- If you are defining inside your class make sure it is a **const** member function and takes in a single "other" parameter. This will be used to refer to the object that is on the right side of the operator.(If a < b, b is on the right side and should be the one referred to by "other"). Also when defining inside your class, you are able to access private member variables for your comparisons. You cannot do this if defining outside your class and will need to use getter functions to access certain values.

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
