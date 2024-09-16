# Library
SET(LIBRARY_NAME ${PROJECT_NAME})

ADD_LIBRARY(${LIBRARY_NAME} SHARED
  ${HEADERS}
  doc.hh
  distance-capsule-point.cc
  fitter.cc
  util.cc
  volume.cc
  )

SET_TARGET_PROPERTIES(${LIBRARY_NAME} PROPERTIES VERSION 3 SOVERSION 3.2.0)

TARGET_LINK_LIBRARIES(${LIBRARY_NAME} ${QHULL_LIBRARIES} roboptim-core::roboptim-core Eigen3::Eigen roboptim-core-plugin-ipopt::roboptim-core-plugin-ipopt Boost::filesystem)  
target_include_directories(
  ${LIBRARY_NAME} PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
#PKG_CONFIG_USE_DEPENDENCY(${LIBRARY_NAME} roboptim-core)
#PKG_CONFIG_USE_DEPENDENCY(${LIBRARY_NAME} roboptim-core-plugin-ipopt)

INSTALL(TARGETS ${LIBRARY_NAME}
  EXPORT ${TARGETS_EXPORT_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Executable
SET(EXECUTABLE_NAME capsule-generator)
ADD_EXECUTABLE(${EXECUTABLE_NAME} capsule-generator.cc)
TARGET_LINK_LIBRARIES(${EXECUTABLE_NAME} ${LIBRARY_NAME} boost_program_options boost_filesystem)

INSTALL(TARGETS ${EXECUTABLE_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
