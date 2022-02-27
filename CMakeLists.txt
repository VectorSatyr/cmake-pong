# CMakeList.txt : CMake project for cmake-pong, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("cmake-pong")

find_package(SDL2 CONFIG REQUIRED)

# Add source to this project's executable.
add_executable (cmake-pong   "include/msdll/msdll.hpp" "src/msdll/events.cpp" "src/msdll/exception.cpp" "src/msdll/function.cpp" "src/msdll/renderer.cpp" "src/msdll/texture.cpp" "src/msdll/timer.cpp" "src/msdll/window.cpp" "include/game.hpp" "src/ball.cpp" "src/game.cpp" "apps/app.cpp" "src/paddle.cpp" "src/rect.cpp")

# TODO: Add tests and install targets if needed.
target_include_directories (cmake-pong PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(cmake-pong PRIVATE SDL2::SDL2 SDL2::SDL2main)
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/
)
add_dependencies(cmake-pong copy_assets)

# Copy SDL2 DLLs to output folder on Windows
if(WIN32)
    foreach(DLL ${SDL2_DLLS})
        add_custom_command(TARGET cmake-pong POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:cmake-pong>)
    endforeach()
endif()