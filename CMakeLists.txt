cmake_minimum_required(VERSION 2.8.12 )

# Set project name and version
project( tronmoi )
set( PROJECT_MAJOR_VERSION 0 )
set( PROJECT_MINOR_VERSION 2 )
set( PROJECT_PATCH_VERSION 0 )

# Set compiler flags
add_compile_options( -std=c++11 )
add_compile_options( -Wall )
add_compile_options( -Wextra )
add_compile_options( -pedantic )
add_compile_options( -pedantic-errors )

# Set source and include dirs.
set( SOURCE_DIR "${CMAKE_SOURCE_DIR}/src" )
set( INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src" )
include_directories( ${INCLUDE_DIR} )

# Source files
set( SOURCE_FILES
    "${SOURCE_DIR}/main.cpp"
    "${SOURCE_DIR}/game_grid.cpp"
    "${SOURCE_DIR}/tronmoi.cpp"
)

# Include SDL
include( FindPkgConfig )
find_package( SDL REQUIRED )
find_package( SDL_ttf REQUIRED )
include_directories( ${SDL_INCLUDE_DIR} ${SDL_TTF_INCLUDE_DIR} )

# Set executable
add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )
target_link_libraries( ${PROJECT_NAME} ${SDL_LIBRARY} ${SDL_TTF_LIBRARY} )
