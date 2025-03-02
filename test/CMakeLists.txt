file(GLOB TEST_SOURCES "*.cpp") 

add_executable(polinom_tests ${TEST_SOURCES})

add_subdirectory(${CMAKE_SOURCE_DIR}/gtest ${CMAKE_BINARY_DIR}/gtest)

target_link_libraries(polinom_tests PRIVATE list_lib polinom_lib gtest)

# Указываем путь для поиска заголовков
target_include_directories(polinom_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(polinom_tests PRIVATE ${CMAKE_BINARY_DIR}/gtest)

# Добавляем команду для автоматического запуска тестов после сборки
add_test(polinom_tests polinom_tests)