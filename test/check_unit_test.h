#ifndef CHECK_UNIT_TEST_H_
#define CHECK_UNIT_TEST_H_
/**
 * @file      check_unit_test.h
 * @copyright VCA Technology
 * @~english
 * @brief     Suppresses warnings in @c check.h
 */

#include <stdint.h>

/* This unit test file uses the excellent Check unit testing library.
 * The API documentation is available here:
 * http://check.sourceforge.net/doc/check_html/index.html
 */
#ifdef __clang__
#pragma clang diagnostic push
// FIXME: check uses GCC specific variadic macros that are non-standard
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#endif
#ifdef _MSC_VER
#undef pid_t
#define pid_t int
/* Unreferenced formal parameter. START_TEST has _i */
#pragma warning(disable : 4100)
/* conditional expression is constant . asserts use while(0) */
#pragma warning(disable : 4127)
#endif
#include <check.h>
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif  /* CHECK_UNIT_TEST_H_ */
