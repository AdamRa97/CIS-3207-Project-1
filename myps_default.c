#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include "myps.h"

int opt, pid, uid, seconds, count;
unsigned long utime;
char filename[1000];
char status_path[1000];
char cmd_path[1000];
char cmd_line[1000];
char stat_path[1000];
char line[1000];
char state;
size_t len;

int defFlag(bool s, bool U, bool S, bool v, bool c){
    // To enter the '/proc' file
    DIR* dir = opendir("/proc");
    if (dir == NULL){
        perror("opendir");
        return 1;
    }

    struct dirent* entry;
    struct stat statStruct;
    while ((entry = readdir(dir)) != NULL){
        char* name = entry->d_name;
        // If it's not a PID directory then skip it
        if (name[0] < '0' || name[0] > '9')
            continue;

        // Read contents of /proc/<PID>/stat file
        snprintf(stat_path, sizeof(stat_path), "/proc/%s/stat", name);
        FILE* stat_file = fopen(stat_path, "r");

        // Error checks, if there is one just iterate to next loop
        if (stat_file == NULL)
            continue;

        if (stat(stat_path, &statStruct) == 1)
            continue;

        if (statStruct.st_uid != uid)
            continue;

        // Parsing fields from the stat file
        fscanf(stat_file, "%d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu", &pid, &state, &utime);


        // Reading contents of /proc/<PID>/cmdline file
        snprintf(cmd_path, sizeof(cmd_path), "/proc/%s/cmdline", name);
        FILE* cmd_file = fopen(cmd_path, "r");
        if (cmd_file == NULL)
            continue;

        // Looping through the cmdline arguments and replacing each null byte to a new line
        len = strlen(cmd_line);
        for(size_t i = 0; i <len; i++){
            if (cmd_line[i] == '\0')
                cmd_line[i] = '\n';
        }

        // Error checking and also retrieving the information needed
        if (fgets(cmd_line, sizeof(cmd_line), cmd_file) == NULL)
            continue;

        // Converting utime into seconds for visualization
        seconds = (int)utime / sysconf(_SC_CLK_TCK);

        fclose(stat_file);
        fclose(cmd_file);

        // Default
        if (!s && !U && !S && !v && !c){
                // Printing out stuff and also format checking through if else statements
                printf("PID:    %d | UTIME:    %d\n",pid, seconds);
                if (strcmp(cmd_line,"") == 0){
                    return 1;
                }
                else{
                    printf("Command Line Arguments:\n\n");
                    printf("        [  %d] %s\n", count, cmd_line);
                    count++;
                }
        }
        // -s
        else if (s && !U && !S && !v && !c){
            // Printing out stuff and also format checking through if else statements
            printf("PID:    %d | Process State: %c | UTIME:    %d\n",pid, state, seconds);
            if (strcmp(cmd_line,"") == 0){
                return 1;
            }
            else{
                printf("Command Line Arguments:\n\n");
                printf("        [  %d] %s\n", count, cmd_line);
                count++;
            }
        }
        // -U
        else if (!s && U && !S && !v && !c){
            // Printing out stuff and also format checking through if else statements
            printf("PID:    %d |\n",pid);
            if (strcmp(cmd_line,"") == 0){
                return 1;
            }
            else{
                printf("Command Line Arguments:\n\n");
                printf("        [  %d] %s\n", count, cmd_line);
                count++;
            }
        }
    }
    closedir(dir);
    return 0;
}