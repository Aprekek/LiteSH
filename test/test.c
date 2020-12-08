#include "../thirdparty/ctest.h"
#include "filesystem.h"
#include <cstdio>

CTEST(filesystem, getFileSize)
{
    int expected = 0;

    FILE* test;
    test = fopen("test.txt", "w");
    int result = getFileSize("test.txt");

    fclose(test);
    remove("rest.txt");

    ASSERT_EQUAL(expected, result);
}