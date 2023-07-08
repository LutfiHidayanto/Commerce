cmake_minimum_required(VERSION 3.0.0)
project(ecommerce VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Specify the source files in the "src" folder
file(GLOB SOURCES "src/*.cpp")

# Specify the header files in the "header" folder
file(GLOB HEADERS "header/*.h")

# Add the executable and link the source and header files
add_executable(MyExecutable ${SOURCES} ${HEADERS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
