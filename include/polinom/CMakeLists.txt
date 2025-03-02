add_library(polinom_lib STATIC polinom.h polinom.cpp)

target_link_libraries(polinom_lib PUBLIC list_lib)


target_include_directories(polinom_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})