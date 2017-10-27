#include "genetic-algorithm.h"
#include <iostream>
#include <vector>
#include <bitset>
#include <cstdlib>
#include <climits>

void mutate0(int& candidate) {
  int pivot = rand() % 32;
  candidate = candidate ^ (1 << pivot);
}

int fitness0(const int& candidate) {
  int R = 0;
  for (int i = 0; i < 32; i++) {
    // isolate:
    R += (candidate >> i) & 1;
  }
  return R;
}

std::vector<int> cross0(const int& p1, const int& p2) {
  std::vector<int> children(2);
  int pivot = rand() % 32;
  int bottom = (1 << pivot) - 1;
  int top = ~bottom;
  children[0] = (p1 & top) | (p2 & bottom);
  children[1] = (p1 & bottom) | (p2 & top);
  return children;
}

void mutate_meta(genetic_algorithm<int>& candidate) {
  int value = rand() % 2;
  if (value == 0) {
    candidate.set_crossover((float) rand() / INT_MAX);
  } else if (value == 1) {
    candidate.set_mutation((float) rand() / INT_MAX);
  }
}

int fitness_meta(const genetic_algorithm<int>& candidate) {
  genetic_algorithm<int> tmp = candidate;
  int avg_gens = 0;
  for (int i = 0; i < 100; i++) {
    tmp.reset_generations();
    int best = tmp.best_candidate();
    std::string binary = std::bitset<32>(best).to_string(); //to binary
    // std::cout<<binary<< ": " << fitness0(best) << std::endl;
    while (fitness0(best) < 32 && tmp.get_generation_count() < 1000) {
      tmp.do_generation();
      best = tmp.best_candidate();
      std::string binary = std::bitset<32>(best).to_string(); //to binary
      // std::cout<<binary<< ": " << fitness0(best) << std::endl;
    }
    // std::cout << "generations: " << tmp.get_generation_count() << std::endl;
    avg_gens += tmp.get_generation_count();
  }
  avg_gens = (int) ((float) avg_gens / 100);
  std::cout << "average generations: " << avg_gens << std::endl;
  return -avg_gens;
}

std::vector<genetic_algorithm<int> > cross_meta(const genetic_algorithm<int>& p1, const genetic_algorithm<int>& p2) {
  std::vector<genetic_algorithm<int> > children;
  children.push_back(genetic_algorithm<int>(10, p1.get_crossover(), p2.get_mutation(), &rand, &cross0, &fitness0, &mutate0));
  children.push_back(genetic_algorithm<int>(10, p2.get_crossover(), p1.get_mutation(), &rand, &cross0, &fitness0, &mutate0));
  return children;
}

genetic_algorithm<int> random_meta() {
  float C = (float) rand() / INT_MAX;
  float M = (float) rand() / INT_MAX;
  return genetic_algorithm<int>(10, C, M, &rand, &cross0, &fitness0, &mutate0);
}

int main () {
  genetic_algorithm<genetic_algorithm<int> > meta(10, 0.7, 0.2, &random_meta, &cross_meta, &fitness_meta, &mutate_meta);
  for (int gen = 0; gen < 10; gen++) {
    std::cout << "====== GENERATION " << gen + 1 << " ====== AVERAGE FITNESS: " << meta.avg_fitness() << std::endl; 
    meta.do_generation();
  }
  std::cout << "best crossover rate: " << meta.best_candidate().get_crossover() << std::endl;
  std::cout << "best mutation rate: " << meta.best_candidate().get_mutation() << std::endl;
  std::cout << "best generations: " << std::endl;
  fitness_meta(meta.best_candidate());
  return 0;
}
