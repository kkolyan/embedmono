cmake_minimum_required(VERSION 3.17)
project(embedmono)

set(CMAKE_CXX_STANDARD 17)

add_executable(embedmono main.cpp)

if (NOT DEFINED MONO_HOME)
    set(MONO_HOME "C:/Program Files/Mono")
endif ()

target_compile_definitions(embedmono PRIVATE MONO_HOME=\"${MONO_HOME}\")

target_include_directories(embedmono PRIVATE "${MONO_HOME}/include/mono-2.0")

target_link_libraries(embedmono PRIVATE
        "${MONO_HOME}/bin/mono-2.0-sgen.dll"
        )

configure_file("${MONO_HOME}/bin/mono-2.0-sgen.dll" "${PROJECT_BINARY_DIR}/mono-2.0-sgen.dll" COPYONLY)

list(APPEND cs "Cat.cs")
list(APPEND cs "Dog.cs")
foreach (csFile ${cs})
    configure_file("${PROJECT_SOURCE_DIR}/cs/${csFile}" "${PROJECT_BINARY_DIR}/${csFile}")
endforeach()
