# Construction and Destruction

**The Big Picture**
- Construction is the process of initializing a new object for use when its first created
- Destruction is the process of freeing the memory and resources used by an object when its lifetime ends

## Understanding Construction
### Concept #1: Phases of Construction
1. _We'll learn this later!_
2. C++ constructs all non-primitive member variables (e.g. strings) in the order they appear in the class
3. C++ runs the body {...} of your constructor

If you don't explicity define a constructor for your class then C++ provides a hidden **default constructor** with no parameters for you and initialization goes 
through the same process above. 

Example Code and Resulting Output 
```
cpp

class Stomach {
  public:
    Stomach() {
      cout << "Empty stomach!" << endl;
    }
};

class Colon {
  public:
    Colon() {
      cout << "Nothing to digest!" << endl;
    }
    makeNoise() {
      cout << "grumble...";
    }
};

class Intestine {
  public:
    Intestine() {
      cout << "Empty guts!" << endl;
      m_digestion.makeNoise();
    }
  private:
    Colon m_digestion;  
};

class Constipated {
  public:
    Constipated() {
      cout << "But can't poop!";
    }
  private:
    Stomach m_tummy;
    Intestine m_guts;
}

int main() {
    Constipated david; // WHAT DOES THIS OUTPUT??
}
```
Before looking at the output, notice how the Intestine class has an instance of the Colon class as a member variable within it. When we do this in programs, it is called 
**class composition**.

OUTPUT:
```
Empty stomach!
Nothing to digest!
Empty guts!
grumble...
But can't poop!
```

You might find yourself wondering why C++ constructs member variables before running the constructor. This is done to ensure the member variables are initialized before 
they are used by the code in the constructor body. If we didn't do this, the constructor could end up trying to operate on something that hasn't been created yet. Think about it!
If the phases didn't go in this order, class composition wouldn't work (in the example above, the line `m_digestion.makeNoise();` wouldn't work since m_digestion hasn't been 
initialized yet).

### Concept #2: Initializer Lists






