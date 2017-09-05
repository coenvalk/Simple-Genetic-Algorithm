#include "genetic-algorithm.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <bitset>

void mutate(int& candidate) {
  int pivot = rand() % 32;
  candidate = candidate ^ (1 << pivot);
}

int fitness(const int& candidate) {
  int R = 0;
  for (int i = 0; i < 32; i++) {
    // isolate:
    R += (candidate >> i) & 1;
  }
  return R;
}

std::vector<int> cross(const int& p1, const int& p2) {
  std::vector<int> children(2);
  int pivot = rand() % 32;
  int bottom = (1 << pivot) - 1;
  int top = ~bottom;
  children[0] = (p1 & top) | (p2 & bottom);
  children[1] = (p1 & bottom) | (p2 & top);
  return children;
}

int main() {
  genetic_algorithm<int> test0(10, .7, 0.2, &rand, &cross, &fitness, &mutate);
  int best = test0.best_candidate();
  std::string binary = std::bitset<32>(best).to_string(); //to binary
  std::cout<<binary<< ": " << fitness(best) << std::endl;
  while (fitness(best) < 32) {
    test0.do_generation();
    best = test0.best_candidate();
    std::string binary = std::bitset<32>(best).to_string(); //to binary
    std::cout<<binary<< ": " << fitness(best) << std::endl;
  }
  std::cout << "generations: " << test0.get_generation_count() << std::endl;
}
