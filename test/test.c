#include "../thirdparty/ctest.h"
#include "filesystem.h"

CTEST(filesystem, getFileSize)
{
    int expected = 3432;
    int result = getFileSize("./main.c");

    ASSERT_EQUAL(expected, result);
}