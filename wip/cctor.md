# Copy Constructor

Contributors: Edward Zhang

---
## Introduction

Let's talk about copy constructors! If you're coming from Java, this might be one of the biggest changes

C++ has the notion of a copy constructor, appreviated `cctor`

The cctor is a special type of constructor that creates a new object as a copy of some existing object

It's important to remember that in C/C++, almost everything is passed by value. This means that for better or worse, the cctor is quite frequently invoked, sometimes when you might not expect it.

---

## cctor implementation

For the rest of this chapter, let's use the `Node` class as an example

```C++
class Node{
public:
  int val;

  Node(int val);
  Node(const Node& other); // This is the copy constructor
};
```

We can see that the first parameter of a cctor is a REFERENCE to some existing object of the same type
- ... why must it be a reference? We'll come back to this at the end of the chapter

<br>

Here is what one implementation of the cctor could look like:
```C++
Node::Node(const Node& other){
  val = other.val;
}
```

The code is very straightforward! As its name implies, we simply construct a new object by making copies (whatever that means to you) of some existing object's data members

---
The next few sections will examine when the copy constructor is invoked. There are 3 main cases

---
## cctor invocation case #1

This is a fairly common case.