# Requires at least CMake 2.8 to configure the package.
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_CXX_STANDARD 14)

SET(PROJECT_NAME roboptim-capsule)
SET(PROJECT_DESCRIPTION
  "An automated optimal capsule generator over polyhedrons.")
SET(PROJECT_URL "https://github.com/roboptim/roboptim-capsule")
set(PROJECT_USE_CMAKE_EXPORT TRUE)

# Use MathJax for Doxygen formulae
SET(DOXYGEN_USE_MATHJAX "YES")


SET(${PROJECT_NAME}_HEADERS
  include/roboptim/capsule/distance-capsule-point.hh
  include/roboptim/capsule/fwd.hh
  include/roboptim/capsule/fitter.hh
  include/roboptim/capsule/qhull.hh
  include/roboptim/capsule/types.hh
  include/roboptim/capsule/util.hh
  include/roboptim/capsule/volume.hh
)

SET(CXX_DISABLE_WERROR TRUE)
INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/qhull.cmake)
INCLUDE(cmake/eigen.cmake)

compute_project_args(PROJECT_ARGS LANGUAGES CXX C)
project(${PROJECT_NAME} ${PROJECT_ARGS})

# Where to compile shared objects
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Declare dependencies
SET(BOOST_COMPONENTS
  date_time filesystem system thread program_options unit_test_framework)
SEARCH_FOR_BOOST()
SEARCH_FOR_QHULL()
ADD_project_DEPENDENCY(Eigen3)
ADD_PROJECT_DEPENDENCY(Eigen3)
SEARCH_FOR_EIGEN("eigen3 >= 3.2.5")
ADD_project_DEPENDENCY(roboptim-core )
ADD_project_DEPENDENCY(roboptim-core-plugin-ipopt)

set(BOOST_REQUIRED_COMPONENTS filesystem)
add_project_dependency(Boost REQUIRED COMPONENTS ${BOOST_REQUIRED_COMPONENTS})

# Add main library to pkg-config file.
PKG_CONFIG_APPEND_LIBS(${PROJECT_NAME})

ADD_SUBDIRECTORY(src)
#ADD_SUBDIRECTORY(tests)

