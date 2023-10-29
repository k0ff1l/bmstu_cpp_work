cmake_minimum_required(VERSION 3.14)
project(example)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 23)
set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(${TEST_NAME} example_test.cpp)

# Добавляем все исходные файлы из папки let_4_phones
file(GLOB SOURCES_LET_4 "let_4_phones/*")

# Добавляем все исходные файлы из папки let_5_bruteforce
file(GLOB SOURCES_LET_5 "let_5_bruteforce/*")

# Добавляем все исходные файлы из папки hw_2_string
file(GLOB SOURCES_HW_2_STRING "hw_2_string/*")

# Объединяем все списки исходных файлов
set(ALL_SOURCES ${SOURCES_LET_4} ${SOURCES_LET_5} ${SOURCES_HW_2_STRING})

# Добавляем исходные файлы к проекту
target_sources(${TEST_NAME} PRIVATE ${ALL_SOURCES})

target_link_libraries(${TEST_NAME} gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})
