add_executable(bool-test "bool-test.cxx")
add_test(
    NAME bool-test
    COMMAND bool-test)

add_executable(int-test "int-test.cxx")
add_test(
    NAME int-test
    COMMAND int-test)

add_executable(pointer-test "pointer-test.cxx")
add_test(
    NAME pointer-test
    COMMAND pointer-test)

add_executable(string-test "string-test.cxx")
add_test(
    NAME string-test
    COMMAND string-test)

add_executable(size-test "size-test.cxx")
add_test(
    NAME size-test
    COMMAND size-test)

add_executable(any-test "any-test.cxx")
add_test(
    NAME any-test
    COMMAND any-test)

add_executable(every-test "every-test.cxx")
add_test(
    NAME every-test
    COMMAND every-test)

add_executable(any-every-test "any-every-test.cxx")
add_test(
    NAME any-every-test
    COMMAND any-every-test)
