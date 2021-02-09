#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#include "binary_parsing.h"

extern ssize_t load_binary(const char *path, void **mapped_victim);

int __wrap_open (const char *__path, int __oflag, ...)
{
    check_expected_ptr(__path);
    check_expected(__oflag);
    int retval = mock_type(int);
    if (retval != 0) { return retval; }

    return retval;
}


void __wrap_perror (const char *__s)
{
    check_expected_ptr(__s);
}


void *__wrap_memset (void *__s, int __c, size_t __n)
{
    return malloc(1);
}


int __wrap_lstat (const char *__restrict __file,
		  struct stat *__restrict __buf)
{
    return -1;
}


void *__wrap_mmap (void *__addr, size_t __len, int __prot,
		   int __flags, int __fd, __off_t __offset)
{
    return malloc(1);
}


int __wrap_close (int __fd)
{
    return 0;
}


static void test_open_failure(void ** state)
{
    int retval = 0;
    void *mapped_victim;
    const char *binary_name = "bad.bin";
    const char *open_failure = "failed to open victim binary";

    will_return(__wrap_open, EACCES);

    expect_string(__wrap_open, __path, binary_name);
    expect_value(__wrap_open, __oflag, O_RDWR);
    expect_string(__wrap_perror, __s, open_failure);

    retval = load_binary(binary_name, &mapped_victim);
    assert_int_equal(retval, -1);
}

int main (){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_open_failure)
    };

    int count_fail_tests = cmocka_run_group_tests(tests, NULL, NULL);

    return count_fail_tests;
}