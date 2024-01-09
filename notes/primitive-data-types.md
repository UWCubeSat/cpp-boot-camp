# Primitive Data Types

Contributors: Tri Nguyen

## Introduction

Here, we talk about the characteristics of each primitive type, including memory size, storage characteristics and more.

----------------
Problem 1:

You are an electrical engineer working for Leibniz Microelectronics. You are tasked with making a system that will be used by computers to represent integers. For simplicity, you create a large scale model of 8 lightbulbs in a row (In other words, an array of lights). They are modifiable in any aspect (color, brightness, etc.), and you can represent the integer in whatever base you wish. What base would be the easiest to use?

Answer: Binary. If I choose 0 for off and 1 for on, it is easy for both you and a computer to read the number in binary. However, if we chose base 16, we would have to choose many colors/brightnesses to represent each digit, and its hard even for a human to read off that number.

----------------

As is illustrated, using binary is the easiest because its uses the mimimum possible light states (on or off) and is also the easiest to read. In other words, the use of binary allows for the discretization of values.

Binary has some special terminology for you to be aware of:

<br/>

Table 1 - Binary Sizes
Term|Defintion
:---:|---
Bit|One Binary Digit
Byte|Eight Binary Digits

<br/>

Generally, the sizes of primitives come in different quantities depending on your system. Below is the type sizes for 64-bit system, which will be used throughout this entire course:

<br/>

Table 2 - Common Type Sizes for 64-bit systems
Type|Size (Bytes)
:---:|---
Boolean (`bool`) | 1
Character (`char`) | 2
Integer (`int`) | 4
Float (`float`) | 4
Double (`double`) | 8

<br/>

## Endianess

In Western cultures, we take it for granted that we read things from left to right. However, before the meeting between the East and the West (1200 A.D.), many Asian countries read from right to left, and wrote that way too. So that begs the question, which way should computers read information (bytes). Thus, we introduce the following terms:

<br/>
<div style="text-align: center"> Table 3 - Endianess </div>

Term|Defintion
:---:|---
Most Significant Byte (MSB) | The byte that defines the beginning of the data
Least Significant Byte (LSB) | The byte that defines the end of the data
Little Endian | The data is organized from right to left, so the LSB is to the left and the MSB is to the right
Big Endian | The data is organized from left to right, so the MSB is to the left and the MSB is to the right

<br/>


## Integers

Integers are a bit more complicated than you would think. A positive integer would be represented how you think it would, using the normal conversion discussed in [Numerical Representation](numerical-representations.md). If an integer is defined in code such that it only supports positive numbers, it is called *unsigned*.

But what about negative integers, or *signed* integers? What happens is that the Most Significant Bit (MSBit) is used to indicate the sign of the digit (1 for negative, 0 for positive). However, it will be in the interest of the computer to be able to directly add binary numbers together, but unfortunately, manipulating the MSBit alone won't cut it.

----------------
Example 1:

Let's say we're using an 4 bit integer. Its really 3 bits since one is used for the sign. Let us say we want to subtract 4 and 3 in binary. There's two ways of doing this. We can simply subtract them

<div style="text-align: center">

$$0100_2-0011_2 = 0001_2 = 1_{10}$$


</div>

However, if we add 4 and -3, watch what happens:

<div style="text-align: center">

$$0100_2+1011_2 = 1111_2 = -7_{10}$$


</div>

You will notice it adds in the wrong direction.

----------------

Therefore, we need to change up the representation of the negative numbers in addition to the negative. *Two's Complement* is a system in which we can achieve mathematical equivalence in base 2. The simple rule is that to negate a number b<sub>2</sub>

1. Negate b<sub>2</sub>
2. Add 1

If you know the notation for this, it would be:

<div style="text-align: center">

$$!(b_2)<<1$$


</div>

This works regardless of whether b<sub>2</sub> is positive or negative.

In C++, you can represent Integers in many different ways. They can be *unsigned* (*signed* by default), and you can also make them different lengths (8, 16, 32, or 64). For a size N, the syntax is of the form:

<div style="text-align: center">

`intN_t` (*signed*)


`uintN_t` (*unsigned*)

</div>

For any size N, the range of numbers an integer can represent in decimal is:

<div style="text-align: center">

*Signed*: -2<sup>N/2</sup> to 2<sup>N/2 - 1</sup>

*Unsigned* 0 to 2<sup>N</sup> - 1

</div>

## Floats and Doubles

Floats are actually quite different. As a first, these are always signed. But secondly, representing them is very different. We need to form an equivalent to the integer case, so take the decimal number

<div style="text-align: center">

15.72
$$1\times10^1+5\times10^0+7\times10^{-1}+2\times10^{-2}$$


</div>

As you can see, just as the "places" can increment value, they also decrement, so you can imaging the same happens in binary.

----------------
Problem 2:

Represent the fraction 1/3 in binary using an 8 bit float. Note: The sign bit should be first.

Answer: You can't, but you can get close. We can choose the first (sign) and second (whole number) bits to be 0. The determination of the other bits is this:
- Bit 3 (Tenth Place): If we turn this on, then our number is at least 2<sup>-1</sup> or 1/2, so we need this to be zero
- Bit 4 (Hundreth Place): This should be on, since this will guarentee a number of at least 1/4
- Bit 5 (Thousanth Place): This should be off, since 1/4 + 1/8 is greater than 1/3
- Bit 6 (Ten Thousanth Place): This should be on since 1/4 + 1/16 is less than 1/3
- Bit 7 (Hundred Thousanth Place): This should be off since 1/4 + 1/16 + 1/32 is more than 1/3
- Bit 8 (Millionth Place): This should be on since 1/4 + 1/16 + 1/64 is less than 1/3

This results in the binary number 0.010101<sub>2</sub>, but this is 0.328125<sub>10</sub>, which is close to, but not 1/3.

----------------

This is the weakness of a float/double, since they will never be able to accuratly represent all possible non-integers. Any other representation will generate some degree of error, so it is in the best interest to minimize this error. Luckily, the Institute of Electrical and Electronics Engineers (IEEE) found a way to do so, which is this:

- The first bit shall always be dedicated to the **sign** S<sub>2</sub>
- The next few bits shall be dedicated to an **exponent** E<sub>2</sub>
- The remaining bits shall be dedicated to the **mantissa** or **significand** M<sub>2</sub>. It is to be interpreted as part of the fractional number (1.M)<sub>2
- An offset O<sub>2</sub> is sometimes employed, which is typically the maximum possible number of a signed integer with the same bit size as the exponent.

This is arranged such that the resulting float/double number is:

<div style="text-align: center">

$$(-1)^{S_2}\times2^{E_2 - O_2}\times(1.M)_2$$

</div>

This guarentees a very good accuracy of floats/doubles, but you'll sometimes see a very small error, which is why when you make a double variable with value 3.0 and print it, it might end up as 2.999999999


## Characters

These have a very simple representation, as they are the equivalent of an unsigned integer with less space. A mapping of char to integer values is shown with the following ASCII table:
![](../images/ascii-table.png)
<div style="text-align: center"> Figure 1 - ASCII Table</div>

## Booleans

Booleans are quite simple. It is 0 for false and 1 for true, but you'll notice that we use an entire byte for it as opposed to a single bit. This is because since everything else is a whole multiple of a byte, people decided to make it at least a byte too.
