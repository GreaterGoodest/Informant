#include <stdarg.h>
#include <stddef.h>
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
    if (retval < 0) { return retval; }

}


void __wrap_perror (const char *__s)
{

}


static void test_open_failure(void ** state)
{
    int retval = 0;
    void *mapped_victim;
    const char *binary_name = "bad.bin";

    will_return(__wrap_open, EACCES);
    expect_string(__wrap_open, __path, binary_name);
    expect_value(__wrap_open, __oflag, O_RDWR);
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