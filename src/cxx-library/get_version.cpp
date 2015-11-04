/**
 * @file      get_version.cpp
 * @copyright VCA Technology
 * @~english
 * @brief     Implementation of @c get_version
 */

#include <vca/boilerplate/get_version.hpp>

namespace vca {
namespace boilerplate {

const version& get_version() VCA_BOILERPLATE_NOEXCEPT {
  static const version s_version = {
    VCA_BOILERPLATE_VERSION_MAJOR,
    VCA_BOILERPLATE_VERSION_MINOR,
    VCA_BOILERPLATE_VERSION_REVISION,
    VCA_BOILERPLATE_VERSION_COMMIT,
    VCA_BOILERPLATE_VERSION_STRING
  };
  return s_version;
}

}  // namespace boilerplate
}  // namespace vca
