// Adam Ra
// Purpose : A parser to read into the /proc filesystem
// Lab 01

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int opt, unused, ppid;
    char filename[1000];
    char comm[1000];
    char state;
    
    if (argc == 1)
        printf("No parameters\n");

	while((opt = getopt(argc, argv, "p:sUSvc")) != -1)
	{
		switch(opt)
		{
			case 'p':
                printf("pid = %s\n",optarg);
                sprintf(filename,"/proc/%s/stat",optarg);
                FILE *f = fopen(filename, "r");
                fscanf(f, "%d %s %c %d", &unused, comm, &state, &ppid);
                printf("comm = %s\n", comm);
                printf("state = %c\n", state);
                printf("parent pid = %d\n", ppid);
                fclose(f);
                break;
            case 's':
                printf("s\n");
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
