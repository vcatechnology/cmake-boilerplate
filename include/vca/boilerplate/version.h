#ifndef VCA_BOILERPLATE_VERSION_H_
#define VCA_BOILERPLATE_VERSION_H_
/**
 * @file      vca/boilerplate/version.h
 * @copyright VCA Technology
 * @~english
 * @brief     C preprocessor macros describing the project version
 */

/**
 * @~english
 * The major version of the project
 * @see VCA_BOILERPLATE_REQUIRED
 */
#define VCA_BOILERPLATE_VERSION_MAJOR 0

/**
 * @~english
 * The minor version of the project
 * @see VCA_BOILERPLATE_VERSION_REQUIRED
 */
#define VCA_BOILERPLATE_VERSION_MINOR 0

/**
 * @~english
 * The revision version of the project
 * @see VCA_BOILERPLATE_VERSION_REQUIRED
 */
#define VCA_BOILERPLATE_VERSION_REVISION 0

/**
 * @~english
 * The release commit of the project
 */
#define VCA_BOILERPLATE_VERSION_COMMIT "0000000000000000000000000000000000000000"

/**
 * @~english
 * The version of the library as a constant char string
 */
#define VCA_BOILERPLATE_VERSION_STRING \
  "VCA_BOILERPLATE_VERSION_MAJOR.VCA_BOILERPLATE_VERSION_MINOR.VCA_BOILERPLATE_VERSION_REVISION"

/**
 * @~english
 * Checks if the version of the library is a certain version.
 * @code{.c}
 * #if VCA_BOILERPLATE_VERSION_AT_LEAST(1, 3, 0)
 *   // Some code specific for the >= libvca_test.so.1.3.0
 * #else
 *   // Some code specific for the < libvca_test.so.1.2.x
 * #endif
 * @endcode
 */
#define VCA_BOILERPLATE_VERSION_AT_LEAST(major, minor, revision) \
  ((VCA_BOILERPLATE_VERSION_MAJOR >= major) && \
  (VCA_BOILERPLATE_VERSION_MINOR >= minor) && \
  (VCA_BOILERPLATE_VERSION_REVISION >= revision))

#endif  /* VCA_BOILERPLATE_VERSION_H_ */
