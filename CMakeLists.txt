cmake_minimum_required(VERSION 3.22)
project(llvm_playground)
find_package(LLVM REQUIRED CONFIG)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(AddLLVM)



SET(INCLUDE_PROJECT_DIR "${CMAKE_SOURCE_DIR}/include/")
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)


function(add_llvm_playground target source)
    add_llvm_executable(${target} ${source})
    target_include_directories(${target} PRIVATE ${INCLUDE_PROJECT_DIR} ${LLVM_INCLUDE_DIRS})
endfunction()


add_llvm_playground(generate_add playground/1_generate_add/generate_add.cpp)
