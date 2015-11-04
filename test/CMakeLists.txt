# Determine if we should print to the output
if (${PROJECT}_ENABLE_THIRD_PARTY_OUTPUT)
  set(THIRD_PARTY_LOGGING 0)
else()
  set(THIRD_PARTY_LOGGING 1)
endif()

# We use the check unit testing framework for our C unit tests
find_package(LibCheck)

# Build the C unit tests
file(GLOB_RECURSE C_UNIT_TEST_SRC "*.c")
list(REMOVE_ITEM C_UNIT_TEST_SRC "main.c")
add_library(c-unit-tests STATIC ${C_UNIT_TEST_SRC})
if (BUILD_SHARED_LIBS)
  target_compile_definitions(c-unit-tests PRIVATE ${PROJECT}_DLL_IMPORTS)
endif()
target_include_directories(
  c-unit-tests PUBLIC
  ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(c-unit-tests c-library Check::LibCheck)
if (LIBCOMPAT_FOUND)
  target_link_libraries(c-unit-tests Check::LibCompat)
endif()
if (LIBM_FOUND)
  target_link_libraries(c-unit-tests System::LibM)
endif()
if (LIBRT_FOUND)
  target_link_libraries(c-unit-tests System::LibRt)
endif()

add_executable(${CMAKE_PROJECT_NAME}-c-unit-test main.c)
target_link_libraries(${CMAKE_PROJECT_NAME}-c-unit-test c-unit-tests)

# Add a check command that builds the dependent test program
add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS ${CMAKE_PROJECT_NAME}-c-unit-test)

# A macro for adding tests
macro(boilerplate_add_test type suite test_case)
  set(test "test-${suite}-${test_case}")
  string(TOLOWER "${test}" test)
  string(REGEX REPLACE "[^-A-Za-z0-9]" "-" test "${test}")
  add_test(
    NAME ${test}
    COMMAND ${CMAKE_PROJECT_NAME}-${type}-unit-test "--suite=${suite}" "--test-case=${test_case}")
  if (WIN32)
    string(REPLACE ";" "\\;" test_path "$ENV{PATH}")
    set_tests_properties(${test} PROPERTIES
      ENVIRONMENT "PATH=${test_path}\\;$<TARGET_FILE_DIR:${type}-library>")
  endif()
endmacro(boilerplate_add_test)

# C Unit Tests
boilerplate_add_test(c Utility Version)

# Add the coverage command(s)
if (${CMAKE_BUILD_TYPE} MATCHES "[Cc]overage")
  find_program(GCOV_EXECUTABLE gcov)
  find_program(LCOV_EXECUTABLE lcov)
  find_program(GENHTML_EXECUTABLE genhtml)
  find_program(CTEST_EXECUTABLE ctest)
  if (GCOV_EXECUTABLE AND LCOV_EXECUTABLE AND GENHTML_EXECUTABLE AND CTEST_EXECUTABLE AND HAVE_C_FLAG_COVERAGE)
    add_custom_command(
      OUTPUT ${CMAKE_BINARY_DIR}/lcov/index.html
      COMMAND ${LCOV_EXECUTABLE} -q -z -d .
      COMMAND ${LCOV_EXECUTABLE} -q --no-external -c -b "${CMAKE_SOURCE_DIR}" -d . -o before.lcov -i
      COMMAND ${CTEST_EXECUTABLE} --force-new-ctest-process
      COMMAND ${LCOV_EXECUTABLE} -q --no-external -c -b "${CMAKE_SOURCE_DIR}" -d . -o after.lcov
      COMMAND ${LCOV_EXECUTABLE} -q -a before.lcov -a after.lcov --output-file final.lcov
      COMMAND ${LCOV_EXECUTABLE} -q -r final.lcov "'${CMAKE_SOURCE_DIR}/test/*'" -o final.lcov
      COMMAND ${GENHTML_EXECUTABLE} final.lcov -o lcov --demangle-cpp --sort -p "${CMAKE_SOURCE_DIR}" -t benchmark
      DEPENDS ${CMAKE_PROJECT_NAME}-c-unit-test
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Running LCOV"
    )
    add_custom_target(coverage
      DEPENDS ${CMAKE_BINARY_DIR}/lcov/index.html
      COMMENT "LCOV report at lcov/index.html"
    )
    message(STATUS "Coverage command added")
  else()
    if (HAVE_C_FLAG_COVERAGE)
      set(C_FLAG_COVERAGE_MESSAGE supported)
    else()
      set(C_FLAG_COVERAGE_MESSAGE unavailable)
    endif()
    message(WARNING
      "Coverage command not available:\n"
      "  gcov: ${GCOV_EXECUTABLE}\n"
      "  lcov: ${LCOV_EXECUTABLE}\n"
      "  genhtml: ${GENHTML_EXECUTABLE}\n"
      "  ctest: ${CTEST_EXECUTABLE}\n"
      "  --coverage flag: ${C_FLAG_COVERAGE_MESSAGE}")
  endif()
endif()
