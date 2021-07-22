include_directories(test ${CMAKE_SOURCE_DIR}/include)
include_directories(test ${CMAKE_SOURCE_DIR}/src)

add_executable(assimp assimp.cpp)
target_link_libraries(assimp PUBLIC threepp)
