cmake_minimum_required(VERSION 3.16)
project(llm_rag_examples CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(CURL REQUIRED)

add_executable(chunk_demo examples/chunk_demo.cpp)
target_include_directories(chunk_demo PRIVATE include)
target_link_libraries(chunk_demo CURL::libcurl)

add_executable(basic_rag examples/basic_rag.cpp)
target_include_directories(basic_rag PRIVATE include)
target_link_libraries(basic_rag CURL::libcurl)
