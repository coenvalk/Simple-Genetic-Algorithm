#ifndef __genetic_algorithm_h__
#define __genetic_algorithm_h__

#include <vector>
#include <iostream>
#include <cstdlib>
#include <limits.h>

template <class T>
class genetic_algorithm {
 public:
  /*
    constructor:
    needs population, a function to make a
    random candidate, crossover function,
    fitness function, and mutate function.
   */
 genetic_algorithm(int population,
		   float C,
		   float M,
		   T (*random_candidate)(),
		   std::vector<T> (*crossover)(const T& p1, const T& p2),
		   int (*fitness)(const T& candidate),
		   void (*mutate)(T& candidate)) :
  crossover_(crossover), fitness_(fitness), mutate_(mutate), generation_(0), M_(M), C_(C) {
    population_ = std::vector<T>(population);
    fitnesses_ = std::vector<int>(population);
    for (int i = 0; i < population; i++) {
      population_[i] = (*random_candidate)();
    }
    sort_pop();
  }

  int get_generation_count() { return generation_; }

  // finds the best candidate
  const T& best_candidate() {
    return population_[0];
  }
  
  /*
    performs one generation. calculates fitness
    of all candidates, takes the top population,
    crosses some of them over, mutates some, and
    makes that the new population
  */
  void do_generation() {
    /*
      TODO: make more efficient
     */
    int x = 2;
    int n = 1;
    while (n < population_.size()) {
      x++;
      n = x * (x - 1) / 2;
    }
    x = 0;
    std::vector<T> new_population(population_.size());
    for (int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) {
	T one = population_[i];
	T two = population_[j];
	if ((float) rand() < C_ * (float) INT_MAX) {
	  // crossover!
	  std::vector<T> children = (*crossover_)(one, two);
	  one = children[0];
	  two = children[1];
	}
	if ((float) rand() < M_ * (float) INT_MAX) {
	  // mutate one!
	  (*mutate_)(one);
	}
	if ((float) rand() < M_ * (float) INT_MAX) {
	  // mutate two!
	  (*mutate_)(two);
	}
	if (x < new_population.size()) {
	  new_population[x] = one;
	  x++;
	}
	if (x < new_population.size()) {
	  new_population[x] = two;
	  x++;
	}
      }
    }
    population_ = new_population;
    sort_pop();
    generation_++;
  }

  
  
 private:
  int generation_;
  std::vector<T> population_;
  std::vector<int> fitnesses_;
  float C_;
  float M_;

  /*
    necessary functions for genetic algorithms
    must be implemented by the user and passed
    in with the constructor.
  */
  std::vector<T> (*crossover_)(const T& p1, const T& p2);
  int (*fitness_)(const T& candidate);
  void (*mutate_)(T& candidate);
  
  void compute_fitnesses() {
    for (int i = 0; i < population_.size(); i++) {
      fitnesses_[i] = (*fitness_)(population_[i]);
      // std::cout << "fitness " << i << ": " << fitnesses_[i] << std::endl;
    }
  }

  // swaps two elements in both population and fitnesses
  void swap(int index1, int index2) {
    T tmp = population_[index1];
    population_[index1] = population_[index2];
    population_[index2] = tmp;

    int TMP = fitnesses_[index1];
    fitnesses_[index1] = fitnesses_[index2];
    fitnesses_[index2] = TMP;
  }

  int partition(int lo, int hi) {
    int pivot = fitnesses_[hi];
    int i = lo - 1;
    for (int j = lo; j < hi; j++) {
      if (fitnesses_[j] > pivot) {
	i++;
	swap(i, j);
      }
    }
    if (fitnesses_[hi] > fitnesses_[i + 1]) {
      swap(i + 1, hi);
    }
    return i + 1;
  }

  void quicksort(int lo, int hi) {
    if (lo < hi) {
      int p = partition(lo, hi);
      quicksort(lo, p - 1);
      quicksort(p + 1, hi);
    }
  }
  
  /*
    private population sorting function:
    selection sort based on fitness function
    largest fitness first
  */
  void sort_pop() {
    compute_fitnesses();
    quicksort(0, population_.size() - 1);
  }  
};

#endif
