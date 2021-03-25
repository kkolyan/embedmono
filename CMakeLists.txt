cmake_minimum_required(VERSION 3.17)
project(embedmono)

set(CMAKE_CXX_STANDARD 17)

add_executable(embedmono main.cpp)

set(MONO_HOME "C:/Program Files/Mono")

target_compile_definitions(embedmono PRIVATE MONO_HOME=\"${MONO_HOME}\")

target_include_directories(embedmono PRIVATE "${MONO_HOME}/include/mono-2.0")

target_link_libraries(embedmono PRIVATE
        "${MONO_HOME}/bin/mono-2.0-sgen.dll"
        )

configure_file("${MONO_HOME}/bin/mono-2.0-sgen.dll" "${PROJECT_BINARY_DIR}/mono-2.0-sgen.dll" COPYONLY)
configure_file("${PROJECT_SOURCE_DIR}/cs/Dog.cs" "${PROJECT_BINARY_DIR}/Dog.cs")

