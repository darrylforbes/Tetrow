cmake_minimum_required(VERSION 3.3)
project(final-project CXX)
include(.eecs211/cmake/CMakeLists.txt)

set(MODEL_SRC
        src/board.cpp
        src/model.cpp
        src/piece.cpp
        src/tile.cpp)

add_program(main
        src/controller.cpp
        src/main.cpp
        src/view.cpp
        ${MODEL_SRC})
target_link_libraries(main ge211)

add_test_program(model_test
    test/model_test.cpp
    ${MODEL_SRC})
target_link_libraries(model_test ge211)
