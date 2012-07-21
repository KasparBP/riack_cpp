# - Try to find riack
# Once done this will define
#
#  RIACK_FOUND - system has riack
#  RIACK_INCLUDE_DIR - the riack include directory
#  RIACK_LIBRARIES - Link these to use riack
#  RIACK_DEFINITIONS - Compiler switches required for using riack

if ( RIACK_INCLUDE_DIR AND RIACK_LIBRARIES )
   # in cache already
   SET(riack_FIND_QUIETLY TRUE)
endif ( RIACK_INCLUDE_DIR AND RIACK_LIBRARIES )

if ( WIN32 )
   SET (RIACK_INCLUDE_DIRS C:/Development/precompiled-riack)
   SET (RIACK_LIBRARY_DIRS C:/Development/precompiled-riack)
endif ( WIN32 )

# use pkg-config to get the directories and then use these values
# in the FIND_PATH() and FIND_LIBRARY() calls
if( NOT WIN32 )
  find_package(PkgConfig)

  pkg_check_modules(RIACK riack)

  set(RIACK_DEFINITIONS ${RIACK_CFLAGS})
endif( NOT WIN32 )

FIND_PATH(RIACK_INCLUDE_DIR 
  NAMES riack.h
  PATHS
  ${RIACK_INCLUDE_DIRS}
)

FIND_LIBRARY(RIACK_LIBRARIES 
  NAMES riack
  PATHS
  ${RIACK_LIBRARY_DIRS}
)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(riack DEFAULT_MSG RIACK_INCLUDE_DIR RIACK_LIBRARIES )

# show the RIACK_INCLUDE_DIR variables only in the advanced view
MARK_AS_ADVANCED(RIACK_INCLUDE_DIR RIACK_LIBRARIES )

