#include "pifo.h"

#include <iostream>
#include <random>

int main() {
  // Random priority generation
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> prio_dis(1, 10000);

  // Set up one PIFO
  PIFO<int> pifo;

  // Execute simulation
  for (uint32_t i = 0; i < 10000; i++) {
    pifo.push(prio_dis(gen));
  }

  // Print out PIFO
  pifo.print_queue();
}
