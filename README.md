C/C++ CMake Boilerplate
=======================

[![Travis Build Status](https://travis-ci.org/vcatechnology/cmake-boilerplate.svg?branch=master)](https://travis-ci.org/vcatechnology/cmake-boilerplate)
[![Appveyor Build Status](https://ci.appveyor.com/api/projects/status/github/vcatechnology/cmake-boilerplate?svg=true)](https://ci.appveyor.com/project/vcatechnology/cmake-boilerplate/branch/master)
[![Coverage Status](https://coveralls.io/repos/vcatechnology/cmake-boilerplate/badge.svg?branch=master&service=github)](https://coveralls.io/github/vcatechnology/cmake-boilerplate?branch=master)

This project allows for a good start for any C/C++ project that would like to
be built with CMake. It includes:

  - Auto detection of the latest C++ standard
  - Strict warning flags
  - Warnings as errors in release builds
  - Address sanitization in debug builds
  - Undefined behaviour detection in debug builds
  - C unit testing support with `check`
  - C++ unit testing support with `catch`
  - Travis support
  - Appveyor support with multiple compilers
  - Coveralls support

The idea behind the boilerplate is to get any project up and running with the
tooling needed for a modern C or C++ codebase. The integration of coverage,
unit testing and benchmarking allows almost instant access to those features of
the tooling. The Travis and Appveyor YAML scripts allow for continuous
integration to be running from the first push of new code.

Getting Started
---------------

1. Clone the repository to get the boilerplate:

```
git clone https://github.com/vcatechnology/cmake.git my-project
cd my-project
```

2. Update the project name in the `CMakeList.txt` file:

```
sed -i 's|project([^)]\+)|project(my_project)|' CMakeList.txt
```

3. Modify the boilerplate to suit the needs of the of the new project. This
   will require changes to:

     - `README.md`
     - `LICENSE.md`
     - `CONTRIBUTE.md`
     - Namespaces in C++ files
     - Function prefixes in C files
     - Removal of the C or C++ part of the build if necessary

4. Push up the changes to your new project

```
git remote set-url origin https://github.com/user/my-project.git
git push -u origin master
```

5. Enable Travis, Appveyor and Coveralls for the project so that all the
   goodness of the tooling can occur.

6. Start writing code! The `README.md` in `src` and `test` will provide more
   information

Building
--------

The project is a standard out of tree CMake project. To build the code run the
following commands:

```
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
make test
```

On Windows it is possible to create and build Visual Studio projects from the
command line:

```
mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" ..
set "msbuild_opts=/clp:OnlyErrors;OnlyWarnings /nologo /m /v:m"
msbuild %msbuild_opts% /p:Configuration=Release /p:Platform=x64 boilerplate.sln
msbuild %msbuild_opts% RUN_TESTS.vcxproj
```
