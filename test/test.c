#include "../thirdparty/ctest.h"
#include "filesystem.h"
#include <cstdio>

CTEST(filesystem, getFileSize)
{
    int expected = 69;
    int result = getFileSize("./test/folder_test/test.txt");

    ASSERT_EQUAL(expected, result);
}

CTEST(filesystem, getDirSize)
{
    int expected = 54 + 69;
    int result = getDirSize("./test/folder_test");

    ASSERT_EQUAL(expected, result);
}

CTEST(filesystem, displayAllFiles)
{
    int expected = 0;
    int result = displayAllFiles("./test/folder_test");

    ASSERT_EQUAL(expected, result);
}

CTEST(filesystem, deleteFile)
{
    FILE *test;
    test = fopen("test3.txt", "w");
    
    int expected = -1;
    int result = deleteFile("test3.txt");

    ASSERT_EQUAL(expected, result);
}

CTEST(filesystem, copyFile)
{
    FILE *test;
    test = fopen("test4.txt", "w");

    int expected = 0;
    int result = copyFile("./test/folder_test/folder_test2", "test4.txt");

    remove("test4.txt");

    ASSERT_EQUAL(expected, result);
}

CTEST(filesystem, moveFile)
{
    FILE *test;
    test = fopen("test5.txt", "w");

    int expected = -1;
    int result = moveFile("./test/folder_test/folder_test2", "test5.txt");

    ASSERT_EQUAL(expected, result);
}