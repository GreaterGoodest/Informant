#ifndef _BINARY_PARSING_
#define _BINARY_PARSING_

#include <elf.h>

#define BAD_TYPE -1
#define EXECUTABLE 0
#define SHARED_OBJECT 1

ssize_t load_binary(char *path, void **mapped_victim);
int determine_type(Elf64_Ehdr *header);

#endif