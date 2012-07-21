cmake_minimum_required (VERSION 2.6)
project (Riack++)

OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)

ENABLE_TESTING()

SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

find_package(riack REQUIRED)
include_directories(${RIACK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${RIACK_LIBRARIES})

SET(RIACKCPP_SRC	Client.cpp
					Bucket.cpp
					Object.cpp)

# SET(TESTS_MAIN_SRC	)

SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

add_library (riack_cpp ${LIB_TYPE} ${RIACKCPP_SRC})
target_link_libraries(riack_cpp ${LIBS})

INSTALL(TARGETS riack_cpp
        DESTINATION lib
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
        
INSTALL(FILES riack_cpp/client.h
        DESTINATION include
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

# add_executable(tests ${TESTS_MAIN_SRC})
# target_link_libraries(tests ${LIBS} riack)

IF (WIN32)
ELSE()
   SET_TARGET_PROPERTIES(riack_cpp PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (WIN32)
