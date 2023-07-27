cmake_minimum_required(VERSION 3.25.1)
project(package-flashback)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "Source Files/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "Header Files/*.h")

include_directories("${PROJECT_SOURCE_DIR}/Header Files")

add_executable(${PROJECT_NAME} ${SOURCES})
