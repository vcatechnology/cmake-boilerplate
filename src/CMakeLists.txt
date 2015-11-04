# The C API library
file(GLOB_RECURSE C_LIBRARY_SRC "c-library/*.c")
add_library(c-library ${C_LIBRARY_SRC})
set_target_properties(c-library PROPERTIES
  OUTPUT_NAME "${CMAKE_PROJECT_NAME}_c"
  VERSION ${${PROJECT}_VERSION}
  SOVERSION ${${PROJECT}_VERSION}
)
if (BUILD_SHARED_LIBS)
  target_compile_definitions(c-library PRIVATE BUILDING_DLL)
endif()
target_include_directories(
  c-library PUBLIC
  ${PROJECT_SOURCE_DIR}/include)
install(
  TARGETS c-library
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  COMPONENT c-library)
file(GLOB_RECURSE C_LIBRARY_INCLUDES "${PROJECT_SOURCE_DIR}/include/*.h")
install(FILES
  ${C_LIBRARY_INCLUDES}
  DESTINATION include
  COMPONENT c-library)

# The C++ API library
file(GLOB_RECURSE CXX_LIBRARY_SRC "cxx-library/*.cpp")
add_library(cxx-library ${CXX_LIBRARY_SRC})
set_target_properties(cxx-library PROPERTIES
  OUTPUT_NAME "${CMAKE_PROJECT_NAME}_cxx"
  VERSION ${${PROJECT}_VERSION}
  SOVERSION ${${PROJECT}_VERSION}
)
if (BUILD_SHARED_LIBS)
  target_compile_definitions(cxx-library PRIVATE BUILDING_DLL)
endif()
target_include_directories(
  cxx-library PUBLIC
  ${PROJECT_SOURCE_DIR}/include)
install(
  TARGETS cxx-library
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  COMPONENT cxx-library)
file(GLOB_RECURSE CXX_LIBRARY_INCLUDES "${PROJECT_SOURCE_DIR}/include/*.hpp")
install(FILES
  ${CXX_LIBRARY_INCLUDES}
  DESTINATION include
  COMPONENT cxx-library)

# A C executable
file(GLOB_RECURSE CXX_EXECUTABLE_SRC "c-executable/*.c")
add_executable(c-executable ${CXX_EXECUTABLE_SRC})
set_target_properties(c-executable PROPERTIES
  OUTPUT_NAME "${CMAKE_PROJECT_NAME}_c"
)
install(
  TARGETS c-executable
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  COMPONENT c-executable)
target_include_directories(
  c-executable PUBLIC
  ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(c-executable c-library)

# A C++ executable
file(GLOB_RECURSE CXX_EXECUTABLE_SRC "cxx-executable/*.cpp")
add_executable(cxx-executable ${CXX_EXECUTABLE_SRC})
set_target_properties(cxx-executable PROPERTIES
  OUTPUT_NAME "${CMAKE_PROJECT_NAME}_cxx"
)
install(
  TARGETS cxx-executable
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  COMPONENT cxx-executable)
target_include_directories(
  cxx-executable PUBLIC
  ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(cxx-executable cxx-library)

# Link system libraries if they are found
find_package(Threads)
target_link_libraries(c-library ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(cxx-library ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(c-executable ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(cxx-executable ${CMAKE_THREAD_LIBS_INIT})
find_package(LibRt)
if (LIBRT_FOUND)
  target_link_libraries(c-library System::LibRt)
  target_link_libraries(cxx-library System::LibRt)
  target_link_libraries(c-executable System::LibRt)
  target_link_libraries(cxx-executable System::LibRt)
endif()
find_package(LibDl)
if (LIBDL_FOUND)
  target_link_libraries(c-library System::LibDl)
  target_link_libraries(cxx-library System::LibDl)
  target_link_libraries(c-executable System::LibDl)
  target_link_libraries(cxx-executable System::LibDl)
endif()
