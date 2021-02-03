#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "binary_parsing.h"

ssize_t load_binary(char *path, void **mapped_victim)
{
    int fd = -1;
    int retval = 0;
    struct stat victim_stats;
    size_t victim_size = -1;

    fd = open(path, O_RDWR);
    if (fd == -1){ perror("failed to open victim binary"); retval = -1; goto cleanup; }

    /* Get victim stats */
    memset(&victim_stats, 0, sizeof(struct stat));    
    retval = lstat(path, &victim_stats);
    if (retval == -1){ perror("failed to get victim stats"); retval = -1; goto cleanup; }

    /*
     * Map victim binary into memory
     * Use MAP_SHARED to propagate changes to disk
     */
    victim_size = victim_stats.st_size;
    *mapped_victim = mmap(NULL, victim_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_victim == MAP_FAILED){ perror("Failed to map victim"); retval = -1; goto cleanup; }

    retval = victim_size;
cleanup:
    return retval;
}