/**
 * @file      main.c
 * @copyright VCA Technology
 * @~english
 * @brief     Implementation of @c main
 */

#include <stdio.h>
#include <string.h>
#include <vca/boilerplate/get_version.h>

/**
 * @~english
 * The entry point for the executable
 * @returns a status code
 */
int main(const int argc, const char * const * const argv) {
  for (int i = 0; i < argc; ++i) {
    if (0 == strcmp("--version", argv[i])) {
      printf("%s\n", vca_boilerplate_get_version()->string);
      return 0;
    }
  }

  printf("Hello, world!\n");
  return 0;
}
