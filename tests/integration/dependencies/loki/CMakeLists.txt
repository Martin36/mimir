cmake_minimum_required(VERSION 3.21)
project(InstallLoki)

include(ExternalProject)


list(APPEND CMAKE_ARGS
    -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_PREFIX_PATH=${CMAKE_INSTALL_PREFIX}
    -DCMAKE_BUILD_TYPE=Release
    )

message(STATUS "Preparing external project \"loki\" with args:")
foreach(CMAKE_ARG ${CMAKE_ARGS})
    message(STATUS "-- ${CMAKE_ARG}")
endforeach()

ExternalProject_Add(
    loki
    GIT_REPOSITORY https://github.com/drexlerd/Loki.git
    GIT_TAG 4f1e99336e5f32c8a52ad1fa3ea133af47dafea3
    PREFIX ${CMAKE_BINARY_DIR}/loki
    DEPENDS boost abseil
    CMAKE_ARGS ${CMAKE_ARGS}
)
