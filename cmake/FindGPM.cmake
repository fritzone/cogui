# - Try to find LIBGPM
# Once done this will define
#  LIBGPM_FOUND - System has LIBGPM
#  LIBGPM_INCLUDE_DIRS - The LIBGPM include directories
#  LIBGPM_LIBRARIES - The libraries needed to use LIBGPM
#  LIBGPM_DEFINITIONS - Compiler switches required for using LIBGPM

find_package(PkgConfig)
pkg_check_modules(PC_LIBGPM QUIET libgpm)
set(LIBGPM_DEFINITIONS ${PC_LIBGPM_CFLAGS_OTHER})

find_path(LIBGPM_INCLUDE_DIR gpm.h
          HINTS ${PC_LIBGPM_INCLUDEDIR} ${PC_LIBGPM_INCLUDE_DIRS}
          PATH_SUFFIXES LIBGPM )

find_library(LIBGPM_LIBRARY NAMES gpm LIBGPM
             HINTS ${PC_LIBGPM_LIBDIR} ${PC_LIBGPM_LIBRARY_DIRS} 
             DOC "Path to libgpm.so or .lib or .a")

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBGPM_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBGPM  DEFAULT_MSG
                                  LIBGPM_LIBRARY LIBGPM_INCLUDE_DIR)

mark_as_advanced(LIBGPM_INCLUDE_DIR LIBGPM_LIBRARY )

set(LIBGPM_LIBRARIES ${LIBGPM_LIBRARY} )
set(LIBGPM_INCLUDE_DIRS ${LIBGPM_INCLUDE_DIR} )

