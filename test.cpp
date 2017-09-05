#include "genetic-algorithm.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <bitset>

void mutate(int& candidate) {
  int pivot = rand() % 32;
  candidate = candidate ^ pivot;
}

int fitness(const int& candidate) {
  int R = 0;
  int C = candidate;
  while (C > 0) {
    R += C & 1;
    C /= 2;
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
  genetic_algorithm<int> test0(100, 1, 0.1, &rand, &cross, &fitness, &mutate);
  int best = test0.best_candidate();
  std::string binary = std::bitset<32>(best).to_string(); //to binary
  std::cout<<binary<< ": " << fitness(best) << std::endl;
  for (int i = 0; i < 10000; i++) {
    test0.do_generation();
    best = test0.best_candidate();
    std::string binary = std::bitset<32>(best).to_string(); //to binary
    std::cout<<binary<< ": " << fitness(best) << std::endl;
  }
}
