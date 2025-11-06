cmake_minimum_required(VERSION 3.10.0)
project(lab2 VERSION 0.1.0 LANGUAGES C CXX)

set_property(DIRECTORY . PROPERTY CMAKE_CONFIGURE_DEPENDS main.cpp)

find_package(Git QUIET)

if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-list --all --count

        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_COUNT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

else()
    set(GIT_COMMIT_COUNT "0")
endif()

add_definitions(-DVERSION_PROJECT=${GIT_COMMIT_COUNT})

add_executable(lab2 main.cpp)

configure_file(${CMAKE_SOURCE_DIR}/ip_filter.tsv ${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv COPYONLY)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(test_ip_filter tests/test_ip_filter.cpp)
target_link_libraries(test_ip_filter GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_ip_filter)

target_include_directories(lab2 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PACKAGE_NAME "lab2")

set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

if(WIN32)
    set(CPACK_GENERATOR "ZIP")
endif()

if(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kiegechev Pavel <kiegechev09@gmail.com>")
endif()

install(TARGETS lab2 DESTINATION bin)
install(FILES ip_filter.tsv DESTINATION bin)

include(CPack)

