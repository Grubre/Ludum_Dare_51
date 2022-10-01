cmake_minimum_required(VERSION 3.21)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(
    ludum_dare_51
    VERSION 0.0.1
    DESCRIPTION ""
    LANGUAGES CXX
)


# find_program(CLANG_TIDY NAMES "clang-tidy" "clang-tidy-10" "clang-tidy-11" REQUIRED)
# set (CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
                    -Wall\
                    -Wextra\
                    -Wpedantic\
                    -Werror\
")


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}\
                          -fsanitize=address\
")


set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}\
                                 -fsanitize=address\
")


file(GLOB_RECURSE SRC src/*.cpp)


add_executable(main ${SRC})

include_directories(src)


if(STATIC_LIBS)
    set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML COMPONENTS system audio window graphics REQUIRED)


target_link_libraries(main sfml-graphics sfml-audio)
