#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "helpers.h"

extern void print_usage();

int __wrap_puts (const char *__s)
{
    check_expected_ptr(__s);

    return 0;
}

static void test_print_correct(void ** state)
{
    const char *help_string = "Usage: ./informant [victim binary]";
    expect_string(__wrap_puts, __s, help_string);
    print_usage();
}


int main (){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_print_correct)
    };

    int count_fail_tests = cmocka_run_group_tests(tests, NULL, NULL);

    return count_fail_tests;
}