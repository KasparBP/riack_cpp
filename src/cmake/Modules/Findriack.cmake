# - Try to find riack
# Once done this will define
#
#  RIACK_FOUND - system has ProtoBufC
#  RIACK_INCLUDE_DIR - the ProtoBufC include directory
#  RIACK_LIBRARIES - Link these to use ProtoBufC
#  RIACK_DEFINITIONS - Compiler switches required for using ProtoBufC
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


if ( PROTOBUFC_INCLUDE_DIR )
   # in cache already
   SET(riack_FIND_QUIETLY TRUE)
endif ( PROTOBUFC_INCLUDE_DIR )

if ( WIN32 )
   SET (PROTOBUFC_INCLUDE_DIRS C:/Development/precompiled-riack/include)
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

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(riack DEFAULT_MSG RIACK_INCLUDE_DIR )

# show the RIACK_INCLUDE_DIR variables only in the advanced view
MARK_AS_ADVANCED(PROTOBUFC_INCLUDE_DIR )

