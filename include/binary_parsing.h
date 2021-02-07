#ifndef _BINARY_PARSING_
#define _BINARY_PARSING_

#include <elf.h>

#define BAD_TYPE -1
#define EXECUTABLE 0
#define SHARED_OBJECT 1


/**
 * Loads the victim binary into memory, and maps it so that any changes
 * propagate to disk
 * @param path String representing location of binary on disk
 * @param mapped_victim Stores the address of the newly mapped victim
 * 
 * @return Size of the loaded binary or -1 on error
 */
ssize_t load_binary(const char *path, void **mapped_victim);


/**
 * Determines whether binary is valid, and if so whether it is a shared object or not
 * @param header ELF Header
 * 
 * @return Constant representing binary type
 */
int determine_type(Elf64_Ehdr *header);

#endif