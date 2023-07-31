# TextToMath
This program allows for user to enter a set of mathematical expressions as a string and get the solution. This program is initially created to support the KiCAD_Coil repository but it grew to become a handy and fast offline calculator that became really useful!

This program can support basic mathematical expressions such as addition, substraction, multiplication, division, modulus, and exponents.
This program does also support mathematical constants and expressions such as pi, Euler's number, square root, rounding, flooring, and ceiling.

In the example folder there is an example code that you can run to play with it. It will ask you to enter a mathematical equation or an expression and it will solve it for you. Try something hard! If it does not work please contact me so I can fix the bug.

More updates will be coming as needed to fix bugs or add new mathematical functionalities such as complex numbers, calculus, etc...

The library only allows the use of the ```float textCalc(char *str)``` function. All the other functions defined in the header file (textMath.h) are static and only used by the program itself. To use this program calling the ```textCalc()``` function is enough. 

This function takes in a string (a char array) and returns a float number that contains the solution of the mathematical expressions written in the string.

This repository contains an "example" folder where you can find an example.c code file, a Makefile and an executable "example" file. To try out the TextToMath Program you can run the example executable and it will ask you to input a mathematical expression. Then enter your mathematical expression to get the solution.

## Usage
The mathematical expressions are very similar to the ones used by Google Search and Desmos or Geogebra.

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
    - To find the sine of an angle you can use the ```sin(pi/6)``` mathematical trig function and in this example the result should be ```0.5```

8. Cosine:
    - To find the cosine of an angle you can use the ```cos(30deg)``` mathematical trig function and in this example the result should be ```0.87```

8. Tangent:
    - To find the tangent of an angle you can use the ```tan( (20+25)deg )``` mathematical trig function and in this example the result should be ```1.00```

9. Cotangent:
    - To find the cotangent of an angle you can use the ```cot( (15*2)deg )``` mathematical trig function and in this example the result should be ```1.73```

10. Arcsine:
    - To find the inverse sine of an angle you can use the ```asin(0.9)``` mathematical trig function and in this example the result should be ```1.12```

11. Arccosine:
    - To find the inverse cosine of an angle you can use the ```acos(0.9)``` mathematical trig function and in this example the result should be ```0.45```

12. Arctangent:
    - To find the inverse tangent of an angle you can use the ```atan(0.9)``` mathematical trig function and in this example the result should be ```0.73```

13. Arccotangent:
    - To find the inverse sine of an angle you can use the ```acot(0.9)``` mathematical trig function and in this example the result should be ```1.36```

14. Multiplication:
    - To multiply two float values you can use either the star sign '```*```' or the underscore '```_```' sign. For example entering ```"3.25*2.68"``` would result in ```8.71```

15. Division:
    - To divide two float values you can use the slash '```/```' sign. For example entering ```"3/2"``` would result in ```1.5```

16. Modulus:
    - To find the modulus of two float values you can use the mod '```%```' sign. For example entering ```"3%2"``` would result in ```1.00```

17. Addition:
    - To add two float values you can use the plus '```+```' sign. For example entering ```"3+2"``` would result in ```5.0```

18. Substraction:
    - To substract two float values you can use the minus '```-```' sign. For example entering ```"3-2"``` would result in ```1.00```

19. PI (π):
    - To input PI (π) into your mathematical expression you can simply type ```"pi"``` or ```"PI``` or ```"Pi"``` or ```"pI"```. For example entering ```"pi^2"``` would result in ```9.87```

20. Euler's Number (e):
    -   To input the Euler's Number (e) into your mathematical expression you can simply type ```e```. For example entering ```sqrt(2.45*e)``` would result in ```2.58```

Below are some examples on how to use these terms together to create more complex mathematical expressions

## Examples
This program can support different terms for multiplication and pharanthesis to accomodate command-line (terminal) inputs. This is because terms such as "*" or "()" or "$", and more are specific predefined command line arguments. Hence, it gives an error when trying to do multiplication, and else.

This is why the multiplication opperation is supported with the underscore character '_' and the paranthesis are supported by curly brackets "{}" and square brackets "[]".

### Example 1

```
2.45*e^round(1.36*(10.4+sqrt(8)*pi)/3)
```