project("ApproxMVBBExample-MVBB")

set (CMAKE_CXX_STANDARD 11)
find_package(ApproxMVBB REQUIRED COMPONENTS)

add_executable(${PROJECT_NAME}  src/main.cpp )
target_link_libraries(${PROJECT_NAME} "ApproxMVBB::Core")

