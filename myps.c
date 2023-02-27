// Adam Ra
// Purpose : A parser to read into the /proc filesystem
// Lab 01

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// void parseFile(char *optarg);

int opt, unused, ppid, pgrp, session, tty_nr;
unsigned long long utime;
char filename[1000];
char comm[1000];
char state;

int main(int argc, char *argv[])
{
    
    if (argc == 1){
        // printf("No parameters\n");
        // To get current PID for program
        pid_t curr_pid = getpid();
        sprintf(filename,"/proc/%d/stat",curr_pid);
        FILE *f = fopen(filename, "r");
        fscanf(f, "%d %s %c %d %d %d %d", &unused, comm, &state, &ppid, &pgrp, &session, &tty_nr);
        fclose(f);

        FILE *self = fopen("/proc/self/stat", "r");
        if (fscanf(self, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %llu", &utime) == 1)
            printf("My utime is: %llu\n", utime);
        fclose(self);

        printf("PID:    %d | ", curr_pid);
        printf("utime:  %llu |\n", utime);

    }

	while((opt = getopt(argc, argv, "p:sUSvc")) != -1)
	{
		switch(opt)
		{
			case 'p':
                // parseFile(optarg)
                // Accessing the file location and reading through it
                sprintf(filename,"/proc/%s/stat",optarg);
                FILE *f = fopen(filename, "r");
                fscanf(f, "%d %s %c %d %d %d %d", &unused, comm, &state, &ppid, &pgrp, &session, &tty_nr);
                fclose(f);


                printf("pid = %s\n",optarg);
                printf("comm = %s\n", comm);
                printf("state = %c\n", state);
                printf("parent pid = %d\n", ppid);
                printf("pgrp = %d\n",pgrp);
                printf("session = %d\n",session); 
                break;
            case 's':
                // parseFile(optarg);
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

	return 0;
}


// void parseFile(char *optarg){
//     if (optarg == NULL){
//         // sprintf(filename,"/proc/1/stat");
//         // FILE *f = fopen(filename, "r");
//         // fscanf(f, "%d %s %c %d %d %d %d", &unused, comm, &state, &ppid, &pgrp, &session, &tty_nr);
//         // fclose(f);
//         printf("Hello\n");
//     }
//     else{
//         sprintf(filename,"/proc/%s/stat",optarg);
//         FILE *f = fopen(filename, "r");
//         fscanf(f, "%d %s %c %d %d %d %d", &unused, comm, &state, &ppid, &pgrp, &session, &tty_nr);
//         fclose(f);
//     }
// }