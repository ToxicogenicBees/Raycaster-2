cmake_minimum_required(VERSION 3.15)
project(Raytracer)

set(EXE_NAME_VAR render)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

# ------------------------------
# Source files
# ------------------------------
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)
add_executable(${EXE_NAME_VAR} ${SRC_FILES})

# ------------------------------
# Include directories
# ------------------------------
target_include_directories(${EXE_NAME_VAR} PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/lib/"
    "${CMAKE_SOURCE_DIR}/src"
)

# ------------------------------
# Output folder
# ------------------------------
set_target_properties(${EXE_NAME_VAR} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
