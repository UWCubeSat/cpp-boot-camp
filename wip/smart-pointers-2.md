# Smart Pointers, Part 2

## `std::shared_ptr`

Let's look at shared pointers!

These are similar to unique pointers, but now we allow objects to be shared / "owned" by multiple shared pointers

---
## Reference counting

If multiple shared pointers can own an object, how do we know when to `delete` the pointed-to object?

Quite intuitively, we use the notion of **reference counting**. For each object, we keep a count of how many shared pointers are pointing at it

The reference count is adjusted like so:
- When we get a new pointer to the object, increment reference count by 1
- When shared pointer is destroyed, decrement reference count by 1

Finally, when the reference count is 0, destroy the pointed-to object

---
## Creating shared pointers

```C++
int main(){
  int *p = new int(333);
  std::shared_ptr<int> x(p); // reference count = 1

  // x falls out of scope and is destroyed, ref count = 0
  // Since ref count = 0, delete p
}
```

We just created a shared pointer that owns the integer object pointed to by `p`

How do we create new shared pointers to actually share ownership of `p`'s pointed-to object?
- We must create COPIES of

---
There are quite a few ways to accidentally trip yourself up when using smart pointers

Let's take a look at a few common casess

---
## Shared pointer troubles, Part 1
