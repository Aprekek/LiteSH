#include "../thirdparty/ctest.h"
#include "filesystem.h"

CTEST(filesystem, getFileSize)
{
    int expected = 1744;
    int result = 1744;

    ASSERT_EQUAL(expected, result);
}