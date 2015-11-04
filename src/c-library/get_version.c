/**
 * @file      get_version.c
 * @copyright VCA Technology
 * @~english
 * @brief     Implementation of @c vca_boilerplate_get_version
 */

#include <vca/boilerplate/get_version.h>

const struct vca_boilerplate_version * vca_boilerplate_get_version(void) {
  static const struct vca_boilerplate_version s_version = {
    VCA_BOILERPLATE_VERSION_MAJOR,
    VCA_BOILERPLATE_VERSION_MINOR,
    VCA_BOILERPLATE_VERSION_REVISION,
    VCA_BOILERPLATE_VERSION_COMMIT,
    VCA_BOILERPLATE_VERSION_STRING
  };
  return &s_version;
}
