cmake_minimum_required(VERSION 3.21)
project(CHomPjl)

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../.install/cmake/Modules)

find_package(Boost 1.74.0 REQUIRED COMPONENTS chrono system thread serialization)
find_package(Threads)
find_package(GMP REQUIRED)

find_package(JlCxx REQUIRED)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")
message(STATUS "Found JlCxx at ${JlCxx_location}")

include_directories(
    ${CMAKE_SOURCE_DIR}/../include
    ${Boost_INCLUDE_DIRS}
)

link_directories(
    /usr/local/lib
    /opt/local/lib
)

set(LIBS ${LIBS}
         ${CMAKE_THREAD_LIBS_INIT}
         ${Boost_LIBRARIES}
         ${GMP_LIBRARIES}
         ${GMPXX_LIBRARIES}
         JlCxx::cxxwrap_julia
)

set(TARGETS Fieldjl)

foreach(TARGET ${TARGETS})
    add_library(${TARGET} SHARED ${TARGET}.cpp)
    target_link_libraries(${TARGET} ${LIBS})
endforeach(TARGET)

install(TARGETS ${TARGETS}
        LIBRARY DESTINATION lib)
