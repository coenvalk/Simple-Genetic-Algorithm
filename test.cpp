/*
  MIT License

  Copyright (c) 2017 Coen Valk
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "genetic-algorithm.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <bitset>

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

int main() {
  genetic_algorithm<int> test0(10, .7, 0.2, &rand, &cross0, &fitness0, &mutate0);
  int best = test0.best_candidate();
  std::string binary = std::bitset<32>(best).to_string(); //to binary
  std::cout<<binary<< ": " << fitness0(best) << std::endl;
  while (fitness0(best) < 32) {
    test0.do_generation();
    best = test0.best_candidate();
    std::string binary = std::bitset<32>(best).to_string(); //to binary
    std::cout<<binary<< ": " << fitness0(best) << std::endl;
  }
  std::cout << "generations: " << test0.get_generation_count() << std::endl;
  return 0;
}
