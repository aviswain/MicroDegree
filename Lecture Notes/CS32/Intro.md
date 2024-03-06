# Intro

**Abstract Data Type (ADT)** : A group of data structures, algorithms, and interface functions that work together to serve a common purpose
- The data structures and algorithms are kept "secret", while the interface enables the rest of the program to use it
- Typically programs are built from a collection of different ADTs, where each solves a different sub-problem
- In C++, we use classes to define ADTs in our program...the rest of the program will access it through the class' public interface while ignoring its
  implementations that exist under the hood
- If we wanted to make some radical change to the implementation of our ADT, the rest of the program will remain unaffected since it only knows about
  its public interface and none of its private inner-workings.

**Object Oriented Programming (OOP)**: a model of programming based around the concept of ADTs
- Programs might have multiple classes that communicate with each other by using public interface functions...while knowing nothing about how the others work on the inside!

## Defining and using a new Class
Some things to note before looking at the code below:
- Creating a class makes a new data type for your program like `string`, `int`, or `double`, not a variable
- Normally, we define each new class in its own .h file (header file) and put the file in the same folder as your .cpp files
- The header file will typically only contain class declarations and constants, while the .cpp file contains the class function bodies and implementations
- You can define variables with your class throughout your program. Whenever you do, each instance of the variable gets its own copy of all the functions and member variables
  inside the variable itself
- When you are working throughout your program keep in mind the scope of different variables. Private member variables and functions of a class will only be accessible through the class' member
  functions. Functions in the public interface of your class will be accessible from anywhere, once you have included an instance of your class to the program. Hiding the internal implementation
  details of a class is called "**encapsulation**". It makes your program simpler!

```
cpp
// Nerd.h (header file)

class Nerd {
  public:
    
    Nerd(int stink, int IQ) {} // constructor

    void study(int hours) {}

    int getStinkyLevel() {}

private:
    int m_Stinkiness;
    int m_IQ;
};
```
```
cpp
// Nerd.cpp (source file)

Nerd::Nerd(int stink, int IQ) {
  m_Stinkiness = stink;
  m_IQ = IQ;
}

void Nerd::study(int hours) {
  m_Stinkiness += 3 * hours;
  m_IQ *= 1.01;
}

int Nerd::getStinkyLevel() {
  int total_stink = m_IQ * 10 + m_Stinkiness;
  return total_stink;
}
```
```
cpp
// example main.cpp file

int main() {
  int num_nerds = 1;
  Nerd david(30, 150);
  david.study(10); // calling a function from the public interface of Nerd!
}
```

**Other details about classes**
- The primitive member variables of a class (ints, doubles, etc. like m_Stinkiness and m_IQ) will start out uninitialized and with random values in them.
  You constructor's jobis to initialize them
- You only should use member variables to store permanent attributes of your class (ones that you'd like to retain over time). Don't make member variables for temporary computations
