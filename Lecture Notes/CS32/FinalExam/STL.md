# Standard Template Library (STL)
## Vector
**When to choose a vector**: Since vectors are based on dynamic arrays, they allow fast access to any element (via brackets) but adding new items is often slower.
- Think of it as an array that can grow and shrink automatically when you add/remove items
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
## List
**When to Choose**: Since the STL list is based on a linked list, it offers fast insertion/deletion, but slow access to middle elements
- `.push_back(...);` adds a new item to the end of a list
- `.front();` reads the first item in the list
- `.back();` reads the last item in the list
- `.popback()` removes an item from the back of the list
- `.size()` gets the current number of items in a list
- `.empty()` determines if the list is empty
- `.push_front(...)` adds a new item to the front of a list
- `.pop_front()` removes the front item of the list

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
## Map
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
## Set
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


