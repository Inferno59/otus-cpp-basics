cmake_minimum_required(VERSION 3.5)

project(2_5.details)

function(add_exec EXEC_NAME)
    add_executable(${EXEC_NAME} ${EXEC_NAME}.cpp)
    set_target_properties(${EXEC_NAME} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
endfunction()

add_exec(explicit)
add_exec(convertion)
add_exec(complex_value)
add_exec(complex_value_copy)
add_exec(destructors)
add_exec(move)