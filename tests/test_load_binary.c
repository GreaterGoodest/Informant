#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sys/types.h>
#include <sys/mman.h>
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


int __wrap_lstat (const char *__restrict __file,
		  struct stat *__restrict __buf)
{
    check_expected_ptr(__file);
    check_expected(__buf->st_size);

    int retval = mock_type(int);
    if (retval != 0) { return retval; }

    __buf->st_size = 4096;

    return retval;
}


void *__wrap_mmap (void *__addr, size_t __len, int __prot,
		   int __flags, int __fd, __off_t __offset)
{
    void *retval = mock_ptr_type(void *);
    return retval;
}


int __wrap_close (int __fd)
{
    return 0;
}


static void test_open_failure(void ** state)
{
    int retval = 0;
    void *mapped_victim = NULL;
    const char *binary_name = "bad.bin";
    const char *open_failure = "failed to open victim binary";

    will_return(__wrap_open, -1);

    expect_string(__wrap_open, __path, binary_name);
    expect_value(__wrap_open, __oflag, O_RDWR);
    expect_string(__wrap_perror, __s, open_failure);

    retval = load_binary(binary_name, &mapped_victim);
    assert_int_equal(retval, -1);
}


static void test_lstat_failure(void ** state)
{
    int retval = 0;
    void *mapped_victim = NULL;
    const char *binary_name = "bad.bin";
    const char *lstat_failure = "failed to get victim stats";

    will_return(__wrap_open, 4);
    will_return(__wrap_lstat, -1);

    expect_string(__wrap_open, __path, binary_name);
    expect_value(__wrap_open, __oflag, O_RDWR);
    expect_string(__wrap_lstat, __file, binary_name);
    expect_value(__wrap_lstat, __buf->st_size, 0);
    expect_string(__wrap_perror, __s, lstat_failure);

    retval = load_binary(binary_name, &mapped_victim);
    assert_int_equal(retval, -1);
}


static void test_mmap_failure(void ** state)
{
    int retval = 0;
    void *mapped_victim = NULL;
    const char *binary_name = "bad.bin";
    const char *mmap_failure = "Failed to map victim";
    will_return(__wrap_open, 4);
    will_return(__wrap_lstat, 0);
    will_return(__wrap_mmap, MAP_FAILED);

    expect_string(__wrap_open, __path, binary_name);
    expect_value(__wrap_open, __oflag, O_RDWR);
    expect_string(__wrap_lstat, __file, binary_name);
    expect_value(__wrap_lstat, __buf->st_size, 0);
    expect_string(__wrap_perror, __s, mmap_failure);

    retval = load_binary(binary_name, &mapped_victim);
    assert_int_equal(retval, -1);
}


static void test_load_binary_success(void ** state)
{
    int retval = 0;
    int binary_size = 4096;
    void *mapped_victim = NULL;
    const char *binary_name = "bad.bin";
    will_return(__wrap_open, 4);
    will_return(__wrap_lstat, 0);
    will_return(__wrap_mmap, mapped_victim);

    expect_string(__wrap_open, __path, binary_name);
    expect_value(__wrap_open, __oflag, O_RDWR);
    expect_string(__wrap_lstat, __file, binary_name);
    expect_value(__wrap_lstat, __buf->st_size, 0);

    retval = load_binary(binary_name, &mapped_victim);
    assert_int_equal(retval, binary_size);

}


int main (){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_open_failure),
        cmocka_unit_test(test_lstat_failure),
        cmocka_unit_test(test_mmap_failure),
        cmocka_unit_test(test_load_binary_success)
    };

    int count_fail_tests = cmocka_run_group_tests(tests, NULL, NULL);

    return count_fail_tests;
}