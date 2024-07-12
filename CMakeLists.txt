cmake_minimum_required(VERSION 3.0.0)
project(main VERSION 0.1.0)

INCLUDE_DIRECTORIES(
  /Users/usr_desarrollo/Proyectos/Personal/vcpkg/installed/x64-osx/include
)

LINK_DIRECTORIES(
  /Users/usr_desarrollo/Proyectos/Personal/vcpkg/installed/x64-osx/lib
)

add_executable(main scraper.cpp)
target_compile_features(main PRIVATE cxx_std_20)

find_package(cpr CONFIG REQUIRED)
target_link_libraries(main PRIVATE cpr::cpr)

find_package(LibXml2 REQUIRED)
target_link_libraries(main PRIVATE LibXml2::LibXml2)