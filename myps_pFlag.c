// Adam Ra
// Purpose : A separate C file that is a function for flags with -p
// Also checks for other boolean values to print corresponding output
// Lab 01

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include "myps.h"

/* 
    This function returns a 0 and prints output if all is well, 
    otherwise it returns a 1

    Takes in the specific PID via optarg, and the 5 remaining flag booleans

    With the PID given, can go into all the required /proc files to obtain the
    information needed to parse

    Depending on the flag booleans, will print out corresponding output
*/
int pFlag(char *optarg, bool s, bool U, bool S, bool v, bool c){
    int pid, count, mem;
    unsigned long utime, stime;
    char cmd_path[4096];
    char statm_path[4096];
    char cmd_line[4096];
    char stat_path[4096];
    char state;
    size_t len;
    count = 0;

    // Read contents of /proc/<PID>/stat file
    snprintf(stat_path, sizeof(stat_path), "/proc/%s/stat", optarg);
    FILE* stat_file = fopen(stat_path, "r");

    // Error checks, if there is one just iterate to next loop
    if (stat_file == NULL)
        return 1;

    // Parsing fields from the stat file
    fscanf(stat_file, "%d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu", &pid, &state, &utime, &stime);

    // Reading contents of /proc/<PID>/cmdline file
    snprintf(cmd_path, sizeof(cmd_path), "/proc/%s/cmdline", optarg);
    FILE* cmd_file = fopen(cmd_path, "r");
    if (cmd_file == NULL)
        return 1;

    // Looping through the cmdline arguments and replacing each null byte to a new line
    len = strlen(cmd_line);
    for(size_t i = 0; i <len; i++){
        if (cmd_line[i] == '\0')
            cmd_line[i] = '\n';
    }

    // Error checking and also retrieving the information needed
    if (fgets(cmd_line, sizeof(cmd_line), cmd_file) == NULL)
        ;

    // Reading into contents of /proc/<PID>/statm file
    snprintf(statm_path, sizeof(statm_path), "/proc/%s/statm", optarg);
    FILE* statm_file = fopen(statm_path, "r");
    if (statm_file == NULL)
        return 1;

    // Retrieving the virtual memory and storing it
    fscanf(statm_file, "%d", &mem);

    // fclose() cleans up all resources from fopen(), so no need to utilize free()
    fclose(statm_file);
    fclose(stat_file);
    fclose(cmd_file);


    /* 
        The rest below are just string formatted outputs depending
        on the boolean values paired up with -p
    */


    // -p
    if (!s && !U && !S && !v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | UTIME:    %lu\n",pid, utime);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -s
    else if (s && !U && !S && !v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | Process State: %c | UTIME:    %lu\n",pid, state, utime);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -s && -U
    else if (s && U && !S && !v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | Process State: %c\n",pid, state);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -s && -U && -S
    else if (s && U && S && !v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | Process State: %c | STIME:    %lu\n",pid, state, stime);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -s && -U && -S && -v
    else if (s && U && S && v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | Process State: %c | STIME:    %lu | virtual mem:    %d\n",pid, state, stime,mem);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -s && -U && -S && -v && -c
    else if (s && U && S && v && c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | Process State: %c | STIME:    %lu | virtual mem:    %d\n",pid, state, stime, mem);
        if (strcmp(cmd_line,"") == 0)
            return 1;
    }
    // -p && -U
    else if (!s && U && !S && !v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d\n",pid);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -U && -S
    else if (!s && U && S && !v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | STIME:    %lu\n",pid,stime);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -U && -S && -v
    else if (!s && U && S && v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | STIME:    %lu | virtual mem:    %d\n",pid,stime,mem);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -U && -S && -v && -c
    else if (!s && U && S && v && c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | STIME:    %lu | virtual mem:    %d\n",pid,stime,mem);
        if (strcmp(cmd_line,"") == 0)
            return 1;
    }
    // -p && -S
    else if (!s && !U && S && !v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | UTIME:    %lu | STIME:    %lu\n",pid,utime,stime);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -S && -v
    else if (!s && !U && S && v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | UTIME:    %lu | STIME:    %lu | virtual mem:    %d\n",pid,utime,stime,mem);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -S && -v && -c
    else if (!s && !U && S && v && c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | UTIME:    %lu | STIME:    %lu | virtual mem:    %d\n",pid,utime,stime,mem);
        if (strcmp(cmd_line,"") == 0)
            return 1;
    }
    // -p && -v
    else if (!s && !U && !S && v && !c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | UTIME:    %lu | virtual mem:    %d\n",pid,utime,mem);
        if (strcmp(cmd_line,"") == 0)
            return 1;
        else{
            printf("Command Line Arguments:\n\n");
            printf("        [  %d] %s\n", count, cmd_line);
            count++;
        }
    }
    // -p && -v && -c
    else if (!s && !U && !S && v && c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | UTIME:    %lu | virtual mem:    %d\n",pid,utime,mem);
        if (strcmp(cmd_line,"") == 0)
            return 1;
    }
    // -p && -c
    else if (!s && !U && !S && !v && c){
        // Printing out stuff and also format checking through if else statements
        printf("PID:    %d | UTIME:    %lu\n",pid,utime);
        if (strcmp(cmd_line,"") == 0)
            return 1;
    }
    return 0;
}
    