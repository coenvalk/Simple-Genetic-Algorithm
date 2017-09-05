# Simple Genetic Algorithm

This is a simple genetic algorithm helper class made in C++. It is a templated
class that provides the framework for developing data through generations over
time. This program can provide information about the populations, best candidate,
and how many generations have passed.

## Usage:

This is a container class, so the user must first choose what type each candidate will be.
For the time being, we will assume that the container type is some type T.

The user must implement a few functions:
1. `void mutate(T& candidate)`: This randomly mutates the candidate in some small way
1. `std::vector<T> crossover(const T& p1, const T& p2)`: crosses over two candidates, and returns
  two "child" candidates that contain information from both the mother and the father.
1. `int fitness(const T& candidate)`: the function that actually tests the candidate's fitness.
  Should return an integer fitness value. Larger is better.
1. `T random()`: Should be a function that returns a random candidate of type T.

The user also needs to select the population, crossover rate, and the mutation rate.

Once these functions are implemented, you can use the member function
`void do_generation()` which will perform a single generation, and get the best candidate with the function
`const T& best_candidate()`.

To get an idea of how to use the class, take a look at test.cpp. This program uses the genetic algorithm to find an integer created of all
one's in binary.
