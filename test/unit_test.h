#ifndef UNIT_TEST_H_
#define UNIT_TEST_H_
/**
 * @file      unit_test.h
 * @copyright VCA Technology
 * @~english
 * @brief     Check unit tests
 */

#include <vca/boilerplate/macros.h>
#include "check_unit_test.h"

/**
 * @~english
 * Utility unit tests. Tests parts of the library such as retrieving the library version
 * @returns a check unit test suite
 */
VCA_BOILERPLATE_DLL_PUBLIC Suite *make_utility_suite(void);

#endif  /* UNIT_TEST_H_ */
