# TinyGP

Reimplementation of JAVA Genetic Algorithm Example Program into C++.

This example uses a genetic algorithm to find the answer to a simple mathematical problem, supporting the following grammar;

1. Addition

2. Multiplication

3. Division

4. Subtraction

This particular demonstration of a genetic algorithm is being used to find a set of mathematical operators to approximate a sin wave.

# Genetic Algorthms

A Genetic Algorithm is a simulation of evolutionary processes you would typically find in nature, this includes modelling processes such as breeding, random selection and mutation. the process is;

1. Create a population of "randomly generated genetic programs"

2. Run through the population, and assign a score to each program, determining how well it performs, with a given assigned problem

3. Randomly select X number of programs from the general population, and hold a tournament, until two programs are selected with the best score.

4. Cross breed those two programs with each other (usually a 50/50 process of randomly selecting features from both)

5. Retest the new child program, and assign a score.

6. Goto step 3, repeat until a program is created with the ideal best score (i.e. most fitted towards the given probllem)

# Requirements

This code was written on an Linux based machine, with GCC and CMake pre-installed.

# Building and Running

From the comand line, to build;

```
cmake .
make

```
To Run;

```
cd build
./tiny_gp
```

Ensure the "build" directory exists beforehand (this may need to be manually created after pulling the code from the repo)

# References

[TinyGP, Original Source, Riccaro Poli](https://cswww.essex.ac.uk/staff/rpoli/TinyGP/index.html)

[TinyGP, Original Java Code](https://cswww.essex.ac.uk/staff/rpoli/TinyGP/tiny_gp.java)


