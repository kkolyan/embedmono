cmake_minimum_required(VERSION 3.17)
project(embedmono)

set(CMAKE_CXX_STANDARD 17)

add_executable(embedmono main.cpp)

target_include_directories(embedmono PRIVATE "C:/Program Files/Mono/include/mono-2.0")

#target_link_libraries(embedmono PRIVATE
#        "C:/Program Files/Mono/lib/mono-2.0-sgen.lib"
#        "C:/Program Files/Mono/lib/libmono-static-sgen.lib"
#        "C:/Program Files/Mono/lib/MonoPosixHelper.lib"
#)

target_link_libraries(embedmono PRIVATE
        "C:/Program Files/Mono/bin/mono-2.0-sgen.dll"
        )

configure_file(${PROJECT_SOURCE_DIR}/cs/Dog.cs ${PROJECT_BINARY_DIR}/Dog.cs)

