cmake_minimum_required(VERSION 3.14)
project(let_repo)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

#glob all directories who end with _hw
file(GLOB let_dirs RELATIVE ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/let_*)
message("let_dirs: ${let_dirs}")
foreach (let_dir ${let_dirs})
    add_subdirectory(${let_dir})
endforeach ()

add_subdirectory(sandbox)