# Advent of Code 2021

![Code Christmas Tree](https://www.caphyon.ro/wp-content/uploads/2020/11/advent-code-1-1024x647.png)

---
#### My Solutions for the problems in Advent of Code 2021

### UPDATE - 2021.12.31

This is what I had time for up until the end of the year. I completed all tasks except for
+ Day 19, Task 1 and 2
+ Day 21, Task 2
+ Day 22, Task 2
+ Day 23, Task 2

These tasks proved much harder to me than I originally anticipated. Since I also have some university assignments to work on, that take priority, I'll have to leave these unsolved. Maybe I'll come back to them in February. It was a great milestone for me though, since this was the first year I attempted Advent of Code seriously, so I think I can be proud of coming this far! See you next year!

### UPDATE - 2021.12.17

I have basically restructured the entire project and divided it into multiple headers and their implementations. There are 3 new classes now, all of them can be found in the ``AoC2021/src`` folder. They each have a ``.cpp`` and ``.h`` file, which make up a library, that is linked to ``main.cpp`` using CMake. Here are the details of the classes:

+ Structures - Consists of the structures used to solve the problems.
+ Helpers - Consists of static methods which had to be seperated from the solver functions. This was either because the function is recursive, or I would have had to duplicate a lot of code.
+ Solvers - Consists of static methods for each day's each task. They (mostly) don't have any parameters and they return the result, which has to be submitted throught the Advent of Code website. They are named as follows: ``d<day_numer>t<task_number>``

The ``main.cpp`` only uses the functions defined in the Solvers class to print the results to the console.

##### Small exceptions:

+ Day 6's and Day 14's solutions for both task 1 and 2 were the same, only for a different number of iterations, therefore there is only one solver function for these, with different parameters.
+ On Day 13 the output was a pattern, which looks like some capital letters. Since I didn't want to write a pattern recognition program (wonder why), I am outputting this pattern to the ``AoC2021/outputs/day13.txt`` file. The main program prints the result I got from my inputs hardcoded onto the console. So if you're trying this out with a different input, the console output won't change, but the file does, so that's where your result will be.

---
For the problems check out the Advent of Code website!

https://adventofcode.com/2021




