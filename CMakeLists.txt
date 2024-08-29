cmake_minimum_required(VERSION 3.10)
project(EnDeCryptor)

include(ExternalProject)

set(wxWidgets_INSTALL_DIR ${CMAKE_BINARY_DIR}/wxWidgets)
set(wxWidgets_SOURCE_DIR ${CMAKE_SOURCE_DIR}/External/wxWidgets)

ExternalProject_Add(
    wxWidgets
    PREFIX ${CMAKE_BINARY_DIR}/wxWidgets
    SOURCE_DIR ${wxWidgets_SOURCE_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    BUILD_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/wxWidgets/src/wxWidgets-build --config Release
    INSTALL_COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/wxWidgets/src/wxWidgets-build --target install
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON
    LOG_INSTALL ON
)

include_directories(${CMAKE_SOURCE_DIR}/Include)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/Source/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

add_dependencies(${PROJECT_NAME} wxWidgets)

include_directories(${wxWidgets_INSTALL_DIR}/include)
link_directories(${wxWidgets_INSTALL_DIR}/lib)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

if(MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:WINDOWS)
endif()
