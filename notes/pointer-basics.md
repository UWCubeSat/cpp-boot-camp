# Pointers

Contributors: Edward Zhang

---
A **pointer** is a type of variable that stores an address

Pointers are most commonly used to indirectly access another object at some address
- Thus, a pointer "points" to whatever data is located at the address it stores

Example:
```C++
int x = 333;
int *p = &x;
// Print p's value. Here, it's the address of variable x
std::cout << p << std::endl;
// prints something like: 0x7fffb2cf5bc0
```

---
## Declaring a pointer

A pointer declaration gives our pointer variable a name and specifies the *type of object* to which our variable "points"

Generic definition: `typeName* variableName;`

Example:
```C++
int *p; // Pointer variable with name "p" points to some integer
std::string *p2; // p2 points to some string object

```
- Writing `typeName *variableName;` also works

---
## Setting the value of a pointer

A pointer stores the address of some object
- Thus a pointer variable's "value" is the address of some object, NOT the value of the object itself

You can get the address of an object using the **address-of operator (&)**

```C++
int x = 333;
int *p = &x;
```
- Now `p` holds the address of `x`, aka `p` is a pointer to `x`


Notice that the type of the pointer and the object to which it points must match

```C++
double x = 333;
int *p = &x; // Compiler error
```

You also shouldn't treat the value of a pointer as a number. For example, you cannot assign an int to a pointer like this:

```C++
int *p = 808; // Compiler error
```

---
## Dereferencing a pointer

So how do we actually access the object a pointer POINTS to?

We can use the **dereference operator (*)** to get the object to which the pointer points

```C++
int x = 333;
int *p = &x; // p points to x
std::cout << *p << std::endl; // prints 333

```

This means we can also assign to the object a pointer points to
- Only if the pointer is not `const` though

```C++
int x = 333;
int *p = &x;

*p = 124;
std::cout << *p << std::endl; // prints 124 now
```

---
## Null pointers

Null pointers do not point to any object
- I.e. they point "nowhere"

Dereferencing a null pointer will cause a segfault

To get a null pointer:
```C++
int *p = 0;
int *p2 = nullptr;
int *p3 = NULL;
// All 3 ways of initializing null pointer are basically equivalent

```
- C++ introduced `nullptr`, which has type `std::nullptr_t`
- C's `NULL` macro is defined by `cstdlib` as `0`
- However, `nullptr` avoids some ambiguity when resolving function overloads since `NULL` tends to get treated as an `int`

---
## Pointer arithmetic

You can perform arithmetic on pointers, for example:
```C++
char *p = ...
int *q = ...
long *r = ...

// Note: the "..." isn't valid C code, just filler
// For the purposes of the example, let's assume:
// p has value = 0x1000, q = 0x2000, r = 0x3000
// Remember the value of a pointer variable is some address

p += 3;
q += 3;
r += 3;

// What are the values of p, q, and r now?

```

Answer:
- `p = 0x1003, q = 0x2012, r = 0x3024`


Why?

First, the type of the object a pointer points to matters. In the above example, `q` points to an int object.

You might've already guessed the pattern. In general, for `typeName* ptrName`, the expression `ptrName + k` really evalutes to `ptrName + k * sizeof(typeName)`

So in the above example `r + 3` would be the same as `r + 3*sizeof(long) = r + 3*8 = 3000 + 24 = 3024`
- Intuitively, this means we are moving the pointer right by 3 `long`s worth of memory


---
## void* Pointer

The type `void*` is a special pointer type

Pointer variables of this type can hold the address of any object
- Basically the pointer holds an address, but we don't know the type of object at that address

```C++
int x = 333;
void *p = &x;

// Now p holds the address of x
// You could cast p to be an int pointer, then dereference it to get x's value
std::cout << *((int*)p) << std::endl;

```


---
Now let's examine some common use cases for pointers

---
## Output parameters

Remember that C/C++ passes arguments by value
- Thus the callee receives a local copy of the argument
- If the callee modifies a parameter, the caller's copy is NOT modified

Bugged example:
```C++
void foo(int x){
  x = 333;
}

int main(){
  int x = 351;
  foo(x);
  std::cout << x << std::endl; // what gets printed?
}

```
- Answer: `351` is printed! Updating `x` in function `foo` does not modify the caller (`main`'s) version of `x`

Solution: we can mimic pass-by-reference using pointers!
- Sure, the pointer VALUE (some address of an object) is passed by copy, but the address still indirectly gives access to the same object

Fixed example:
```C++
void foo(int *x){
  *x = 333;
}

int main(){
  int x = 351;
  foo(&x);
  std::cout << x << std::endl; // Now prints 333
}
```

---
## Dynamic Memory Allocation

Both `malloc()` and `new` allocate a block of memory on the heap, then return a pointer (if allocation succeeded) to the start of the block

```C++
int main() {
  int *p = new int(333);
  std::cout << *p << std::endl; // prints 333

  int *q = (int*)malloc(sizeof(int) * 3);
  q[1] = 124;
  std::cout << q[1] << std::endl; // prints 124

  free(q);
  delete p;
}
```