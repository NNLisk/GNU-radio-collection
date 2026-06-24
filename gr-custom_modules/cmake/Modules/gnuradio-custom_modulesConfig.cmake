find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_CUSTOM_MODULES gnuradio-custom_modules)

FIND_PATH(
    GR_CUSTOM_MODULES_INCLUDE_DIRS
    NAMES gnuradio/custom_modules/api.h
    HINTS $ENV{CUSTOM_MODULES_DIR}/include
        ${PC_CUSTOM_MODULES_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_CUSTOM_MODULES_LIBRARIES
    NAMES gnuradio-custom_modules
    HINTS $ENV{CUSTOM_MODULES_DIR}/lib
        ${PC_CUSTOM_MODULES_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-custom_modulesTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_CUSTOM_MODULES DEFAULT_MSG GR_CUSTOM_MODULES_LIBRARIES GR_CUSTOM_MODULES_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_CUSTOM_MODULES_LIBRARIES GR_CUSTOM_MODULES_INCLUDE_DIRS)
