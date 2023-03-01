// Adam Ra
// Purpose : A parser to read into the /proc filesystem
// Lab 01

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>

int opt, unused, pid, ppid, pgrp, session, tty_nr, uid;
unsigned long long utime;
char filename[1000];
char comm[1000];
char status_path[1000];
char stat_path[1000];
char line[1000];
char state;

int main(int argc, char *argv[]){
    uid = getuid();

    // To enter the '/proc' file
    DIR* dir = opendir("/proc");
    if (dir == NULL){
        perror("opendir");
        return 1;
    }

    // If there are no flags then just print out everything normally
    if (argc == 1){

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
            if (stat_file == NULL)
                continue;

            if (stat(stat_path, &statStruct) == 1)
                continue;

            if (statStruct.st_uid != uid)
                continue;

            // Parse the first field (the PID) from the stat file
            fscanf(stat_file, "%d %s %c", &pid, comm, &state);
            fclose(stat_file);

            // Open and read contents of /proc/<PID>/status file
            snprintf(status_path, sizeof(status_path), "/proc/%s/status", name);
            FILE* status_file = fopen(status_path, "r");
            if (status_file == NULL)
                continue;
            // fscanf(status_file, "blah blah", test test);
            
            fclose(status_file);

            printf("PID:    %d | ",pid);
            printf("UTIME:  %llu|\n",utime);
        }
    }


    // Going through the flags given via case switches
	while((opt = getopt(argc, argv, "p:sUSvc")) != -1)
	{
		switch(opt)
		{
			case 'p':
                // Accessing the file location and reading through it
                sprintf(filename,"/proc/%s/stat",optarg);
                FILE *f = fopen(filename, "r");
                if (f != NULL)
                    fscanf(f, "%*d %s %c %d %d %d %d", comm, &state, &ppid, &pgrp, &session, &tty_nr);
                fclose(f);

                printf("pid = %s\n",optarg);
                printf("comm = %s\n", comm);
                printf("state = %c\n", state);
                printf("parent pid = %d\n", ppid);
                printf("pgrp = %d\n",pgrp);
                printf("session = %d\n",session); 
                break;
            case 's':
                // printf("state = %c\n", state);
                break;
            case 'U':
                printf("U\n");
                break;
            case 'S':
                printf("S\n");
                break;
            case 'v':
                printf("v\n");
                break;
            case 'c':
                printf("c\n");
                break;
		}
	}

    closedir(dir);
	return 0;
}