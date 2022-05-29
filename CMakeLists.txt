cmake_minimum_required(VERSION 3.0.0)
project(Drawer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(draw ${SOURCES} main.cpp)
add_executable(autotest ${SOURCES} test/test.cpp)

add_test(NAME manual COMMAND autotest WORKING_DIRECTORY ../test/manual)
set_tests_properties(manual PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME line COMMAND autotest WORKING_DIRECTORY ../test/line)
set_tests_properties(line PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME text COMMAND autotest WORKING_DIRECTORY ../test/text)
set_tests_properties(text PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME macro COMMAND autotest WORKING_DIRECTORY ../test/macro)
set_tests_properties(macro PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME color COMMAND autotest WORKING_DIRECTORY ../test/color)
set_tests_properties(color PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME undo COMMAND autotest WORKING_DIRECTORY ../test/undo)
set_tests_properties(undo PROPERTIES PASS_REGULAR_EXPRESSION "OK")

add_test(NAME redo COMMAND autotest WORKING_DIRECTORY ../test/redo)
set_tests_properties(redo PROPERTIES PASS_REGULAR_EXPRESSION "OK")

# add_test(NAME test_line COMMAND test_line -g 256 script.txt WORKING_DIRECTORY ../test/line)
# set_tests_properties(test_line PROPERTIES PASS_REGULAR_EXPRESSION "OK")
