# Determines what CMake APIs we can rely on
cmake_minimum_required (VERSION 2.8.11)
if (${CMAKE_VERSION} VERSION_GREATER 3.2.2)
  cmake_policy(VERSION 3.2.2)
endif()
if (${CMAKE_VERSION} VERSION_GREATER 3.1 OR
    ${CMAKE_VERSION} VERSION_EQUAL 3.1)
  cmake_policy(SET CMP0054 NEW)
endif()

# Do not allow in source builds
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Make sure we can import CMake extensions
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Load in the needed CMake modules
include(CheckIncludeFiles)
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
include(AddCCompilerFlag)
include(AddCXXCompilerFlag)
include(DetermineTargetArchitecture)
include(CMakeDependentOption)

# Set up the project
project(boilerplate)
string(TOUPPER ${CMAKE_PROJECT_NAME} PROJECT)
file(READ VERSION VERSION)
if (NOT VERSION)
  message(FATAL_ERROR "There was no VERSION file to be read")
endif()
set(${PROJECT}_VERSION "${VERSION}" CACHE STRING "The version of the civetweb library")
unset(VERSION)
string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" ${PROJECT}_VERSION_MATCH "${${PROJECT}_VERSION}")
if ("${${PROJECT}_VERSION_MATCH}" STREQUAL "")
  message(FATAL_ERROR "Must specify a semantic version: major.minor.patch")
endif()
set(${PROJECT}_VERSION_MAJOR "${CMAKE_MATCH_1}")
set(${PROJECT}_VERSION_MINOR "${CMAKE_MATCH_2}")
set(${PROJECT}_VERSION_PATCH "${CMAKE_MATCH_3}")
set(${PROJECT}_VERSION "${${PROJECT}_VERSION_MAJOR}.${${PROJECT}_VERSION_MINOR}.${${PROJECT}_VERSION_PATCH}")
message(STATUS "Project version - ${${PROJECT}_VERSION}")
determine_target_architecture(${PROJECT}_ARCHITECTURE)

# Detect the platform reliably
if(NOT MACOSX AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   SET(DARWIN YES)
elseif(NOT BSD AND ${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    SET(FREEBSD YES)
elseif(NOT LINUX AND ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(LINUX YES)
endif()

# Add options
option(${PROJECT}_ENABLE_THIRD_PARTY_OUTPUT "The building of third party libraries is output to the terminal" OFF)

# The C and C++ standards to use
set(${PROJECT}_C_STANDARD auto CACHE STRING
  "The C standard to use; auto determines the latest supported by the compiler")
set_property(CACHE ${PROJECT}_C_STANDARD PROPERTY STRINGS auto c11 c99 c89)
set(${PROJECT}_CXX_STANDARD auto CACHE STRING
  "The C++ standard to use; auto determines the latest supported by the compiler")
set_property(CACHE ${PROJECT}_CXX_STANDARD PROPERTY STRINGS auto c++14 c++11 c++98)

# Configure the linker
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
  find_program(GCC_AR gcc-ar)
  if (GCC_AR)
    set(CMAKE_AR ${GCC_AR})
  endif()
  find_program(GCC_RANLIB gcc-ranlib)
  if (GCC_RANLIB)
    set(CMAKE_RANLIB ${GCC_RANLIB})
  endif()
endif()

# Configure the C compiler
message(STATUS "Configuring C Compiler")
if ("${${PROJECT}_C_STANDARD}" STREQUAL "auto")
  add_c_compiler_flag(-std=c11)
  if (NOT HAVE_C_FLAG_STD_C11)
    add_c_compiler_flag(-std=c99)
    if (NOT HAVE_C_FLAG_STD_C99)
      add_c_compiler_flag(-std=c89)
    endif()
  endif()
else()
  add_c_compiler_flag(-std=${${PROJECT}_C_STANDARD})
endif()
add_c_compiler_flag(-Wall)
add_c_compiler_flag(-Wextra)
add_c_compiler_flag(-Wshadow)
add_c_compiler_flag(-Wsign-conversion)
add_c_compiler_flag(-Wmissing-prototypes)
add_c_compiler_flag(-Weverything)
add_c_compiler_flag(/W4)
add_c_compiler_flag(-Wno-padded)
add_c_compiler_flag(/Wd4820) # padding
add_c_compiler_flag(-Wno-unused-macros)
add_c_compiler_flag(-Wno-format-nonliteral)
if (MINGW)
  add_c_compiler_flag(-Wno-format)
endif()
add_c_compiler_flag(-Werror RELEASE)
add_c_compiler_flag(/WX RELEASE)
add_c_compiler_flag(-pedantic-errors)
add_c_compiler_flag(-fvisibility=hidden)
add_c_compiler_flag(-fstack-protector-strong RELEASE)
add_c_compiler_flag(-flto RELEASE)
add_c_compiler_flag(-fsanitize=undefined DEBUG)
add_c_compiler_flag(-fsanitize=address DEBUG)
if (HAVE_C_FLAG_FSANITIZE_ADDRESS)
  add_c_compiler_flag(-static-asan DEBUG)
endif()
add_c_compiler_flag(-fstack-protector-all DEBUG)
add_c_compiler_flag(-mwindows)

# Coverage build type
set(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the C compiler during coverage builds."
    FORCE)
set(CMAKE_EXE_LINKER_FLAGS_COVERAGE
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Flags used for linking binaries during coverage builds."
    FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the shared libraries linker during coverage builds."
    FORCE)
mark_as_advanced(
    CMAKE_CXX_FLAGS_COVERAGE
    CMAKE_C_FLAGS_COVERAGE
    CMAKE_EXE_LINKER_FLAGS_COVERAGE
    CMAKE_SHARED_LINKER_FLAGS_COVERAGE)
set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Coverage."
    FORCE)
add_c_compiler_flag(--coverage COVERAGE)

# Configure the C++ compiler
message(STATUS "Configuring C++ Compiler")
if ("${${PROJECT}_CXX_STANDARD}" STREQUAL "auto")
  add_cxx_compiler_flag(-std=c++14)
  if (NOT HAVE_CXX_FLAG_STD_CXX14)
    add_cxx_compiler_flag(-std=c++11)
    if (NOT HAVE_CXX_FLAG_STD_CXX11)
      add_cxx_compiler_flag(-std=c++0x)
      if (NOT HAVE_CXX_FLAG_STD_CXX0X)
        add_cxx_compiler_flag(-std=c++98)
      endif()
    endif()
  endif()
else()
  add_cxx_compiler_flag(-std=${${PROJECT}_CXX_STANDARD})
endif()
add_cxx_compiler_flag(-Wall)
add_cxx_compiler_flag(-Wextra)
add_cxx_compiler_flag(-Wshadow)
add_cxx_compiler_flag(-Wsign-conversion)
add_cxx_compiler_flag(-Wmissing-prototypes)
add_cxx_compiler_flag(-Weverything)
add_cxx_compiler_flag(/W4)
add_cxx_compiler_flag(-Wno-padded)
add_cxx_compiler_flag(/Wd4820) # padding
add_cxx_compiler_flag(-Wno-unused-macros)
add_cxx_compiler_flag(-Wno-format-nonliteral)
add_cxx_compiler_flag(-Wno-c++98-compat)
if (MINGW)
  add_cxx_compiler_flag(-Wno-format)
endif()
add_cxx_compiler_flag(-Werror RELEASE)
add_cxx_compiler_flag(/WX RELEASE)
add_cxx_compiler_flag(-pedantic-errors)
add_cxx_compiler_flag(-Wzero-as-null-pointer-constant)
add_cxx_compiler_flag(-fvisibility=hidden)
add_cxx_compiler_flag(-fstack-protector-strong RELEASE)
add_cxx_compiler_flag(-flto RELEASE)
add_cxx_compiler_flag(-fsanitize=undefined DEBUG)
add_cxx_compiler_flag(-fsanitize=address DEBUG)
if (HAVE_CXX_FLAG_FSANITIZE_ADDRESS)
  add_cxx_compiler_flag(-static-asan DEBUG)
endif()
add_cxx_compiler_flag(-fstack-protector-all DEBUG)
add_cxx_compiler_flag(-mwindows)
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the C++ compiler during coverage builds."
    FORCE)
add_cxx_compiler_flag(--coverage COVERAGE)

# Check the headers that are needed
check_include_files(stdint.h HAVE_STDINT)

# Set up the definitions
if (${CMAKE_BUILD_TYPE} MATCHES "[Dd]ebug")
  add_definitions(-DDEBUG)
endif()

# Build the targets
add_subdirectory(src)

# Enable the testing of the library/executable
include(CTest)
if (BUILD_TESTING)
  add_subdirectory(test)
endif()

# Set up CPack
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VENDOR "${CMAKE_PROJECT_NAME} Contributors")
set(CPACK_PACKAGE_CONTACT "bugs@${CMAKE_PROJECT_NAME}.com")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT}_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${${PROJECT}_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A HTTP library and server")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.md")
set(CPACK_STRIP_FILES TRUE)
set(CPACK_PACKAGE_DEPENDS "")

# RPM Packaging
set(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_ARCHITECTURE "${${PROJECT}_ARCHITECTURE}")
set(CPACK_RPM_PACKAGE_REQUIRES "${CPACK_PACKAGE_DEPENDS}")

# Debian Packaging
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "${${PROJECT}_ARCHITECTURE}")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/bel2125/civetweb")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "${CPACK_PACKAGE_DEPENDS}")

# WiX Packaging
# TODO: www.cmake.org/cmake/help/v3.0/module/CPackWIX.html

# Finalize CPack settings
include(CPack)
