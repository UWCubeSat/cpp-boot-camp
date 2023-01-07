# Compilation and Linkage

Contributors: Tri Nguyen

## Introduction

Let's say I'm a structural engineer. I've made a drawing for a bridge, and I tell you to build it. How? Are you just gonna build it from left to right? Are you gonna build it part by part, and then assemble it?

If you've used Eclipse/PyCharm/VSCode/etc., you make your program, press a button, and it magically runs. But how? In C/C++, it looks like this (prepare yourself):

<div style="text-align: center">

![](../images/g%2B%2B-compilation-process-1.PNG)

Figure 1 - C/C++ Compilation

</div>

Just like how building a bridge will have a structured process, so will any language for compiling its program.

**QUICK NOTE**: You may have noticed by now that C++ is compatible with C syntax, but not the other way around. The first 2 steps will be described with examples specific to C, but do note that C++ does the same thing, but it must use a different system (The C++ Native Compiler) which allows for the use of C++ specific-syntax.

## The C Preprocessor

For a bridge, let's say that one of the components is a beam. Me, the engineer, will need to draw out all the components of the beam. There might be things like screws, wires, and metal pieces that will be layed out in the drawing. 

Likewise, as the coder, we must lay out all the necessary packages, functions, and definitions for our programs to run. The Preprocessor helps out with this a lot by simplifying the process.

The C Preprocessor is a text-replacement program that modifies your code before it is converted into other forms. It contains registers/variables to keep track of certain things throughout the lifetime of its use.

### Preprocessor Directives

The preprocessor allows for the use of so-called "directives", which are various statements that do different things.

#### Import (`#include`)

This is quite a simple statement, which simply includes a file. To utilize the contents of a file, all you have to do is the following:

<div style="text-align: center">

`#include <libraryFile>`

or

`#include <libraryPath>`

</div>

You may have also created files that require access to definitions within other files you also created. In that case, you should use the following syntax

<div style="text-align: center">

`#include "myFile"`

</div>

Be wary that some libraries have files without `.c`, `.cpp`, `.h` or `.hpp`. Also note that you can never include an entire folder of C/C++ files. The reason being that whenever an `#include` directive occurs, it will replace it with the code in that file. That's right, no matter how big that file is, it will copy and paste it into your file, and folders don't directly contain code, so including a folder is not possible.

#### Macros (`#define`, `#undef`)

Macros are custom literals that have a value associated with them. Whenever you use these macros, the preprocessor replaces them with the value specified. You can sort of think of them as constant variables, if that helps. Here is an example of making some macros:

```C
// #define VARIABLE_TYPE_MACRO_NAME MACRO_VALUE

#define PI 3.1415926535
#define LOST "AND FOUND"
```
<div style="text-align: center"> 

Figure 2a - Declaration of `#define` directive  for variable-type macros

</div>

The C preprocessor will make variables for each of these directives, with the appropriate name and value. You can use these names as if they are constants in the files where it is defined. Below is the use of this in the `snyder.c`

```C
#define PI 3.1415926535
#define LOST "AND FOUND"

#include <printf.h>

int main() {
    float area = 2 * 2 * PI;
    printf("The perimeter of a circle with a radius of 2m is: %dm\n", area);
    printf("LOST %s", LOST);
    return 0;
}
```
<div style="text-align: center"> 

Figure 2b - Use of the `#define` directive for variable-type macros

</div>

Technically, definitions will have a scope that starts at `#define` and ends at `#undef`. However, if `#undef` is not specified, the scope will last until the end of the program.

What actually happens here is that the preprocessor will replace every instance of `PI` and `LOST` with their literal values. So let's say that the program processes `synder.c` into `processedSynder.c`:

```C++
// Code inside of printf.h goes here

int main() {
    float area = 2 * 2 * 3.1415926535;
    printf("The perimeter of a circle with a radius of 2m is: %dm\n", area);
    printf("LOST %s", "AND FOUND");
    return 0;
}
/* Output:
 * The area of a circle with a perimeter of 2m is: 12.5663706m
 * LOST AND FOUND
**/
```
<div style="text-align: center"> 

Figure 2c - Preprocessing of directives for variable-type macros

</div>

If you are on Linux, you can actually run the preprocessor with the `cpp` command on the terminal:

```Unix
# cpp [optionalFlags] fileToBePreProcessed outputFile

cpp snyder.c processedSnyder.c
```
<div style="text-align: center">

</div>

<div style="text-align: center"> 

Figure 2d - Preprocessing of directives via terminal commands for variable-type macros

</div>

You can also define function-type macros, which are text-replacers that need an input to replace text

```C
// #define FUNCTION_TYPE_MACRO_NAME(VARIABLE_1, ..., VARIABLE_N) VALUE

#define AREA(x) x * x
#define STATISTICS(a, b) \
        int difference = a - b; \
        printf("a minus b is: %d", difference);
// Use "\" after every line to make a multi-line macro
```
<div style="text-align: center"> 

Figure 3a - Declaration of `#define` directive  for function-type macros

</div>

In this case, all parameters of the function-type macro are variable-type macros that recieve values, and those values will replace the variable-type macros every time the function-type macro is called. Below, the file `sigplan.cpp` uses the above macros.

```C
#define AREA(x) x * x
#define STATISTICS(a, b) \
        int difference = a - b; \
        printf("a minus b is: %d", difference);

#include <printf.h>

int main() {
    printf("A square with a side length of 4m has an area of %f meters squared", AREA(4));
    STATISTICS(9, 4)
    return 0;
}
```
<div style="text-align: center"> 

Figure 3b - Use of `#define` directive  for function-type macros

</div>

The preprocessor will use a search and replace as usual, and the resulting file, called `processedSigplan.c`, will look like the following:

```C
// Code for printf.h

int main() {
    printf("A square with a side length of 4m has an area of %f meters squared", 4 * 4);
    int difference = 9 - 4;
    printf("a minus b is: %d", difference);
    return 0;
}
```
<div style="text-align: center"> 

Figure 3c - Preprocessing of `#define` directive  for function-type macros

</div>

---
Problem 1: Create a list of float variables that have the following names and values: (Forty, 39.9), (Seventy, 70.4), (OneHundred, 101)

Answer:
```C
#define MAKE_VAR(name, value) float name = value;

int main() {
    MAKE_VAR(Forty, 39.9)
    MAKE_VAR(Seventy, 70.4)
    MAKE_VAR(OneHundred, 101)
    return 0;
}
```
---

As the function-macro suggests, you can nest different macro definitions within each other. For example, the X-Macro is a powerful tool that can quickly make many variable definitions or do other things. 

```C
// #define VARIABLES \
   X(argValue1, argValue2, ..., argValueN) \
   ...                                     \
   X(argValueM, argvalue2M, ..., argValueNM)
// #define X(param1, param2, ..., paramN) value
//     VARIABLES
// #undef X

#define VARAIBLES \
    X(VSCode, 5, 1.74) \
    X(Eclipse, 4, 4.26)\
    X(jGrasp, 1, 2.06) \

#include <printf.h>

int main() {
    #define X(ide, number, version) int ide = number;
        VARIABLES
    #undef X

    #define X(ide, number, version) printf("Current Version: %f", version);
        VARIABLES
    #undef X
    return 0;
}
```
<div style="text-align: center"> 

Figure 4a - Use of `#define` directive for X-Macros

</div>

Here, we need `#undef` so that we can reuse the macro `X`. When the preprocessor processes this, this becomes:

```C
// code for printf.h

int main() {
    int VSCode = 5;
    int Eclipse = 4;
    int jGrasp = 1;

    printf("Current Version: %f", 1.74);
    printf("Current Version: %f", 4.26);
    printf("Current Version: %f", 2.06);
    return 0;
}
```
<div style="text-align: center"> 

Figure 4b - Preprocessing of `#define` directive  for X-Macros

</div>

---
Problem 2: Create a list of float variables that have the following names and values: (Forty, 39.9), (Seventy, 70.4), (OneHundred, 101). Use X-Macros this time to make life easier (maybe).

Answer:
```C
#define VARS \
        MAKE_VAR(Forty, 39.9) \
        MAKE_VAR(Seventy, 70.4) \
        MAKE_VAR(OneHundred, 101) \

int main() {
    #define MAKE_VAR(name, value) float name = value;
        VARS
    #undef MAKE_VAR
    return 0;
}
```
---

As one can see, Macros are very useful. However, since the preprocessor just replaces text, it is VERY type-unsafe.

---
Problem 3: What's wrong with the following code?
```C
#define VARS \
        MAKE_VAR(Forty, 39.9) \
        MAKE_VAR(Seventy, 70.4) \
        MAKE_VAR(OneHundred, 101) \

int main() {
    #define MAKE_VAR(name, value) int name = value;
        VARS
    #undef MAKE_VAR

    #define MAKE_VAR(name, value) printf("Number %s", name);
    return 0;
}
```

Answers:
1. No `#include <printf.h>` has been included (Did you miss that?)
2. None of the `value`s are integers, so making integer variables out of them will cause a lousy conversion error.
3. `name` is not a string literal, so trying to print it out as one will cause a type error as well.
---

#### Conditionals (`#if`, `#else`, `#elif`, `#ifdef`, `#ifndef`, `#endif`)

Finally, we have conditionals. `if`, `else` and `elif` are equivalent to `if()`, `else()` and `else if()`, but they are for testing preprocessor macros. We can actually use all the same operators inside of the directive.


```C
// #if/#elif CONDITION
//      STATEMENTS
// #if/#elif CONDITION
//      STATEMENTS
// ...
// #elif CONDITION or #else
//      STATEMENTS
// #endif

#define MEEP  1
#define SHMOON  2

#include <printf.h>

#if MEEP == 1
    #define THIRD_DIRECTIVE 4

int main() {
    #if MEEP == 0
        printf("Meep is 0");
    #elif SHMOON == 2
        #include <malloc.h>
    #else
        #define A_BETTER_DIRECTIVE 3
    #endif
}
```
<div style="text-align: center">

Figure 5 - Conditional Directives

</div>

A few things to note here:

1. Usability - The conditional directives are usable anywhere, and I can put anything in their bodies, so long as its valid
2. Functionality - It works just like any other conditional, whether it contains code or not, the bodies will only run if the condition is true.
3. Closing - All conditional structures must be closed with `#endif`, but this only needs to be placed at the very end of the conditional structure.

There is a unique thing you can do, and it is to see whether certain directives have been defined or not. There are many ways to do this. On the left the condition tests whether it is defined, and on the right, whether it is not defined.

<div style="text-align: center">

`#if defined DIRECTIVE | #if !defined DIRECTIVE`

or

`#if DIRECTIVE == 0 | #if DIRECTIVE != 0`

or

`#ifdef DIRECTIVE | #ifndef DIRECTIVE`

</div>

The last one is the most common one to do since it is the most condensed. It works just like any conditional, but only in the preprocessor is the operator `defined` introduced. It is done so to accommodate this kind of test. 

A word on these options:
1. The last option is the condensed form of the first, so when the preprocessor reads it, it converts to the first option.
2. The second option is a consequence of the lack of directive types. Non-existent or undefined directives point to a null, or zero space.
3. This operation only works on macros, or preprocessor directives using `#defined`.

### Header Files

There are a few issues with pure C/C++ files:

1. Including other C/C++ files can be bad, especially if they are large, as the preprocessor will copy and paste those files
2. If we are designing a system, how do we ensure it is complete? In other words, how do we make sure all classes/functions are implemented?
3. Trying to avoid the first problem can cause us to `#include` the same thing in multiple files. Ideally, there should be as little places to repeat directives.

We can solve this with header files (.h/.hpp). These are also C/C++ files, and technically both .h/.hpp and .c/.cpp files can do the same thing, with the exception that explicit calls to the compiler can only occur on .c/.cpp files. 

So what's the point? Header files are special C/C++ files where we state all preprocessor, class, function, and type definitions. The class and function definitions are then implemented by the corresponding .c/.cpp file, usually of the same name. Its a little bit like a Java interface, if that helps at all, except its not strictly for a class.

Let's look at an example implementation. Here we have `point.hpp`, `point.cpp`, and `pointMain.cpp`

```C++
#define SHIFT_X = 4;
#define SHIFT_Y = 5;

#include <iostream>
#include <string>

struct point {
    std::string name;
    int x;
    int y;
};

point DefaultTranslate();

point Translate(std::string name, int xShift, int yShift);

void printString(point p);
```
<div style="text-align: center">

Figure 6a - `point.hpp`

</div>

```C++
#include "point.hpp"

point Translate(std::string name, int xShift, int yShift) {
    if(xShift == 0 && yShift == 0) {
        return DefaultTranslate(name);
    } else {
        return {name, x + xShift, y + yShift};
    }
}

point DefaultTranslate(std::string name) {
    return {name, x + SHIFT_X, y + SHIFT_Y};
}

void printString(point p) {
    std::cout << "Coordinate Points for" << p.name << ": (" << x << ", " << y << ")" << std::endl;;
}
```
<div style="text-align: center">

Figure 6b - `point.cpp`

</div>

```C++
#include "point.hpp"

int main() {
    point myPoint = {"myPoint", 3, 10};
    myPoint = Translate(myPoint.name, 0, 0);
    printString();
}
/* Output:
 * Coordinate Points for myPoint: (7, 15)
**/
```
<div style="text-align: center">

Figure 6c - `pointMain.cpp`

</div>
A few things happen due to this "abstraction"

1. Readibility - My program makes a lot more sense when I read it. My `point.hpp` tell me what the file does, and my `point.cpp` is just implementation information. Also, my `point.cpp` file only has one directive, which is just the `#include point.hpp` statement.
2. Access - Because of the `#include point.hpp`, my `point.cpp` can access any directives inside of `point.hpp`, and so can other files now too by doing the same, like `pointMain.cpp`.
3. Order - The ordering of function/class defintions no longer matter. As long as `#include point.hpp` goes at the top, their definitions can be seen by all entities.
4. Memory - When the preprocessor runs, `point.cpp` and `pointMain.cpp` will have less code copied at the top of their programs.
5. Completeness - `point.hpp` helps us make sure that we implement everything inside of it. It doesn't give an error if we don't, but there are tools out there that will tell you whether things inside of `.hpp` files have been implemented yet.

However, what if included `iostream` in `pointMain.cpp`? Assuming that it doesn't have what we're about to talk about next, this will cause `iostream` to be repeated inside of `main.cpp`, which is a big problem. So, developers have created something called a header guard, WHICH YOU MUST USE!!! This will prevent the preprocessor from including a file twice within a given piece of code. To use a header guard, you can employ the following to all your .hpp files

```C++
/*
#ifndef HEADER_FILE_NAME (All Caps is the convention)
#define HEADER_FILE_NAME

// Your code

#endif
*/
#ifndef POINT_H
#define POINT_H

#define SHIFT_X = 4;
#define SHIFT_Y = 5;

#include <iostream>
#include <string>

struct point {
    std::string name;
    int x;
    int y;
};

point DefaultTranslate();

point Translate(std::string name, int xShift, int yShift);

void printString(point p);

#endif
```
<div style="text-align: center">

Figure 7 - The Header Guard

</div>

This allows for header files, or any C/C++ file for that matter, to be copied only once per preprocessed file. Another way to do this is with the `#pragma` directive (This isn't common practice for LOST, so don't do it in HSL). It only requires a single declaration at the top of your program

<div style="text-align: center">

`#pragma once`

</div>

Anyway, with all that in mind, the preprocessor will operate exactly the same, but can now copy and paste `.hpp` files into `.cpp` files. You can imagine what `pointMain.cpp` looks like in a C++ preprocessor

```C++
// code for iostream
// code for string

struct point {
    std::string name;
    int x;
    int y;
};

point DefaultTranslate();

point Translate(std::string name, int xShift, int yShift);

void printString(point p);

int main() {
    point myPoint = {"myPoint", 3, 10};
    myPoint = Translate(myPoint.name, 0, 0);
    printString();
}
/* Output:
 * Coordinate Points for myPoint: (7, 15)
**/
```
<div style="text-align: center">

Figure 8 - C++ Preprocessing with `.hpp` files

</div>

But wait, how do we know what the function definitions are? Well, you'll have to find out in the next steps!

## Compilation

After you make your drawings of all the fundamental parts to your bridge, you need to tell your manufacturers how to create each part. You need to tell them in a way that will make sense to them, as engineering and manufacturing will use different terminology to describe the same thing. The compilation achieves this between the coder and the computer by translating code into instructions that are understood to the computer.

After the preprocessor runs, the files we end up with are precursors to what is called a *translation unit*. This is a file that at minimum defines all entities used within a single file, and for the purposes of the coder, the *translation unit* that we understand is what is in the preprocessed file. It is everything that would be in each `.c/.cpp` file after the preprocessor runs.

After the generation of each translation unit, the translation units are then processed a few more times, but the most notable intermediate processing that occurs is the translation of the files from C/C++ to Assembly code, or .asm. These are very basic instructions that talk directly to the registers of your computer how to run your code (You'll get to see it if you look it up or if you have/will take CSE 351).

After this, the each translation unit is then converted to binary, which is actually understandable by the machine itself. These are stored into Object files (.o or .obj), which is what any compiler will need to run code.

To both preprocess and compile, there are defined commands to help you do this. For C:

<div style="text-align: center">

`gcc [optionalFlags] -c yourCFile.c -o outputObjectFile.o`

</div>

For C++:

<div style="text-align: center">

`g++ [optionalFlags] -c yourCFile.cpp -o outputObjectFile.o`

</div>

Both will run the preprocessor (or some derivative of that) and compiler your objects at the same time.


It should be noted that the ommision of the `-o outputObjectFile.o` in any of these will still produce an object file with the same name as your C/C++ file. In fact, it is customary to always name your object files the same as your source code file.

## Static Linking

Back to the bridge analogy, your manufacturers have now created each part! However, the functionality of some of the parts does not make sense individually. There might be a protrusion, hole, fillet, or chamfer that each manufacture made, but they don't really know what the purpose of it. You do though, those features are supposed to function with the other parts, so your job now is to tell them how to assemble the bridge, how to use each feature they made. 

The final step in the compilation process, called linking, will assemble all your object files together into a single executable (.exe), and then you'll be perfect to run. We must bind all files together and map all necessary definitions to memory before the computer can run the program. When that's done, all the definitions and instructions in your code will be mapped to a memory location in your computer, and all translation units that interact with any given definition/instruction will have knowledge over them via the memory address (forshadowing).

To do this, your compiler will need to assemble all your created object files, along with any object files related to the libraries you used, to create this executable. In Linux, we can once again do this via the command prompt. For C:

<div style="text-align: center">

`gcc [optionalFlags] -o executableName objectFile1.o objectFile2.o ... objectFileN.o [otherLibraries]`

</div>

For C++:

<div style="text-align: center">

`g++ [optionalFlags] -o executableName objectFile1.o objectFile2.o ... objectFileN.o [otherLibraries]`

</div>

You can even do this entire compilation in 1 single step, replacing your object files with .c/cpp files. For C:

<div style="text-align: center">

`gcc [optionalFlags] -o executableName objectFile1.c objectFile2.c ... objectFileN.c [otherLibraryFlags]`

</div>

For C++:

<div style="text-align: center">

`g++ [optionalFlags] -o executableName objectFile1.cpp objectFile2.cpp ... objectFileN.cpp [otherLibraryFlags]`

</div>

All the code you wrote is resolved, it no longer needs to be translated by the machine to run a given segment of code. To run this code, all you need to do is

<div style="text-align: center">

`./executableName`

</div>

By default, anything used within the standard library (STL) also be linked into your program. More specifically, it is statically linked to your executable. This means that your program will carry of copy of all the information you need to interact with the STL library. So at compile time, or when your computer finishes this entire process, libraries that are statically linked to your executable will be mapped to your program's memory along with the code you also wrote. This allows for quickly acessing those definitions/instructions defined in those libraries.

---
Interactive Problem 4:

In the exercise folder, look for this chapter, and cd into this folder (If you are using Linux).

Inspect these files. you will notice that:
- `keep.cpp` increments an integer parameter `num` by 1 (It accomplishes this by passing by reference)
- `meep.cpp` prints out meep a specified number of `times`
- Both `keep.cpp` and `meep.cpp` have header files corresponding to them. These files have header guards.
- `main.cpp` uses these files to run. This does not need a header file.

a) Compile each file (Produce their .o files)
b) Link the .o files into an executable named `prog`
c) Run the executable. What is the output?
d) Compile and link the files all in one step.


Answers:

a) The following commands can be run:

`g++ -c keep.cpp -o keep.o` or `g++ -c keep.cpp`

`g++ -c meep.cpp -o meep.o` or `g++ -c meep.cpp`

`g++ -c main.cpp -o main.o` or `g++ -c main.cpp`

b) The following command should be run (For your object file name of course)

`g++ -o prog main.o keep.o meep.o`

c) Running `./prog` will produce the following output:

Meep! Meep! Meep! Meep! 
Meep! Meep! Meep! Meep! Meep! Meep! 

d) To compile and link all in one go, we just replace the `.o` in part b) with the actual source code:

`g++ -o prog main.cpp keep.cpp meep.cpp`

Now, I want you to run `make`, and watch as it automatically does this. If you want to get rid of the object files, run `make clean`. This is due to the magic of `Makefile`, a special kind of file that uses variables and rules to run terminal commands. For many projects, this included `Makefile` will be what you mostly need, so you're welcome.

**WARNING:** If you have done this through git, do not commit and push to master!

---


## Dynamic Linking

**NOTE:** This section is optional, but it would be good for you to learn how this is done. In reality, there are many ways of doing dynamic linking, so take the next few instructions with a grain of salt.

After this, your program is in its final form! You can run your program and it will be fine! However, there are some disadvantages to statically linking a libarary:

1. Memory for the Program - Libraries tend to be long and take up much space in your program's memory space.
2. Memory across Programs - If multiple programs are running at the same time, all of them will require a copy of the exact same library.
3. Use - The library might not even be used for the majority of the program.

To solve this, C++ introduces a cool feature called dynamic linking. This is a process by which a singular memory space, seperate from the program, is created that any program can use to run. To compile a dynamic library, the same steps are followed, up until the creation of the object file. At compilation, two things happen:

1. The compiler creates a space within the computer's memory that stores the binary code for the given library. This is represented by an object file, so the object file does still get created.
2. The compiler then creates a special object file, a shared library object file (.so or .dll) that contains references to that space in memory. We will refer to this as the shared library.

There are a good many ways to do this step, and it varies with what you intend to do with that shared library. However, the simplest way is shown below.

Typically, you should make a seperate file that contains everything you intend to put into your shared library, into a `.c/.cpp` file (You may also use a header file, just as long as its related to a .c/.cpp file). Unless there is a module you can use to avoid the following syntax, your file that represents this library must use a special structure:

```C++
// Any Directives

#ifdef __cplusplus
   extern “C” {
#endif

// Include Directives
// Class Declarations
// Function Declarations
// Other Declarations

#ifdef __cplusplus
   }
#endif
```
<div style="text-align: center">

Figure 9 - How to declare a file representing your external library

</div>


Some notes here:
1. The `ifdef/endif` guards are there to prevent multiple definitions of the external library, which is defined as everything within this `extern C {}` structure.
2. Using `#include` outside of the structure allows you to declare individual entities within `extern C {}`, while doing it inside will declare all entities contained in your included file within `extern C {}`.

To build the shared library, you must compile it, along with anything you included, into the special shared object file.

For C:

<div style="text-align: center">

`gcc [optionalFlags] -shared myCFile1.c myCFile2.c ... myCFileN.c -o mySharedLibraryName.so`
</div>

For C++:

<div style="text-align: center">

`g++ [optionalFlags] -shared myCPPFile1.cpp myCPPFile2.cpp ... myCPPFileN.cpp -o mySharedLibraryName.so`

</div>

Note how all the C/C++ files we must include are all the files we `#include`d within the external library file.

Then, after this, we must statically link this shared library. Don't worry, this since this shared library file only has memory address mappings, its quite small compared to its counterpart. This needs to happen so the program know it exists. For C:

<div style="text-align: center">

`gcc -L<path to .so file> [optionalFlags] -o executableName objectFile1.o objectFile2.o ... objectFileN.o [otherLibraryFlags] -l<sharedLibraryName>`

</div>

For C++:

<div style="text-align: center">

`g++ -L<path to .so file> [optionalFlags] -o executableName objectFile1.o objectFile2.o ... objectFileN.o [otherLibraryFlags] -l<sharedLibraryName>`

</div>

To actually link the `.so` file, we need to specify where that flag (`-lsharedLibraryNameOnly`) points to. We need to use a special linux command to specify what the flag points to.

<div style="text-align: center">

`export LD_LIBRARY_PATH=<path to .so file>:$LD_LIBRARY_PATH`

</div>

After that, you can run your program. When it runs into a definition/instruction used in the shared library, it will go to that small, statically linked part of the program's memory that maps to the library's actual contents. It will follow the mapping and resolve and run the required code at runtime! This has some effects:

1. Memory for the Program - The program can now use a lot more memory for the code that you wrote.
2. Memory across Programs - If multiple programs need this library, they all can statically link the `.so` file, and that will allow them access to a singular shared library (hence the name)
3. Use - If the program does not use the shared library too much, the memory benefits will outweigh the cost for time needed to resolve the shared library. If not, well then, you should statically link your library.

This is a very confusing topic, so I encourage you to read more about it. It is good to know, but as far as I currently know, it is not used within LOST. To see a working example of this, visit [this site](https://iq.opengenus.org/create-shared-library-in-cpp/#:~:text=There%20are%20four%20steps%3A%201%20Compile%20C%2B%2B%20library,Step%201%3A%20Compile%20C%20code%20to%20object%20file).



## In Conclusion

This is a very long chapter, and though after the preprocessor, the information you see might not be important to you, they will certainly assist you in writing better code that is friendly to your compiler. In summary, here is a simplified diagram of how this entire process works:


<div style="text-align: center">

![](../images/g%2B%2B-compilation-process-2.png)

Figure 10 - C/C++ Compilation In Summary

</div>