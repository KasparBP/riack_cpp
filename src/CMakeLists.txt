cmake_minimum_required (VERSION 2.6)
project (Riack++)

SET(RIAK_TEST_SERVER_IP 127.0.0.1)
SET(RIAK_TEST_SERVER_PB_PORT 8081)

OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)

ENABLE_TESTING()

SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

find_package(riack REQUIRED)
include_directories(${RIACK_INCLUDE_DIRS})
set(LIBS ${LIBS} ${RIACK_LIBRARIES})

SET(RIACKCPP_SRC	RiackCpp.cpp
					RiackCpp.h
					RiackCppDefines.h
					Client.cpp
					Client.h
					Bucket.cpp
					Bucket.h
					Object.cpp
					Object.h
					String.cpp
					String.h
					Metadata.cpp
					Metadata.h
					MetadataArray.cpp
					MetadataArray.h
					Resolver.h
					DefaultResolver.h
					DefaultResolver.cpp
					RiakExceptions.h
					RiakExceptions.cpp
					)

SET(TEST_SRC        tests/TestHandler.cpp
                    tests/TestHandler.h
                    tests/ConnectionTest.cpp
                    tests/ConnectionTest.h
                    tests/GetPutTest.cpp
                    tests/GetPutTest.h
                    tests/ConflictedStateTest.cpp
                    tests/ConflictedStateTest.h
                    tests/RiakTestCase.cpp
                    tests/RiakTestCase.h
                    tests/TestCase.h)


SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

add_library (riack++ ${LIB_TYPE} ${RIACKCPP_SRC})
target_link_libraries(riack++ ${LIBS})

INSTALL(TARGETS riack++
        DESTINATION lib
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
        
INSTALL(FILES 	Client.h 
 				Bucket.h 
 				Object.h 
 				String.h
 				RiackCpp.h 
 				RiackCppDefines.h 
 				Resolver.h 
 				DefaultResolver.h 
 				RiakExceptions.h
 				Metadata.h
 				MetadataArray.h
 				
        DESTINATION include/riack++
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)


add_executable(tests ${TEST_SRC})
target_link_libraries(tests ${LIBS} riack++)

IF (WIN32)
ELSE()
   SET_TARGET_PROPERTIES(riack++ PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF (WIN32)

ADD_TEST(test-connect    ${CMAKE_CURRENT_BINARY_DIR}/tests ${RIAK_TEST_SERVER_IP} ${RIAK_TEST_SERVER_PB_PORT} connection)
ADD_TEST(test-getput     ${CMAKE_CURRENT_BINARY_DIR}/tests ${RIAK_TEST_SERVER_IP} ${RIAK_TEST_SERVER_PB_PORT} getput)
ADD_TEST(test-conflicted ${CMAKE_CURRENT_BINARY_DIR}/tests ${RIAK_TEST_SERVER_IP} ${RIAK_TEST_SERVER_PB_PORT} conflicted)
