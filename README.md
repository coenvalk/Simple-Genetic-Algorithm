# Simple Genetic Algorithm

[![Build Status](https://travis-ci.org/coenvalk/Simple-Genetic-Algorithm.svg?branch=master)](https://travis-ci.org/coenvalk/Simple-Genetic-Algorithm)

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

While this class is very minimal, the class is robust enough to perform generations on itself! I implemented a genetic algorithm that takes
in genetic algorithms that take in integers (the same genetic algorithms as test0 in test.cpp) to find the optimal values for crossover rate
and mutation rate. Take a look at meta_test.cpp for a genetic algorithm that performs evolutions on genetic algorithms.

## Documentation

### Constructors

`genetic_algorithm();`
Creates a new genetic algorithm. None of the functions are required yet,
and the mutation rate and crossover rate are both assumed to be 0.5. NOTE:
THIS ALONE CANNOT PERFORM GENERATIONS! YOU MUST GIVE THE CLASS THE REQUIRED
FUNCTIONS TO START GENETIC ALGORITHM!

`genetic_algorithm(int population,
                  float C,
                  float M,
                  T (*random_candidate)(),
                  std::vector<T> (*crossover)(const T& p1, const T& p2),
                  int (*fitness)(const T& candidate),
                  void (*mutate)(T& candidate));`
Creates a new genetic algorithm. all of the functions and values are required, so after this constructor is used, you are ready to perform generations my friend!

### Accessors

`int get_generation_count();` returns the amount of generations this genetic algorithm has been running

`float get_crossover();` returns the crossover rate of the genetic algorithm

`float get_mutation();` returns the mutation rate of the genetic algorithm

`float avg_fitness();` returns the average fitness of the entire population

`const T& best_candidate();` returns the candidate in the population with the highest fitness

### Mutators

`void set_crossover(float new_C);` sets a new crossover rate

`void set_mutation(float new_M);` sets a new mutation rate

`void set_mutate_function(void (*mutate)(T& candidate));` sets a new mutation function

`void set_fitness_funtion(int (*fitness)(const T& candidate));` sets a new fitness function

`void set_crossover_function(std::vector<T> (*crossover)(const T& p1, const T& p2));` Sets a new crossover function

`void set_random_function(T (*random_candidate)());` Sets a new random candidate function

`void reset_generations();` Resets the entire population and sets amount of generations back to 0

`void set_pop(int P);` Sets a new population of size P. NOTE: USE OF THIS FUNCTION ALSO RESETS ALL GENERATIONS

`void do_generation();` Performs one full generation on the population. choses the best candidates of the current generation
pass on information to the next generation.