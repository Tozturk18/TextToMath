# TextToMath
This program allows for user to enter a set of mathematical expressions as a string and get the solution. This program is initially created to support the KiCAD_Coil repository but it grew to become a handy and fast offline calculator that became really useful!

This program can support basic mathematical expressions such as addition, substraction, multiplication, division, modulus, and exponents.
This program does also support mathematical constants and expressions such as pi, Euler's number, square root, rounding, flooring, and ceiling, trigonometry, logarithm, factorial, etc...

In the example folder there are 2 example codes that you can run to play around with this library. Example 1 will ask you to enter a mathematical equation or an expression and it will solve it for you. Try something hard! If it does not work please contact me so I can fix the bug. Reach out to me at [tunaozturk2001@hotmail.com](mailto:tunaozturk2001@hotmail.com)

More updates will be coming as needed to fix bugs or add new mathematical functionalities such as complex numbers, calculus, etc...

The library only allows the use of the ```float textCalc(char *str)``` function and the ```char* textCalcStr(char *str)``` function. All the other functions defined in the header file (textMath.h) are static and only used by the program itself. To use this program calling the ```textCalc()``` function or the ```textCalcStr()``` is enough. 

Both functions takes in a string (a char array) and returns a value containing the solution of the mathematical expressions written in the string. ```textCalc()``` returns the value as a float value and ```textCalcStr()``` returns the value as a string.

```textCalcStr()``` has an upside of being able to handle large numbers because outputing the result as a string allows for it to output using scientific notation for very large and very small outputs.

This repository contains an "examples" folder where you can find an 2 different example files. The "example1" folder contains "example1.c" file which is a program that uses the TextToMath library to find the solution to the user input and repeat. Meanwhile the "example2.c" file showcases the use of TextToMath library via an inline argument while running the executable.

To try out the TextToMath Program you can run the example1 and example2 executables. You can find some examples to try on them at the bottom of this [README file](#examples)

## Usage
The mathematical expressions are very similar to the ones used by Google Search, [Desmos Scientific Calculator](https://www.desmos.com/scientific), and [Geogebra](https://www.geogebra.org/?lang=en). 

(Inline inputs to the terminal, or command center requires for the mathematical expression to not be seperated with spaces or it will detect each term seperated by a space as seperate inputs. The inline inputs also do not allow the usage of paranthesis "```()```" and only allows curly "```{}```" or square brackets "```[]```". Moreover, inline inputs does not allow '```*```' for multiplication, instead '```_```' can be used.)

1. parenthesis:
    - To create a term with parenthesis you can simply use the parenthesis "```(3+2)```", or square brackets "```[3+2]```", or curly brackets "```{3+2}```" sign. In this example the solution would be ```5.00```

2. Exponents:
    - To create an exponent you can use the caret '```^```' sign. For example entering ```"3^2"``` would result in ```9.00```

3. Square Root:
    - To create a square root you can either use the exponent sign and do ```"9^(1/2)"``` or you can simply use the mathematical function ```"sqrt(9)"``` which both will result in ```3.00```

4. Rounding:
    - To round the float value to the nearest integer you can use the ```"round(1.223)"``` mathematical function and in this example the result should be ```1.00```

5. Flooring:
    - To floor the float value to the nearest lower integer you can use the ```"floor(1.82)"``` mathematical function and in this example the result should be ```1.00```

6. Ceiling:
    - To ceil the float value to the nearest higher integer you can use the ```"ceil(0.234)"``` mathematical function and in this example the result should be ```1.00```

7. Sine:
    - To find the sine of an angle you can use the ```sin(pi/6)``` mathematical trig function and in this example the result should be ```0.5``` <b>(Beware: This function uses radians as input)</b>

8. Cosine:
    - To find the cosine of an angle you can use the ```cos(30deg)``` mathematical trig function and in this example the result should be ```0.87``` <b>(Beware: This function uses radians as input)</b>

8. Tangent:
    - To find the tangent of an angle you can use the ```tan( (20+25)deg )``` mathematical trig function and in this example the result should be ```1.00``` <b>(Beware: This function uses radians as input)</b>

9. Cotangent:
    - To find the cotangent of an angle you can use the ```cot( (15*2)deg )``` mathematical trig function and in this example the result should be ```1.73``` <b>(Beware: This function uses radians as input)</b>

10. Arcsine:
    - To find the inverse sine of an angle you can use the ```asin(0.9)``` mathematical trig function and in this example the result should be ```1.12``` <b>(Beware: This function uses radians as input)</b>

11. Arccosine:
    - To find the inverse cosine of an angle you can use the ```acos(0.9)``` mathematical trig function and in this example the result should be ```0.45``` <b>(Beware: This function uses radians as input)</b>

12. Arctangent:
    - To find the inverse tangent of an angle you can use the ```atan(0.9)``` mathematical trig function and in this example the result should be ```0.73``` <b>(Beware: This function uses radians as input)</b>

13. Arccotangent:
    - To find the inverse cotangent of an angle you can use the ```acot(0.9)``` mathematical trig function and in this example the result should be ```1.36``` <b>(Beware: This function uses radians as input)</b>

14. Absolute value:
    - To find the absolute value of a value you can use the ```abs(-12)``` mathematical function and in this example the result should be ```12```

15. Natural Log:
    - To find the natural log of a value you can use the ```ln(e)``` mathematical function and in this example the result should be ```1.00```

16. Log base 10:
    - To find the log base 10 of a value you can use the ```log(100)``` mathematical function and in this example the result shoul be ```2.00```

17. Log base X:
    - To find the log base X of a value where X is another user defined value you can use the ```log2(16)``` mathematical function and in this example the result should be ```4.00```

18. Factorial
    - To find the factorial of a value you can use the ```(2+3)!``` mathematical expression and in this example the result should be ```6.00```

19. Radians to Degrees:
    - To convert a radian value to degrees, you can use the ```(pi/2)deg``` mathematical expression and in this example the result should be ```90.0```

20. Degrees to Radians:
    - To convert a degree value to radians, you can use the ```180rad``` mathematical expression and in this example the result should be ```3.14```

21. Multiplication:
    - To multiply two float values you can use either the star sign '```*```' or the underscore '```_```' sign. For example entering ```"3.25*2.68"``` would result in ```8.71```

22. Division:
    - To divide two float values you can use the slash '```/```' sign. For example entering ```"3/2"``` would result in ```1.5```

23. Modulus:
    - To find the modulus of two float values you can use the mod '```%```' sign. For example entering ```"3%2"``` would result in ```1.00```

24. Addition:
    - To add two float values you can use the plus '```+```' sign. For example entering ```"3+2"``` would result in ```5.0```

25. Substraction:
    - To substract two float values you can use the minus '```-```' sign. For example entering ```"3-2"``` would result in ```1.00```

26. PI (π):
    - To input PI (π) into your mathematical expression you can simply type ```"pi"``` or ```"PI``` or ```"Pi"``` or ```"pI"```. For example entering ```"pi^2"``` would result in ```9.87```

27. Euler's Number (e):
    -   To input the Euler's Number (e) into your mathematical expression you can simply type ```e```. For example entering ```sqrt(2.45*e)``` would result in ```2.58```

Below are some examples on how to use these terms together to create more complex mathematical expressions

## Examples
This program can support different terms for multiplication and pharanthesis to accomodate command-line (terminal) inputs. This is because terms such as "*" or "()" or "$", and more are specific predefined command line arguments. Hence, it gives an error when trying to do multiplication, and else.

This is why the multiplication opperation is supported with the underscore character '_' and the paranthesis are supported by curly brackets "{}" and square brackets "[]".

### Example 1

```
./example1

Welcome! Thank you for trying out Text-To-Math program.
Please enter a mathematical expression below!
Currently the character limit is 225 character...

2.45*e^round(1.36*(10.4+sqrt(8)*pi)/3)
Solution: 19852.55
```
---
### Example 2

```
./example2 180deg

Solution: 3.14
```
---

## Acknowledgements 
This library is created by Ozgur Tuna Ozturk on July 14, 2023.<br>
Last edited by Ozgur Tuna Ozturk on August 11, 2023.<br>
Contributed by ChatGPT on July 14, 2023