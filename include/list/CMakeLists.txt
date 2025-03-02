add_library(list_lib STATIC list.h list.cpp)

target_link_libraries(list_lib PUBLIC polinom_lib)


target_include_directories(list_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})