cmake_minimum_required(VERSION 2.8)
project(hashcode_2016)

# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" ON)
# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
endif(DOXYGEN_FOUND)

if (UNIX)
  message(status "Setting GCC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -g -Wall")
else()
  message(status "Setting MSVC flags")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()
message(status "** CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories("hashcode/hashcode/include")

file(GLOB SRC_FOLDER
    "hashcode/hashcode/src/*.cpp"
	"hashcode/hashcode/src/main/main.cpp"

)
file(GLOB SRC_TEST_FOLDER
	"hashcode/hashcode/src/*.cpp"
    "hashcode/hashcode/src/test/main.cpp"
)

add_executable(hashcode ${SRC_FOLDER})
add_executable(hashcode_test ${SRC_TEST_FOLDER})
