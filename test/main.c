/**
 * @file      main.c
 * @copyright VCA Technology
 * @~english
 * @brief     Implementation of @c main
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "check_unit_test.h"
#include "unit_test.h"

int main(const int argc, const char * const * const argv) {
  // Determine what tests to run
  const char * suite = NULL;
  const char * const suite_arg = "--suite=";
  const size_t suite_arg_size = strlen(suite_arg);
  const char * test_case = NULL;
  const char * const test_case_arg = "--test-case=";
  const size_t test_case_arg_size = strlen(test_case_arg);
  for (int i = 1; i < argc; ++i) {
    if (0 == strncmp(suite_arg, argv[i], suite_arg_size) && (strlen(argv[i]) > suite_arg_size)) {
      suite = &argv[i][suite_arg_size];
    } else if (0 == strncmp(test_case_arg, argv[i], test_case_arg_size) && (strlen(argv[i]) > test_case_arg_size)) {
      test_case = &argv[i][test_case_arg_size];
    } else if (0 == strcmp("--help", argv[i])) {
      printf("Usage: %s [options]\n"
        "  --suite=Suite            Determines the suite to run\n"
        "  --test-case='Test Case'  Determines the test case to run\n",
        argv[0]);
      exit(EXIT_SUCCESS);
    } else {
      fprintf(stderr, "Invalid argument: %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }
  }

  // Run up the tests
  SRunner * const srunner = srunner_create(make_utility_suite());
//  srunner_add_suite(srunner, make_xyz_suite());
  srunner_run(srunner, suite, test_case, CK_NORMAL);
  const int number_run = srunner_ntests_run(srunner);
  const int number_failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return (number_failed == 0) && (number_run != 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
