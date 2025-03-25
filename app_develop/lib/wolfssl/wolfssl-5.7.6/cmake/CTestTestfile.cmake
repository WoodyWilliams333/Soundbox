# CMake generated Testfile for 
# Source directory: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6
# Build directory: /home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit_test "/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/tests/unit.test")
set_tests_properties(unit_test PROPERTIES  WORKING_DIRECTORY "/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6" _BACKTRACE_TRIPLES "/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/CMakeLists.txt;2507;add_test;/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/CMakeLists.txt;0;")
add_test(wolfcrypttest "/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/wolfcrypt/test/testwolfcrypt")
set_tests_properties(wolfcrypttest PROPERTIES  WORKING_DIRECTORY "/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6" _BACKTRACE_TRIPLES "/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/CMakeLists.txt;2549;add_test;/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/CMakeLists.txt;0;")
