// Adam Ra
// Purpose : Reporting the free memory in the system and number of memory buffers
// Lab 01 Warm Up

#include <stdio.h>
#include <string.h>

/*
    This is a program that is designed to show how the amount of free memory in the system
    and the number of buffers within the /proc/meminfo

    Same technique is used as in Week 3 deliverables to go inside the file / directory
*/
int main(void) {
    int mem = 0;
    int buff = 0;
    char line[1024];

    // Opening up the file and checking for errors
    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL)
        return -1;

    // While there are lines of content go through the loop
    while (fgets(line, sizeof(line), meminfo) != NULL) {
        // Check for processor
        if (sscanf(line, "MemFree : %d", &mem) == 1)
            continue;
        // Check for cache size
        else if (sscanf(line, "Buffers : %d", &buff) == 1)
            continue;
    }

    printf("Avilable Free Memory: %d kB\n", mem);
    printf("Buffers: %d kB\n",buff);

    fclose(meminfo);
    return 0;
}