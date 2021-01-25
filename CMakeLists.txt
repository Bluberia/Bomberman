project(indie_studio)
cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
include(FindIrrlicht)

#set(CMAKE_CXX_COMPILER clang)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BUILD_TYPE})

include_directories(cmake_modules/include)
include_directories(sources/Game/Player)
include_directories(sources/Game/PowerUps)
include_directories(sources/Game/Wall)
include_directories(sources/Game)
include_directories(sources/Generation)
include_directories(sources)
include_directories(include)

link_directories(lib)

link_libraries(Irrlicht)

file(GLOB_RECURSE SRCS sources/*.cpp sources/*.hpp)

if (WIN32)
   link_libraries(IrrKlang)
elseif (UNIX)
	set(IRRKLANG_LIB libIrrKlang.so)
endif (WIN32)

add_executable(bomberman ${SRCS})
if (NOT WIN32)
    target_link_libraries(bomberman Irrlicht ${IRRKLANG_LIB})
elseif (NOT WIN32)
    target_link_libraries(bomberman libs)
endif (NOT WIN32)
