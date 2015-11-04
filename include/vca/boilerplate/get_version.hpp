#ifndef VCA_BOILERPLATE_GET_VERSION_HPP_
#define VCA_BOILERPLATE_GET_VERSION_HPP_
/**
 * @file      vca/boilerplate/version.hpp
 * @copyright VCA Technology
 * @~english
 * @brief     Declaration of @c get_version
 */

#include <cstdint>
#include <string>
#include <vca/boilerplate/macros.hpp>

namespace vca {
namespace boilerplate {

/**
 * @~english
 * Holds release version information
 */
struct version {
  /**
   * @~english
   * The major version of the library, changes to this value indicate breaking API changes
   */
  uint32_t major;

  /**
   * @~english
   * The minor version of the library, changes to this value indicate new backwards compatible API changes
   */
  uint32_t minor;

  /**
   * @~english
   * The revision version of the library, changes to this value indicate bug fixes
   */
  uint32_t revision;

  /**
   * @~english
   * The commit of the version control system that the release was built from
   */
  std::string commit;

  /**
   * @~english
   * The release version string
   */
  std::string string;
};

/**
 * @~english
 * Returns a reference to the version structure
 * @returns release version information
 */
VCA_BOILERPLATE_DLL_PUBLIC const version& get_version() VCA_BOILERPLATE_NOEXCEPT;

}  // namespace boilerplate
}  // namespace vca

#endif  /* VCA_BOILERPLATE_GET_VERSION_HPP_ */
