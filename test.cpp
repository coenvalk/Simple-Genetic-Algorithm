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
#include <string>
#include <cassert>

void mutate0(int& candidate) {
  int pivot = rand() % 32;
  candidate = candidate ^ (1 << pivot);
}

void mutate1(std::string& candidate) {
  int pivot = rand() % candidate.length();
  candidate[pivot] = (char) ((rand() % 96) + 32);
}

int fitness0(const int& candidate) {
  int R = 0;
  for (int i = 0; i < 32; i++) {
    // isolate:
    R += (candidate >> i) & 1;
  }
  return R;
}

int fitness1(const std::string& candidate) {
  std::string test_string = "The quick brown fox jumps over the lazy dog.";
  int R = 0;
  for (int i = 0; i < candidate.size(); i++) {
    R += 96 - std::abs(candidate[i] - test_string[i]);
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

std::vector<std::string> cross1(const std::string& p1, const std::string& p2) {
  std::vector<std::string> children(2);
  int pivot = rand() % p1.length();
  children[0] = p1.substr(0, pivot) + p2.substr(pivot);
  children[1] = p2.substr(0, pivot) + p1.substr(pivot);
  return children;
}

std::string random_string() {
  int len = 44;
  std::string new_string;
  for (int i = 0; i < len; i++) {
    new_string += (char) ((rand() % 96) + 32);
  }
  return new_string;
}

int main() {
  srand(1);
  // integer test:
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

  // string test:
  genetic_algorithm<std::string> test1(5000, 0.7, 0.2, &random_string, &cross1, &fitness1, &mutate1);
  while (test1.best_candidate() != "The quick brown fox jumps over the lazy dog.") {
    test1.do_generation();
    std::cout << test1.best_candidate() << std::endl;
  }
  std::cout << "generations: " << test1.get_generation_count() << std::endl;

  return 0;
}
