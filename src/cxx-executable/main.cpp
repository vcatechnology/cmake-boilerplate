/**
 * @file      main.cpp
 * @copyright VCA Technology
 * @~english
 * @brief     Implementation of @c main
 */

#include <cstring>
#include <iostream>
#include <vca/boilerplate/get_version.hpp>

/**
 * @~english
 * The entry point for the executable
 * @returns a status code
 */
int main(const int argc, const char * const * const argv) {
  for (int i = 0; i < argc; ++i) {
    if (0 == std::strcmp("--version", argv[i])) {
      std::cout << vca::boilerplate::get_version().string << std::endl;
      return 0;
    }
  }

  std::cout << "Hello, world!" << std::endl;
  return 0;
}
