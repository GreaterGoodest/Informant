#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#include "helpers.h"
#include "binary_parsing.h"


int main(int argc, char **argv)
{
    int retval = 0;
    int victim_type = -1;
    size_t victim_size = 0;
    char *victim = NULL;
    void *mapped_victim = NULL;
    Elf64_Ehdr *victim_header = NULL;

    /* Appropriate number of arguments? */
    if (argc < 2){ print_usage(); retval = -1; goto cleanup; }
    victim = argv[1];

    victim_size = load_binary(victim, &mapped_victim);
    if (victim_size < 0){ perror("failed to parse victim"); retval = -1; goto cleanup; }
    victim_header = (Elf64_Ehdr *) mapped_victim;

    victim_type = determine_type(victim_header);
    if (victim_type < 0){ perror("Improper victim"); retval = -1; goto cleanup; }

cleanup:
    if (mapped_victim != NULL) munmap(mapped_victim, victim_size);
    return retval;
}