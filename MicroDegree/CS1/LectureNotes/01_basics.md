# Variables
Python is a **dynamically-typed** language. This means that when we create a variable,
we do not need to declare its type at all. 
```
n = 0
print('n =', n) # Outputs n = 0

n = "abc"
print('n =', n) # Outputs n = abc
```

Python also supports multiple assignments
```
n, m = 0, "abc"
n, m, z = 0.125, "abc", False
```

You can also increment a value in the following ways...
notice how you can't increment with `n++`!
```
n = n + 1
n += 1
```

`None` is null (absence of value)
```
n = 4
n = None
```
