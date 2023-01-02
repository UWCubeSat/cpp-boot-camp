# Inheritance, Part 2

In this chapter, we will finally be able to understand and predict the behavior of function calls

---
## Code

Let's revisit our good `Animal` friends. We'll be using and adapting the code quite a bit in this chapter

```C++
class Animal{
public:

    // Say "Hi!"
    void Speak(){
        std::cout << "Hi!" << std::endl;
    }

    virtual int Rank(){
        return 1;
    }
};

class Bun : public Animal{
public:

    virtual int Rank(){
        return 5;
    }

};

class KingBun : public Bun{
public:

    virtual int Rank(){
        return 10;
    }
};

void printRank(Animal &ani){
    std::cout << ani.Rank() << std::endl;
}
```

---
## Virtual functions

Time to finally define this elusive term for good!

A key idea behind polymorphism is that children can redefine existing behavior while preserving the interface
- For example, we know that `Animal` and its derived classes `Bun`, `KingBun` define `Rank()` differently


Sometimes though, we dont' expect or need a child class to redefine behavior. For example, in the above code, we assume that all `Animal`s know how to say "Hi!" Thus, all derived classes of `Animal` should be able to just inherit the original function without needing to change a thing

<br>


In C++, a base class distinguishes between functions that are type dependent and functions that it expects derived classes to inherit without change

We use the `virtual` keyword to denote functions that are intended to be redefined by derived classes

Example:
```C++
class Animal{
public:
    // We expect Rank() to be redefined in derived classes
    // of Animal
    virtual int Rank();
};

```

---
## A couple details about virtual

A base class can specify that a member function is `virtual`
- Constructors cannot be virtual
- Only nonstatic member functions can be virtual. This makes sense, since static functions are not associated with an object

The `virtual` keyword can only appear on the member function declaration inside the class, not on a function definition outside the class

Example:
```C++
class Animal{
public:
    // We expect Rank() to be redefined in derived classes
    // of Animal
    virtual int Rank();
};

// Don't write virtual here
int Animal::Rank(){
  return 1;
}

```

<br>

This is important. A function that is declared `virtual` in the base class is implictly `virtual` in the derived classes as well
- This is true even if we don't declare the function as `virtual` in a derived class

Example:
```C++
class Animal{
public:
    // Now Rank() will forever be virtual
    // in all children/grandchildren, etc. of Animal
    virtual int Rank(){
        return 1;
    }
};

class Bun : public Animal{
public:

    // You can omit virtual, but Rank() will
    // always be virtual
    int Rank(){
        return 5;
    }

};

class KingBun : public Bun{
public:

    // Still virtual!
    int Rank(){
        return 10;
    }
};

```
- Good practice to reduce some potential confusion and just put `virtual` again

Intuitively, this fact makes sense as well. If we want to redefine a function for a child of some base class, it's likely we'll want to redefine the function again for some grandchildren, etc.

---
## Function Calls

Now that you know what `virtual` functions are, let's finally look at function calls

Here, we'll learn how to answer the all-important question: "What function body will be executed when I call a function?"

I'm going to introduce one last pair of terms: static dispatch and dynamic dispatch

---
## Static dispatch vs. dynamic dispatch

**Static dispatch** happens when we know at COMPILE-TIME which function body will be executed when we call a function

**Dynamic dispatch** happens when we select at RUN TIME which function body will be executed when we call a function
- Dynamic dispatch is the mechanism that enables dynamic polymorphism

<br>

So, when does static dispatch happen? I.e., when would we immediately be able to figure out, at compile time, which function to execute?

Let `x` be some variable of type `T` and `foo()` be a function. If I call `x.foo()`, when does static dispathc happen?

There are 3 cases:
1. `x`'s type `T` is neither a reference nor pointer
    - Then, as we saw in the last chapter, there is nothing that will change the type of object to which `x` corresponds.
    - For example, in `Animal a`, variable `a` is always be an object of type `Animal`. It can never correspond to a `Bun` or `KingBun` object
    - Then, at compile-time we know to call the version of `foo()` that `T` holds
