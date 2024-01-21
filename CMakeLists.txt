cmake_minimum_required(VERSION 3.16)

project(wingui)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(WINDOW
    ./GUI/Window/IWindow.cpp
    ./GUI/Window/Windows/Window.cpp
    ./GUI/Window/IWindow.cpp
)

set(PROJECT_SOURCE_FILES
    main.cpp
)

add_executable(wingui WIN32 ${PROJECT_SOURCE_FILES} ${WINDOW})

target_link_libraries(wingui PRIVATE User32.lib Gdi32.lib)
