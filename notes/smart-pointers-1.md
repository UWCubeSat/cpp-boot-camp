# Smart Pointers, Part 1: unique pointers

Contributors: Edward Zhang

---
## The problem with raw pointers

Raw pointers are tricky to work with due to a variety of reasons

- Its declaration doesn't tell you if the pointer points to a single object or an array
  - ... do you use `delete` or `delete[]`?
- Its declaration doesn't tell you if the pointer owns the object it points to
  - ... should you destroy the pointed-to object after you're done using the pointer?
- Easy to cause dangling pointers (i.e., objects are destroyed but we still have pointers to them)
- Easy to cause double frees
- Easy to cause memory leaks

---
## Smart pointers to the rescue!

Smart pointers can help us!

A **smart pointer** is an object that stores a pointer to a heap-allocated object
- Think of them as wrappers around raw pointers
- Smart pointers look and behave like regular pointers

However, smart pointers can automatically delete the object to which it points, at the right time

Let's take a look at 3 kinds of smart pointers

---
## `std::unique_ptr`

A `unique_ptr` is a kind of smart pointer
- Use this for managing resources with exclusive ownership semantics
- Very little overhead, can be used even when memory is limited

Since it is a kind of smart pointer, a unique pointer will take ownership of a pointer to an object

The `unique_ptr`'s destructor will invoke `delete` on the owned pointer when the `unique_ptr` object is destroyed

General syntax:
```
std::unique_ptr<typeName> varName(p)
```
- Where `p` is a pointer of type `typeName*` to heap-allocated memory

Example:
```C++
#include <iostream> // std::cout, std::endl
#include <memory> // std::unique_ptr

void foo(){
  std::unique_ptr<int> x(new int(333));
  // You can dereference x as if it were a normal pointer
  *x += 20;
  std::cout << *x << std::endl;

  // No leaks, even though we never used delete!
  // When x falls out of scope, we run delete on its owned ptr
}

```

---
## `unique_ptr` Operations

For unique pointer `x`:

| Function 	| Purpose 	|
|---	|---	|
| `x.get()` 	| Returns a pointer to the pointed-to object 	|
| `*x` 	| Returns value of pointed-to object, basically normal dereference 	|
| `x.reset(ptr)` 	| Run `delete` on the current owned pointer, then store a new one, `ptr` 	|
| `x.release()` 	| Returns the pointer, sets wrapped pointer to `nullptr`- releases responsibility for explicitly freeing back to user 	|

Example:
```C++
#include <memory> // unique_ptr
#include <iostream> // cout
#include <cstdlib> // EXIT_SUCCESS

int main(){
  // x is a unique pointer that owns an int*
  std::unique_ptr<int> x(new int(333));

  // x.get() returns pointer to pointer-to object
  int* ptr = x.get();
  std::cout << *x << std::endl; // prints 333

  // delete current pointer, stores a new one
  x.reset(new int(124));
  std::cout << *x << std::endl; // prints 124

  // smart pointer releases responsibility for freeing back to user
  ptr = x.release();
  delete ptr;

  return EXIT_SUCCESS;
}

```

---
## `unique_ptr` is not copyable

As its name implies, `std::unique_ptr` cannot be copied
- Copy constructor and copy-assignment operator are disabled
- Compiler error if you try

Bugged example:
```C++
std::unique_ptr<int> x(new int(333));
std::unique_ptr<int> y(x); // Compiler error - cctor disabled

std::unique<int> z; // z is nullptr
z = x; // Compiler error - copy-assignment disabled

```

---
## Bug #1: double free

We've seen that you can't copy unique pointers, but you can still wrap the same raw pointer with multiple unique pointers. This causes a problem

Example:
```C++
int main() {
    int* p = new int(333);
    std::unique_ptr<int> x(p);
    std::unique_ptr<int> y(p);

    // What happens here at the end of main?
}
```
- Now both `x` and `y` "own" pointer `p`
- When `y` falls out of scope, it will call `delete` on `p`, which it owns
- But then when `x` falls out of scope, it also will call `delete` on `p`, which has already been deleted!
- Causes a double-free!

---
## Bug #2

Also remember that smart pointers are intended to wrap raw pointers to HEAP-ALLOCATED memory

You should never try to `delete` memory on the stack anyways

Bugged example:
```C++
int main(){
  int x = 333;
  std::unique_ptr<int> p(&x); // BUG
}
```
- This will still compile
- However, `&x` is a pointer to memory on the stack, so when the unique pointer tries to `delete` it will cause undefined behavior


---
## Transferring ownership

You can transfer ownership of a pointer from one `unique_ptr` to another using `release()` and `reset()` in combination

```C++
int main() {
    std::unique_ptr<int> x(new int(333));

    std::unique_ptr<int> y(x.release());
    // y now owns x's old pointer
    x.reset(new int(124));

    std::cout << *x << std::endl; // prints 124
    std::cout << *y << std::endl; // prints 333

}
```

You can also use move semantics (will cover later)

```C++
std::unique_ptr<int> x(new int(333));
std::unique_ptr<int> y = std::move(x);

std::cout << x.get() << std::endl; // prints 0
std::cout << y.get() << std::endl; // prints something like 0x602000000010
```

---
## `unique_ptr` and STL

Unique pointers can be stored inside STL containers
- Since `unique_ptr` supports move semantics, STL will move rather than copy

However if you try to sort, say a vector of unique pointers, you'll be sorting based on pointer address comparison, not the pointed-to objects

Instead, provide a custom comparator function

```C++
bool cmp(const unique_ptr<int> &x, const unique_ptr<int> &y) {
  return *x < *y;
}

void printFunction(unique_ptr<int> &x){
  cout << *x << endl;
}

int main(){
  vector<unique_ptr<int>> vec;
  vec.push_back(unique_ptr<int>(new int(333)));
  vec.push_back(unique_ptr<int>(new int(124)));

  // Warning: don't do this
  sort(vec.begin(), vec.end());
  // Do this
  sort(vec.begin(), vec.end(), &cmp);
  for_each(vec.begin(), vec.end(), &printFunction);
}
```

---
## `unique_ptr` and arrays

One last thing about unique pointers- they can also wrap arrays

```C++
std::unique_ptr<int[]> x(new int[5]);
```

When `x` is destroyed, it will call `delete[]` appropriately on its owned pointer

Note: instead of using a `std::unique_ptr` for arrays, it might be better to use `std::array` or `std::vector`

---
## Conversion to `std::shared_ptr`

`std::unique_ptr` can be converted into a `std::shared_ptr`
- More on shared points in [Smart Pointers Part 2](./smart-pointers-2.md)

For example, you can write a factory function that returns a unique pointer


---
## Moving on!

Just from looking at one type of smart pointer, the `unique_ptr`, we've resolved all of the issues described in the [first section](#the-problem-with-raw-pointers)

In the [next chapter](./smart-pointers-2.md), we'll look at another type of smart pointer, the `shared_ptr`