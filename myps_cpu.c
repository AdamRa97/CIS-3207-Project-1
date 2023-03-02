// Adam Ra
// Purpose : Reporting the number of processors and amount of cache in each CPU
// Lab 01 Warm Up

#include <stdio.h>
#include <string.h>

/*
    This is a program that is designed to show how many processors and how big the cache size is for each processor
    within the /proc/cpuinfo

    Same technique is used as in Week 3 deliverables to go inside the file / directory
*/
int main() {
    int proc = 0;
    int cache = 0;
    char line[1024];

    // Opening up the file
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL)
        return -1;

    // While there are lines of content go through the loop
    while (fgets(line, sizeof(line), cpuinfo) != NULL) {
        // Check for end of CPU section
        if (strcmp(line, "\n") == 0)
            printf("Processor #%d cache size is %d KB\n", proc, cache);
        // Check for processor
        else if (sscanf(line, "processor : %d", &proc) == 1)
            continue;
        // Check for cache size
        else if (sscanf(line, "cache size : %d", &cache) == 1)
            continue;
    }

    fclose(cpuinfo);
    return 0;
}

