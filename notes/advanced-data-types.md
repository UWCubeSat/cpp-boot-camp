# Advanced Data Types

## Introduction

Here we will discuss types that are unique to C++. This includes `stucts`, `enums` and `unions`. We will also discuss `namespace`, which is not a type but rather an entity that holds variables and functions.

## Structures (`structs`)

A `struct` is an entities capable of holding fields, and you can think of it as a way to hold many variables of different types. 


Below, we create a struct with the name `myBorland`, with fields `myField1` and `myField2`

```
/*
struct {
    type1 fieldName1;
    type2 fieldName2;
    ...
    typeN fieldNameN;
} structVarName;
*/

struct {
    int myField1;
    double myField2;
} myBorland;
```
<div style="text-align: center"> Figure 1a - Simple Struct Declaration </div>
Note how structures are statements, as the ending semicolon denotes. Notice how this structure does not have values yet (Well they do, they're random values, as you'll learn in the Memory and Management Section). So, to initialize values for this `struct`, we will be using dot notation.

```
// structVarName.fieldName = value;

myBorland.myField1 = 0;
myBorland.myField2 = 1.0;
```
<div style="text-align: center"> Figure 1b - Simple Struct Field Initialization </div>

If you wanted to do this all in one step, then you must specify all values of the enum, seperated with commas, within brackets as shown in the following example:
```
struct {
    int myField1;
    double myField2;
} myBorland = {0, 1.0};
```
<div style="text-align: center"> Figure 1c - Struct Declaration and Initialization </div>


Let's say you wanted to make more structs with the same layout. What you can do is that you can change Figure 1 to name multiple structs, seperated by commas:

```
/*
struct {
    type1 fieldName1;
    type2 fieldName2;
    ...
    typeN fieldNameN;
} structVarName1, structVarName2, ..., structVarNameM;
*/
struct {
    int myField1;
    double myField2;
} myBorland1, myBorland2, myBorland3;
```
<div style="text-align: center"> Figure 1d - Multiple Struct Declaration </div>

and the initialization of the fields work exactly the same as in Figure 2!

However, there is a problem with this format. This form of struct formation is really only good for making a single struct. Why? Because if I need this multiple times, chances are I will need this kind of struct again in a different spot in my location, and its not a good idea to reserve memory for a struct that will not get used for a while. So, its good practice to actually declare a type of struct. In the following figure, we've declared the `struct Borland` with the same fields as a new type:

```
/*
struct structName {
    type1 fieldName1;
    type2 fieldName2;
    ...
    typeN fieldnameN;
};
/*
struct Borland {
    int myField1;
    double myField2;
};
```
<div style="text-align: center"> Figure 2a - Struct Type Declaration </div>

Note how there is still a (`;`) after the (`}`). Therefore, to make a `Borland`, you can use a declaration and initialization similar to Figures 1 and 2:

```
// structName structVarName;
// structName structVarName = {value1, value2, ..., valueN};

struct Borland myBorland1;
myBorland1.myField1 = 0;
myBorland1.myField2 = 1.0;
struct Borland myBorland2 = {3, 4.0};
```
<div style="text-align: center"> Figure 2b - Struct Variable Declaration and Initialization </div>

Now, if Figure 5 is placed at the top of your code, you can make a `Borland` anytime you want, and do not have to waste memory!

A cool thing, starting in C++11, you can also place functions into `struct`s as well, as the following figure shows:
```
struct {
    int myField1;
    double myField2;
    char myFunction() {
        return 'c';
    }    
};
```
<div style="text-align: center"> Figure 3 - Struct Declaration and Initialization </div>

## Enumerations (`enum`)

An `enum` is an entity that maps literal constants to integers. 

```
/*
enum enumName {
    constant1,
    constant2,
    ...
    constantN
};
*/
enum weekdays {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};
```
<div style="text-align: center"> Figure 4a - Enum Declaration </div>

Note how each element does not need a type identifier, they are simply literals, and that they are seperated by (`,`), not (`;`). You will also note there are no explicit values assigned to each constant. That is because if that is not done, the first constant is 0, the second is one more than that, and so on. In this example, this would be the same as saying:

```
/*
enum enumName {
    constant1 = value1,
    constant2 = value2,
    ...
    constantN = valueN
};
*/

enum weekdays {
    Sunday = 0,
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6
};
```
<div style="text-align: center"> Figure 4b - Enum Declaration </div>

Now, if you want specific values for each constant, you can use this `= integer` notation, as shown below:
```
enum painMeter {
    noPain = 0,
    somePain = 3,
    pain = 5,
    extremePain = 7,
    CSE351 = 10
};
```
<div style="text-align: center"> Figure 4c - Enum Declaration </div>

You can also do a mix of both

```
enum HuskySatTwo {
    LOST,
    ReactionWheels = 4,
    Magnetorquers
    FOUND,
    Propulsion = 10
};
```
<div style="text-align: center"> Figure 4d - Enum Declaration </div>

- `LOST` has no intitialized value, so its value is 0
- `ReactionWheels` has an initialized value, so its value is 4
- `Magnetorquers` has no initialized value, so it is one more than the last, or 5
- `FOUND` also has no initialized value, so it is 6
- `Propulsion` does, so it is 10

After an enum is declared, you can then make variables out of it using the following notation, which is similar to the declaration of a struct

```
// enumName enumVarName = constant;

weekday day = Wednesday;
painMeter pain;
pain = extremePain;
```
<div style="text-align: center"> Figure 4e - Enum Initialization </div>

## Enumeration Classes (`enum class`)

However, once declared, enums will not allow for any redefinition of any of its constants while you are in the enum's scope. An enum's scope ranges from its declaration to the `}` brackets that contain it (Or the end of the file), and this applies to its fields as well. The below demonstrates a few errors about this:

```
enum People = {Good, Bad}; // Begin People Scope

int main() {
    enum Others = {Good, Meh}; // Begin Others Scope
    // Error: Good has already been defined by People
    
    int Meh = 0;
    // Error: Bad is already a constant
} // End Others Scope

enum Professors = {Okay, Meh} // Begin Professors Scope
// Okay: the enum Others is out of scope of Professors

// End People Scope
// End Professors Scope
```
<div style="text-align: center"> Figure 5a - Enum Errors </div>

Another bad thing is attempting to compare different enums when you don't want it. This is because C++ is not type-safe, so it automatically convert the `enum` constants to integers in a process known as *implicit conversion*. The following program functions, but doesn't conceptually make any sense:

```
weekday day = Friday;
painMeter painRating = pain;
if(painRating == painRating) {
    std::cout << "Days are pain!!!" << std::endl;
}

// Output: Days are pain!!!
```
<div style="text-align: center"> Figure 5b - Demonstration of Lack of Type-Safety for Enums </div>

You see, one should not be able to compare these two enums since they are unrelated, but since friday and pain are both 5, they are "equal". To avoid this, C++11 introduces the `enum class`, which is a strongly typed and strongly scoped type.
T
```
/*
enum class enumName {
    constant1,
    constant2,
    ...
    constantN
};
*/

enum class betterWeekday {
    betterSunday,
    betterMonday,
    betterTuesday,
    betterWednesday,
    betterThursday,
    betterFriday,
    betterSaturday
};
```
<div style="text-align: center"> Figure 6a - Enum Class Declaration </div>

To reference a constant within an `enum class`, you must use the scope resolution operator (`::`):

<div style="text-align: center"> 

`enumClassName::Field` 

</div>

This tells us that constants belonging to `enum class`es are specific to those classes, meaning that we can now define variables or other `enum class` constants with the same name. To demonstrate, let's draw an analogy to Figure 5a with the following valid example:

```
enum class People = {Good, Bad};

int main() {
    enum class Others = {Good, Meh}; // Okay now, since People::Good is not Others::Good
    
    int Meh = 0; // This is okay now, since main::Meh is not Others::Meh
}

enum Professors = {Okay, Meh} // Still okay
```
<div style="text-align: center"> Figure 7a - Demonstration of the Strongly Scoped Enum Class </div>

However, this means the initialization of the `enum class` is different

```
// enumClassName enumClassVarName = enumClassName::Constant;

betterWeekday betterDay = betterWeekday::betterWednesday;

```
<div style="text-align: center"> Figure 6b - Enum Class Initialization </div>

With the use of the keyword `class`, C++ establishes `enum class`es as distinct entities, which does not allow for automatic type conversion.

```
// Pretend weekday and painMeter are now enum classes
weekday day = weekday::Friday;
painMeter painRating = painMeter::pain;
if(painRating == painRating) {
    std::cout << "Days are pain!!!" << std::endl;
}

// Output: Error, no suitible conversion from weekday to PainMeter elements
```
<div style="text-align: center"> Figure 7b - Demonstration of the Strongly Typed Enum Class </div>


There is one more advantage you can control, and that is the underlying type of the constants in an `enum class`. We've accepted that it was an integer, but what if the constants could be less or more bytes? To specify the specific type you want your `enum class` constants to represent, simply use the following notation:
```
/*
enum class enumClassName : type {
    constant1,
    constant2,
    ...
    constantN
};
*/

enum class betterWeekday : char {
    betterSunday,
    betterMonday,
    betterTuesday,
    betterWednesday,
    betterThursday,
    betterFriday,
    betterSaturday
}; 

```
<div style="text-align: center"> Figure 8 - Enum Class Type Specification </div>

## Unions (`union`)

A union is a collection of different variables, like a struct, but it only holds one at a time. To do this, a union will always take up the amount of space specified by the largest variable type. To demonstrate, look at the following union:

```
/*
union unionName {
    type1 field1;
    type2 field2;
    ...
    typeN fieldN;
} unionVarName1, unionVarName2, ..., unionVarNameM;
*/

union Herb {
    char language;
    int contributions;
    double salary;
} Sutter;
```
<div style="text-align: center"> Figure 9a - Simple Union Declaration </div>

When this is declared, `Sutter` only holds 8 bytes, as that is the maximum size of any of the fields (`double`). As a reminder, it only represents one of these fields at a time. So, here is an example of some initializations that occur

```
// unionVarName.field = value;

Sutter.language = 'c';
Sutter.contributions = 1000000; // Probably more
Sutter.salary = 5047289.45;
```
<div style="text-align: center"> Figure 9b - Simple Union Initialization </div>

- First Line: `Sutter` holds the char value `'c'`, which only occupies 1/8 bytes of `Sutter`
- Second Line: `Sutter` discards `'c'` and now holds `1000000`, which now occupies 4/8 bytes of `Sutter`
- Third Line: `Sutter` discards `1000000` and now holds `5047289.45`, which occupies all 8 bytes of `Sutter`

As with `struct`s, `union`s can be pure type definitions by seperating the type declaration and field declaration
```
/*
// Type Declaration
union unionName {
    type1 fieldName1;
    type2 fieldName2;
    ...
    typeN fieldNameN;
};

// Variable Declaration
unionName unionVarName

// Variable Initialization
unionVarName.fieldName = value; // Must be the type corresponding to field
*/

union Herb {
    char language;
    int contributions;
    double salary;
};

// Variable Declaration
union Herb Sutter;

// Variable Initialization
Sutter.language = 'c';
Sutter.contributions = 1000000;
Sutter.salary = 5047289.45;
```
<div style="text-align: center"> Figure 9c - Seperation of Union Type and Union Variable Declaration </div>

**NOTE:** For variable declarations in C, you must always put the type of entity before your user-defined type:
- Structures: `struct structName structVarName`
- Enumerations: `enum enumName enumVarName`
- Unions: `union unionName unionVarName`

## Type Definitions (`typedef`)
___
Let's say that you find an unsavorably lengthy type name, such as the type `unsigned long long int` which represents and unsigned integer with 8 bytes. Obviously if you want to make many variables with this, its going to be a lot to type, so C++ has specified a way to use this type in place of another word. It works like the following

```
// typedef originalTypeName newTypeName

typedef unsigned long long int big;
big eightBits = 0;
```
<div style="text-align: center"> Figure 10 - Definition of Alias Types </div>

Therefore `big` is now a keyword that is really a `unsigned long long int`, and can be used as such. The variable `eightBits` is an `unsigned long long int` that has eight 0's in the memory representing `eightBits`.


## Bit fields
In structures, we can actually control how many bits (not bytes) each field can reserve for itself. The syntax uses the `:` operator:
```
/*
struct structName {
    type1 fieldName1 : numBits1;
    type2 fieldName2 : numBits2;
    ...
    typeN fieldnameN : numBitsN;
};
/*
struct Borland {
    int myField1 : 6;
    double myField2 : 10;
};
```
<div style="text-align: center"> Figure 11 - Structs with Bit Fields </div>

Now, when we make `struct` variables, their `myField1` will be integers with 6 bits, and their `myField2` will be doubles with 10 bits.

## Namespaces (`namespace`)

This is not a data structure, but it is worth mentioning since it somewhat acts as one. For learning purposes, you may think of namespaces as static, non-inheritable classes. Namespaces are entities that can contain types, variables and functions. They are simply a container to contain these things, and they are not `instanceof`-able. Namespaces are declared quite simply.

```
/*
namespace namespaceName {
    // Type, Variable and Function Definitions/Implementations
}
*/

namespace helloWorld {
    typedef std::string words;
    words myFirstProgram = "Hello World!"
    void printHelloWorld() {
        std::cout << myFirstProgram;
    }
}
```
<div style="text-align: center"> Figure 12a - Namespace Declaration </div>

To reference any type, variable, or function contained within a namespace, you can use the scope resolution operator (`::`), assuming you have included the file containing the namespace

```
helloWorld::words earth = "Hello Earth!";
helloWorld::printHelloWorld();
std::cout << hellowWorld::myFirstProgram << std::endl << earth;

// Output: Hello World!Hellow World!
//         Hellow Earth!
```
<div style="text-align: center"> Figure 12b - Namespace Use </div>

However, say that using the scope resolution operator gets tiring. We can say we are using a certain namespace, and the program automatically recognizes all elements inside of the namespace without the need of the operator.

```
// using namespace namespaceName;


using namespace helloWorld;

words earth = "Hello Earth!";
printHelloWorld();
std::cout << myFirstProgram << std::endl << earth;

// Output: Hello World!Hellow World!
//         Hellow Earth!
```
<div style="text-align: center"> Figure 12c - Namespace Use without Scope Resolution Operator </div>

However, there are some problems that can occur:

```
using namespace helloWorld;

words earth = "Hello Earth!";
words myFirstProgram = "My First Program" // Error, defined in helloWorld
printHelloWorld();
std::cout << myFirstProgram << std::endl << earth;
```
<div style="text-align: center"> Figure 12c - Scope Broadening from use of namespace </div>

The problem here is obvious, with that variable declaration, I can no longer distiguish between the `helloWorld`'s variable and the local one. However, if we get rid of the first line, our program is okay again.

```
helloWorld::words earth = "Hello Earth!";

std::string myFirstProgram = "My First Program"; 
// This is fine now, this variable has a different scope than 

helloWorld::printHelloWorld();
std::cout << std::endl << hellowWorld::myFirstProgram << std::endl << earth << std::endl << myFirstProgram;

// Output: Hello World!
//         Hellow World!
//         Hellow Earth!
//         My First Program 

```
<div style="text-align: center"> Figure 12d - Allowing multiple definitions of variable due to difference in scope</div>

Therefore, it is good pratice to never use the statement `using namespace namespaceName` for that very reason.