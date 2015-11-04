#ifndef VCA_BOILERPLATE_MACROS_HPP_
#define VCA_BOILERPLATE_MACROS_HPP_
/**
 * @file      vca/boilerplate/macros.hpp
 * @copyright VCA Technology
 * @~english
 * @brief     Preprocessor helper macros.
 */

#include <vca/boilerplate/version.hpp>

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
 * Defines the version number for @c C++11 which can be used for feature detection
 */
#define VCA_BOILERPLATE_CXX11 201103L

/**
 * @~english
 * Determines the version of @c C++ that we are currently compiling against
 */
#define VCA_BOILERPLATE_CXX __cplusplus

/**
 * @def VCA_BOILERPLATE_FINAL
 * @~english
 * Specifies that a virtual function cannot be overridden. Can be used on a class to disallow inheritance.
 * @def VCA_BOILERPLATE_NOEXCEPT
 * @~english
 * Specifies that a function will never throw an exception.
 * @def VCA_BOILERPLATE_OVERRIDE
 * @~english
 * Specifies that a virtual function overrides an inhertied function.
 * @def VCA_BOILERPLATE_DELETE
 * @~english
 * Deletes a selected function from a class.
 */
#if VCA_BOILERPLATE_CXX >= VCA_BOILERPLATE_CXX11
#define VCA_BOILERPLATE_FINAL final
#define VCA_BOILERPLATE_NOEXCEPT noexcept
#define VCA_BOILERPLATE_OVERRIDE override
#define VCA_BOILERPLATE_DELETE = delete
#else
#define VCA_BOILERPLATE_FINAL
#define VCA_BOILERPLATE_NOEXCEPT throw()
#define VCA_BOILERPLATE_OVERRIDE
#define VCA_BOILERPLATE_DELETE
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

#endif /* VCA_BOILERPLATE_MACROS_HPP_ */
