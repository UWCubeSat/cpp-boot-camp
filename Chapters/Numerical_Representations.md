# Numerical Representation

## Introduction to Numbers
___
Numbers form a point of interest in every culture. Sayings like "third times the charm", "four is an unlucky number", or "thirteen is cursed" are things some of us may have heard before.

Therefore, the title of this may sound silly, but let's think for a moment and ask ourselves a question: Why do we represent numbers the way we do? To be more specific, let's look at a following number:

<div style="text-align: center", size="4">

5,973 

</div>

What do each of these digits mean though? Let's write out the full breakdown of the number:<br />

<div style="text-align: center"> 

$$5\times10^3+9\times10^2+7\times10^1+3\times10^0$$

</div>

So let's think about this system we have today. The number of digits we have is 10, ranging from 0 to 9, each "place" is a power of 10, and the places obviously increase by 1 each time. This system is called *decimal* for its use of 10.

This seems like an obvious mathematical fact, but why? Have you ever questioned this format? Specifically, why do we use 10 for all of these? 

The answer lies in the fact that humans have 10 fingers. From the Chinese to the Arabs to the Romans, every ancient civilization has always counted numbers this way because we have 10 figures, toes, or *digits*. Because of this, many areas of our life rely on this simple fact, from money, politics, and culture.

## Binary
___

However, what if we could break this system? In other words, what if we all had less or more than 10 digits? Or what if we met aliens that had a different number of digits? How do they count?

Let's assert that the new species *alans machinicus* has 2 fingers. We therefore can assume their system is in "base 2", or what is colloquially known as *binary*. Assuming they also use arabic numerals, their numbers will look like this

<div style="text-align: center", size="4">

10011010

</div>

Now let's break this down. Since they only have 2 fingers, they only have 2 options for digits, where we have chosen 0 and 1. Their "places" will be in powers of 2, and the powers will still increase sequentially, so the breakdown is

<div style="text-align: center"> 

$$1\times2^7+0\times2^6+0\times2^5+1\times2^4+1\times2^3+0\times2^2+1\times2^1+0\times2^0$$

</div>

If you want this number in our terms, just compute this expression we have here, and you'll find that it is the number

<div style="text-align: center", size="4">

154

</div>

To avoid confusion, it is common to notate these numbers with the subscript that is associated with this base

<div style="text-align: center", size="4">

Number<sub>base</sub>

</div>

In this case:

<div style="text-align: center", size="4">

10011010<sub>2</sub> = 154<sub>10</sub>

</div>

Ignore this if you don't want to nerd out, but the *alans machinicus* would actually expand the above number as:

<div style="text-align: center"> 

$$1_2\times10_2 ^{111_2}+0_2\times10_2^{110_2}+0_2\times10_2^{101_2}+1_2\times10_2^{100_2}+1_2\times10_2^{11_2}+0_2\times10_2^{10}+1_2\times10_2^1+0_2\times10_2^0$$

</div>


## Hexdecimal
___

In Latin, "Hex" means 6 and "decimal" is a reference to 10, so 6 + 10 is 16, so we'll be working with base 16 now. Let's say that the a new mutation arises in the population where people have 16 fingers (8 on each hand), and scientists name them a new species, *Ritchius Strostrupicus*. A millenium later, they form their own culture, customs, and number system. Based on our conversation from earlier, if they say the phrase


<div style="text-align: center", size="4">

"I have 40<sub>16</sub> cousins" (That's alot)

</div>

we would interpret it as

<div style="text-align: center", size="4">

"I have 64<sub>10</sub> cousins" (That's even more)

</div>

An astute person, however, would notice that the number of possible digits is 16 in hexdecimal, which exceeds the amount in any system. Therefore, we substitute letters for numbers so that the possible digits are 0123456789ABCDEF, 0 to F, or from 0 to 16. The "places" have bases of 16, and the powers increase sequentially. Therefore, the number

<div style="text-align: center", size="4">

F94A23C5<sub>16</sub>

</div>

can be represented as

<div style="text-align: center"> 

$$15\times16^7+9\times16^6+4\times16^5+10\times16^4+2\times16^3+3\times16^2+12\times16^1+5\times16^0$$

</div>

or

<div style="text-align: center"> 

F94A23C5<sub>16</sub> = 4,182,385,605<sub>10</sub>

</div>

## Numerical System Generalization
___

Let's say we have a number in base N. The possible digits range from 0 to N - 1, the "places" have bases of N, and the powers increase sequentially

One last thing though - You'll run into binary and hexdecimal (And decimal obviously) when working with code at one point or another, and so within coding, they earn a special notation for their numbers. For binary, it is

<div style="text-align: center"> 

0bNumber

</div>

in decimal

<div style="text-align: center"> 

0dNumber

</div>

and in hexdecimal

<div style="text-align: center"> 

0xNumber

</div>

As a final example, let's represent the number 9,096 in all the systems we've learned, in this format!

<div style="text-align: center"> 

0b10001110001000 = 0d9096 = 0x2388

</div>