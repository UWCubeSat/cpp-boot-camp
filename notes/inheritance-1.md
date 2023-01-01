# Inheritance, Part 1

Contributors: Edward Zhang

---

Buckle up for inheritance! This multi-part series will cover many of the intricacies of inheritance in C++

Structure for this series:
1. First, let's build some intuition for what inheritance is, why we might want it, and some key inheritance/OOP concepts
2. Next we'll look at function calls in the context of inheritance. I.e., when we invoke a function call, what function is actually executed?
3. Finally, we'll examine the fine details of implementing inheritance in C++

---

## What is inheritance?

Inheritance is a fundamental idea in OOP. Using it, we can elegantly capture parent-child relationships between classes

What is a parent-child relationship? I like to think about it as an "is-a" relationship. Specifically, a child "is a" type of its parent, typically more specialized

Examples:
- A Tesla "is a" Car
- A Husky "is a" Dog
- LOST "is a" StarTracker
- [Korosensei](https://ansatsukyoshitsu.fandom.com/wiki/Korosensei) "is a" Teacher

<br>

In C++, we call a parent class the **base class**, and a child class the **derived class**

---
## Why would we want inheritance?

There are quite a few benefits that arise from using inheritance when appropriate:
- **Polymorphism**: children can redefine existing behavior while preserving the interface
    - Example: all 2D shapes have area. A circle is a shape, but we redefine its area to be $\pi r^2$
- Code reuse: children can automatically inherit functionality from their parents without having to rewrite the same code over and over
    - Example: pretend that all Animals can say "Hi". Then there's no point in rewriting this code for every derived class of `Animal`
- Extensibility: children can specify / add new behavior
    - Example: a Korosensei is a teacher, but can also fly at Mach 20


---
## Setup

Throughout this series on inheritance, let's use the following class hierarchy, appropriately based on rabbit hierarchy in this excellent [xkcd series](https://xkcd.com/1682/)
- By the way, [wild rabbit hierarchy](http://www.bunnyhugga.com/a-to-z/rabbit-behaviour/rabbit-hierarchy.html) is well documented and surprisingly detailed

![](../images/bun.png)
> Title text: If a wild bun is sighted, a nice gesture of respect is to send a 'BUN ALERT' message to friends and family, with photographs documenting the bun's location and rank. If no photographs are possible, emoji may be substituted.

<br>

So, we can come up with our class hierarchy as such:

Class `Bun` derives from base class `Animal`

Class `KingBun` derives from class `Bun`

<br>

Code for these classes will be shown later


---
## Setup code

Let's write out some very basic code for our example classes: `Animal`, `Bun`, and `KingBun`

We will build the code step by step in the following sections and chapters


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
```

---
## Code details

I want to point out a few details in the code above

A derived class must specify the base class it wishes to inherit from. A derived class specifies its parent(s) in the **class derivation list**

General syntax:
```
class childClassName : public parentClassName {...};
```
- Thus, `childClassName` inherits from base class `parentClassName`

We are making some assumptions that will be addressed later, namely:
- Assume that the access specifier for the base class is `public`
- In C++, derived classes are allowed to directly inherit from multiple base classes, called multiple inheritance. For now, assume single inheritance

<br>

Next, notice that some functions are marked `virtual` while some are not. This distinction is super important, we will examine this closely in the next chapter

---

## Example: motivation for polymorphism

As programmers, we're rightfully reluctant to write redundant code

Say we wanted to write a function that printed out an animal's rank. We could implement something like this:

```C++
void printRank(Animal a){
    std::cout << a.Rank() << std::endl;
}

void printRank(Bun b){
    std::cout << b.Rank() << std::endl;
}

void printRank(KingBun kb){
    std::cout << kb.Rank() << std::endl;
}

// etc... for all derived class of Animal

```
- Basically we're abusing function overloading

This isn't great - you can see that code is repeated a lot. This would be super tedious and unmanageable once you started making more derived classes of `Animal`

<br>

Wouldn't it be nice if we could write ONE version of `printRank()` that can process objects of either type `Animal`, `Bun`, `KingBun`, and any other derived classes of `Animal`?

Let's do that here:
```C++
void printRank(Animal &ani){
    std::cout << ani.Rank() << std::endl;
}
```
What did we change?
- We just made the parameter `ani` a reference to our desired base class (in this case `Animal`)
- We didn't change this, but notice that the function `Rank()` is `virtual`
- We will learn how exactly this works later. For now, it's sufficient to know that a solution to our redundancy problem exists

Now, we can call the function like this:
```C++
int main(){
    Animal a;
    Bun b;
    KingBun kb;
    printRank(a); // prints 1
    printRank(b); // prints 5
    printRank(kb); // prints 10
}

```
- Yay, code reuse! This is a lot cleaner and satisfies our needs

---
## Polymorphism

The key concept behind all of this is polymorphism

Through polymorphism, a single entity (e.g., a variable, function, or object), can have multiple forms. Most importantly, this allows us to treat objects, which may be of different types, in the same exact way
- A whole host of benefits arises from using polymorphism: less redundancy, more understandable/modifiable code, etc.

We used this concept to great effect in the above example. Instead of writing the same function for each object of base type `Animal`, we wrote code that allows us to treat all objects of type `Animal` or one of its derived classes in the same exact way!

---
## Types of polymorphism

There are 2 main types of polymorphism: static polymorphism and dynamic polymorphism

You've probably seen a lot of **static polymorphism**, also called **compile-time polymorphism**. This is just regular function overloading!
- When multiple functions have the same name but different signatures, the compiler will pick which one to call based on the arguments passed
- This happens at compile-time

<br>

**Dynamic polymorphism**, also called **runtime polymorphism**, is what happened in the earlier `printRank` example. Sometimes, for reasons we will examine in the next chapter, the compiler doesn't know which version of a function to call until runtime

Here's another way to put it: sometime, the correct function to call can only be determined at runtime, depending on the actual type of object that the function is called on
- When we called `printRank()` in `main()`, notice how we were able to pass (as an argument) an object of either type `Animal`, `Bun`, or `KingBun`
- In `printRank()`, the parameter `ani` has type `Animal&`. We then invoke the virtual function `Rank()` on `ani`
- Now, which class's `Rank()` function do we call? It depends on the actual type of object being passed in for `ani`!
- This step can only happen at runtime - our compiler does not know what the actual type of `ani` is until we start running the program and calling the function with arguments


---
## Dynamic dispatch

**Dynamic dispatch** is the mechanism that enables dynamic polymorphism. It is a mechanism for selecting which implementation of a function to call at runtime

---
Whew! That was a lot of conceptual material. Let's now [move on to the next chapter](inheritance-2.md) and make all of this make sense.