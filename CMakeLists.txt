cmake_minimum_required(VERSION 3.16)
project(spaceinvaders_raylib_prototype LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try to find raylib, but allow building tests without it
find_package(raylib QUIET)

add_executable(spaceinvaders_proto src/main.cpp src/player.cpp)
if (raylib_FOUND)
	target_include_directories(spaceinvaders_proto PRIVATE ${RAYLIB_INCLUDE_DIRS})
	target_link_libraries(spaceinvaders_proto PRIVATE ${RAYLIB_LIBRARIES})
else()
	message(WARNING "raylib not found: the game target will fail to run until raylib is installed. Tests can still be built.")
endif()

# --- Testing (Catch2 via FetchContent) ---
include(FetchContent)
FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v2.13.10
)
FetchContent_MakeAvailable(catch2)

add_executable(tests tests/test_player.cpp src/player.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(tests PRIVATE Catch2::Catch2)
enable_testing()
add_test(NAME player_tests COMMAND tests)
