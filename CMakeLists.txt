cmake_minimum_required(VERSION 3.10.0)
project(CourseWorkOOP VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(src)

find_package(fmt CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)

add_executable(CourseWorkOOP src/main.cpp)

target_link_libraries(CourseWorkOOP PRIVATE fmt::fmt)
target_link_libraries(CourseWorkOOP PRIVATE Crow::Crow asio::asio)
target_link_libraries(CourseWorkOOP PRIVATE ws2_32)
target_link_libraries(CourseWorkOOP PRIVATE wsock32)
