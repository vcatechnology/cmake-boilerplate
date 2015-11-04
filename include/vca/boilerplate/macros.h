#ifndef VCA_BOILERPLATE_MACROS_H_
#define VCA_BOILERPLATE_MACROS_H_
/**
 * @file      vca/boilerplate/macros.hpp
 * @copyright VCA Technology
 * @~english
 * @brief     Preprocessor helper macros.
 */

#include <vca/boilerplate/version.h>

/**
 * @~english
 * Determines if we are compiling on a valid unix machine
 */
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#define VCA_BOILERPLATE_OS_UNIX
#endif

/**
 * @~english
 * Determines if we are compiling on a valid NT machine (Windows)
 */
#if defined(_WIN32)
#define VCA_BOILERPLATE_OS_NT
#endif

/**
 * @~english
 * Defines the version number for @c C11 which can be used for feature detection
 */
#define VCA_BOILERPLATE_C11 201112L

/**
 * @~english
 * Defines the version number for @c C99 which can be used for feature detection
 */
#define VCA_BOILERPLATE_C99 199901L

/**
 * @def VCA_BOILERPLATE_C
 * @~english
 * Determines the version of @c C that we are currently compiling against
 */
#ifdef __STDC_VERSION__
#define VCA_BOILERPLATE_C __STDC_VERSION__
#else
#define VCA_BOILERPLATE_C 0
#endif

/**
 * @def VCA_BOILERPLATE_HAVE_GENERIC_MACROS
 * @~english
 * Determines if the compiler has the @c _Generic C11 feature
 */
#if VCA_BOILERPLATE_C >= VCA_BOILERPLATE_C11
#if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9)))
#define VCA_BOILERPLATE_HAVE_GENERIC_MACROS
#elif !defined(__GNUC__)
#define VCA_BOILERPLATE_HAVE_GENERIC_MACROS
#endif
#endif

/**
 * @def VCA_BOILERPLATE_HAVE_VARIADIC_MACROS
 * @~english
 * Determines if the compiler has support for the variadic macros feature
 */
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ > 1)) || \
    (defined(__GNUC__) && (__STDC__ == 1) && (!defined(__STRICT_ANSI__))) || (__cplusplus)
#define VCA_BOILERPLATE_HAVE_VARIADIC_MACROS
#endif

/**
 * @def VCA_BOILERPLATE_EXTERN_C_BEGIN
 * @~english
 * Begins a C region when included in a C++ file.
 *
 * @def VCA_BOILERPLATE_EXTERN_C_END
 * @~english
 * Ends a C region in C++ files.
 */
#ifdef __cplusplus
#define VCA_BOILERPLATE_EXTERN_C_BEGIN extern "C" {
#define VCA_BOILERPLATE_EXTERN_C_END }
#else
#define VCA_BOILERPLATE_EXTERN_C_BEGIN
#define VCA_BOILERPLATE_EXTERN_C_END
#endif

/**
 * @def VCA_BOILERPLATE_DLL_PUBLIC
 * @~english
 * Enables public export of function in shared library
 *
 * @def VCA_BOILERPLATE_DLL_LOCAL
 * @~english
 * Disables public export of function in shared library
 */
#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_DLL
#ifdef __GNUC__
#define VCA_BOILERPLATE_DLL_PUBLIC __attribute__((dllexport))
#else
#define VCA_BOILERPLATE_DLL_PUBLIC __declspec(dllexport)
#endif
#else
#ifdef __GNUC__
#define VCA_BOILERPLATE_DLL_PUBLIC __attribute__((dllimport))
#else
#define VCA_BOILERPLATE_DLL_PUBLIC __declspec(dllimport)
#endif
#endif
#define VCA_BOILERPLATE_DLL_LOCAL
#elif __GNUC__ >= 4
#define VCA_BOILERPLATE_DLL_PUBLIC __attribute__((visibility("default")))
#define VCA_BOILERPLATE_DLL_LOCAL __attribute__((visibility("hidden")))
#else
#define VCA_BOILERPLATE_DLL_PUBLIC
#define VCA_BOILERPLATE_DLL_LOCAL
#endif

#endif /* VCA_BOILERPLATE_MACROS_H_ */
