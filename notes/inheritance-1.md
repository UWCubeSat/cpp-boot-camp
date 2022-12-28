# Inheritance, Part 1

Contributors: Edward Zhang

---

Buckle up for inheritance! This multi-part series will cover many of the intricacies of inheritance in C++

---

## What is inheritance?

Let's quickly recall what inheritance is, and later, why we might want it

Inheritance is a fundamental idea in OOP. Using it, we can elegantly capture parent-child relationships between classes

What is a parent-child relationship? I like to think about it as an "is-a" relationship. Specifically, a child "is a" type of its parent
- See the next section for what child classes can also do

Examples:
- A Honda "is a" Car
- A Husky "is a" Dog
- LOST "is a" StarTracker
- A [Korosensei](https://ansatsukyoshitsu.fandom.com/wiki/Korosensei) "is a" Teacher
    - you are required to read this article

<br>

In C++, we call a parent class the **base class**, and a child class the **derived class**

---
## Why would we want inheritance?

There are quite a few benefits that arise from using inheritance when appropriate:
- Code reuse: children can automatically inherit functionality from their parents without having to rewrite the same code, over and over
    - Example: as you know, all animals can say "Hi", so there's no need to rewrite the same code in every child class of Animal
- Polymorphism: children can redefine existing behavior while preserving the interface
    - Example: a circle is a shape, but we redefine its area equation to be $\pi r^2$
- Extensibility: children can specify / add new behavior
    - Example: a Korosensei is a teacher, but can also fly at max speed of Mach 20


---
## Setup

Throughout this series on inheritance, let's use the following class hierarchy
- Based on this excellent [xkcd post](https://xkcd.com/1682/)

![](../images/bun.png)
> Title text: If a wild bun is sighted, a nice gesture of respect is to send a 'BUN ALERT' message to friends and family, with photographs documenting the bun's location and rank. If no photographs are possible, emoji may be substituted.

Class `Bun` derives from base class `Animal`

Class `KingBun` derives from class `Bun`

<br>

Code for these classes will be shown later

---
## Virtual Functions

Polymorphism is an important idea. Basically, there will be base class member functions that you want to redefine in some derived class
- Example: the `rank()` of a `Bun` might be 5, but we want to define the `rank()` of a `KingBun` to be 10

Such a function is called a **virtual function**

<br>

In C++, a base class distinguishes between functions that are type dependent and functions that it expects derived classes to inherit without change

We use the `virtual` keyword to denote functions that are intended to be redefined by derived classes

---
## Some code for our example classes

Let's write out some basic code for our example classes: `Animal`, `Bun`, and `KingBun`



