cmake_minimum_required(VERSION 3.14)
project(bmstu_cpp_work)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 23)
set(TEST_NAME ${PROJECT_NAME}_tests)

# Добавляем все летучки
file(GLOB SOURCES_LET "let_*/*.h" "let_*/*.cpp")

# То что нужно удалить
file(GLOB REMOVE_SOURCES "let_6_db/*" "let_7_palindrome/*" "let_3_fresco/*" "let_9_perfect/*" "sandbox/*")

# Объединяем все списки исходных файлов
set(ALL_SOURCES ${SOURCES_LET})

# Удаляем то, что нужно удалить
list(REMOVE_ITEM ALL_SOURCES ${REMOVE_SOURCES})

add_executable(${TEST_NAME} ${ALL_SOURCES})
target_link_libraries(${TEST_NAME} gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

# Добавляем субдиректории
add_subdirectory(let_9_perfect)
add_subdirectory(let_6_db)
add_subdirectory(let_7_palindrome)
add_subdirectory(sandbox)
add_subdirectory(let_3_fresco)

# Не забыть исключить лишнее (добавить в REMOVE_SOURCES)
