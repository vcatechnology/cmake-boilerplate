/**
 * @file      utility.c
 * @copyright VCA Technology
 * @~english
 * @brief     Implementation of @c make_utility_suite
 */

#include <vca/boilerplate/get_version.h>

/* This unit test file uses the excellent Check unit testing library.
 * The API documentation is available here:
 * http://check.sourceforge.net/doc/check_html/index.html
 */
#include "unit_test.h"

START_TEST(test_version_major) {
  const struct vca_boilerplate_version * const version = vca_boilerplate_get_version();
  ck_assert_ptr_ne(NULL, version);
  ck_assert_uint_eq(version->major, VCA_BOILERPLATE_VERSION_MAJOR);
}
END_TEST

START_TEST(test_version_minor) {
  const struct vca_boilerplate_version * const version = vca_boilerplate_get_version();
  ck_assert_ptr_ne(NULL, version);
  ck_assert_uint_eq(version->minor, VCA_BOILERPLATE_VERSION_MINOR);
}
END_TEST

START_TEST(test_version_revision) {
  const struct vca_boilerplate_version * const version = vca_boilerplate_get_version();
  ck_assert_ptr_ne(NULL, version);
  ck_assert_uint_eq(version->revision, VCA_BOILERPLATE_VERSION_REVISION);
}
END_TEST

START_TEST(test_version_commit) {
  const struct vca_boilerplate_version * const version = vca_boilerplate_get_version();
  ck_assert_ptr_ne(NULL, version);
  ck_assert_str_eq(version->commit, VCA_BOILERPLATE_VERSION_COMMIT);
}
END_TEST

START_TEST(test_version_string) {
  const struct vca_boilerplate_version * const version = vca_boilerplate_get_version();
  ck_assert_ptr_ne(NULL, version);
  ck_assert_str_eq(version->string, VCA_BOILERPLATE_VERSION_STRING);
}
END_TEST

Suite *make_utility_suite(void) {
  Suite *const suite = suite_create("Utility");

  TCase *const version = tcase_create("Version");

  tcase_add_test(version, test_version_major);
  tcase_add_test(version, test_version_minor);
  tcase_add_test(version, test_version_revision);
  tcase_add_test(version, test_version_commit);
  tcase_add_test(version, test_version_string);
  suite_add_tcase(suite, version);

  return suite;
}
