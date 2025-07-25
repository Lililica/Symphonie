cmake_minimum_required(VERSION 3.20)

# You can set the name of your project here
project(Symphonie)
add_executable(${PROJECT_NAME})

# Choose your C++ version
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Enable many good warnings.
# /WX and -Werror enable "warnings as errors": This means that your code won't compile if you have any warning.
# This forces you to take warnings into account, which is a good practice because warnings are here for a reason and can save you from a lot of bugs!
# If this is too strict for you, you can remove /WX and -Werror.
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wimplicit-fallthrough)
endif()

# Set the folder where the executable is created
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Prevents compiler-specific extensions to C++ because they might allow code to compile on your machine but not on other people's machine
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF)

# Add all the source files (only .cpp, .c, and .cu)
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.c src/*.cu)
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)


# Add quick-imgui library
add_subdirectory(lib/quick_imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE quick_imgui::quick_imgui)

# Link OpenGL on Windows
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
endif()


find_package(raylib REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)






