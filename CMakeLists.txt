# Set the minimum required cmake version to something relatively recent
cmake_minimum_required(VERSION 3.16)

# Define the project / project version / language
project(Garden LANGUAGES C)

# Make sure we can use SDL2
find_package(SDL2 REQUIRED)

# Create the executable target
add_executable(${PROJECT_NAME} WIN32)

# Add the source file
target_sources(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/garden.c")

# Make the SDL2 headers available
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
    $<BUILD_INTERFACE:${SDL2_INCLUDE_DIRS}>)

# Make sure we link against SDL2's library files 
target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${SDL2_LIBRARIES}
    $<$<NOT:$<PLATFORM_ID:Windows>>:m>)

# Copy SDL2.dll if on windows
if (WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
        VERBATIM
    )
endif()