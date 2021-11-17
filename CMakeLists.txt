cmake_minimum_required(VERSION 3.0.0)
project(DexParser VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(header)

aux_source_directory(src SRC_LIST)
add_executable(DexParser Main.cpp ${SRC_LIST})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
