find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_DSTARDD gnuradio-dstardd)

FIND_PATH(
    GR_DSTARDD_INCLUDE_DIRS
    NAMES gnuradio/dstardd/api.h
    HINTS $ENV{DSTARDD_DIR}/include
        ${PC_DSTARDD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_DSTARDD_LIBRARIES
    NAMES gnuradio-dstardd
    HINTS $ENV{DSTARDD_DIR}/lib
        ${PC_DSTARDD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-dstarddTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_DSTARDD DEFAULT_MSG GR_DSTARDD_LIBRARIES GR_DSTARDD_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_DSTARDD_LIBRARIES GR_DSTARDD_INCLUDE_DIRS)
