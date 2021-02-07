#include <elf.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <sys/types.h>

#include "binary_parsing.h"

extern int determine_type(Elf64_Ehdr *header);

static void test_determine_type_core(void ** state)
{
    int retval = 0;
    Elf64_Ehdr header;

    memset(&header, 0, sizeof(header));
    header.e_type = ET_CORE;
    header.e_ident[EI_CLASS] = ELFCLASS64;


    retval = determine_type(&header);
    assert_int_equal(retval, BAD_TYPE);   
}


static void test_determine_type_relocatable(void ** state)
{
    int retval = 0;
    Elf64_Ehdr header;

    memset(&header, 0, sizeof(header));
    header.e_type = ET_REL;
    header.e_ident[EI_CLASS] = ELFCLASS64;


    retval = determine_type(&header);
    assert_int_equal(retval, BAD_TYPE);   
}


int main (){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test(test_determine_type_core),
        cmocka_unit_test(test_determine_type_relocatable)
    };

    int count_fail_tests = cmocka_run_group_tests(tests, NULL, NULL);

    return count_fail_tests;
}