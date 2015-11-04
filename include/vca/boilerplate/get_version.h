#ifndef VCA_BOILERPLATE_GET_VERSION_H_
#define VCA_BOILERPLATE_GET_VERSION_H_
/**
 * @file      vca/boilerplate/version.h
 * @copyright VCA Technology
 * @~english
 * @brief     Declaration of @c get_version
 */

#include <stdint.h>
#include <vca/boilerplate/macros.h>

VCA_BOILERPLATE_EXTERN_C_BEGIN

/**
 * @~english
 * Holds release version information
 */
struct vca_boilerplate_version {
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
  const char * const commit;

  /**
   * @~english
   * The release version string
   */
  const char * const string;
};

/**
 * @~english
 * Returns a reference to the version structure
 * @returns release version information
 */
VCA_BOILERPLATE_DLL_PUBLIC const struct vca_boilerplate_version * vca_boilerplate_get_version(void);

VCA_BOILERPLATE_EXTERN_C_END

#endif  /* VCA_BOILERPLATE_GET_VERSION_H_ */
