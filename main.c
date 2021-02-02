#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

void print_usage()
{
    puts("Usage: ./informant [victim binary]");
}

int main(int argc, char **argv)
{
    int retval = 0;
    int fd = -1;
    size_t victim_size = 0;
    char *victim = NULL;
    void *mapped_victim = NULL;
    struct stat victim_stats;

    /* Appropriate number of arguments? */
    if (argc < 2){ print_usage(); retval = -1; goto cleanup; }
    victim = argv[1];

    fd = open(victim, O_RDWR);
    if (fd == -1){ perror("failed to open victim binary"); retval = -1; goto cleanup; }

    /* Get victim stats */
    memset(&victim_stats, 0, sizeof(struct stat));    
    retval = lstat(victim, &victim_stats);
    if (retval == -1){ perror("failed to get victim stats"); retval = -1; goto cleanup; }

    /*
     * Map victim binary into memory
     * Use MAP_SHARED to propagate changes to disk
     */
    victim_size = victim_stats.st_size;
    mapped_victim = mmap(NULL, victim_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (mapped_victim == MAP_FAILED){ perror("Failed to map victim"); retval = -1; goto cleanup; }

cleanup:
    if (fd > 0) close(fd);
    if (mapped_victim != NULL) munmap(mapped_victim, victim_size);
    return retval;
}