// Adam Ra
// Purpose : A parser to read into the /proc filesystem
// Lab 01

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include "myps.h"
/*
    myps.c is the main program that is linked together via
    the "myps.h" header file

    this program is to replicate a simple version
    from the linux cli "ps"

    utilizes the getopt() function to read through
    the flags given through the CLI

    Switch Case is used depending on which flags
    are given.

    Utilizing a boolean system to feed through the 2
    different helper files ("myps_pFlag.c" && "myps_default.c")

*/
int main(int argc, char *argv[]){
    int opt;
    char pid[1024];
    bool p_bool = false;
    bool s_bool = false;
    bool U_bool = false;
    bool S_bool = false;
    bool v_bool = false;
    bool c_bool = false;

    // Going through the flags given via case switches
	while((opt = getopt(argc, argv, "p:sUSvc")) != -1)
	{
		switch(opt)
		{
			case 'p':
                sprintf(pid, "%s",optarg);
                p_bool = true;
                break;
            case 's':
                s_bool = true;
                break;
            case 'U':
                U_bool = true;
                break;
            case 'S':
                S_bool = true;
                break;
            case 'v':
                v_bool = true;
                break;
            case 'c':
                c_bool = true;
                break;
            default:
                fprintf(stderr,"Usage: %s", argv[0]);
                exit(EXIT_FAILURE);
		}
	}

    
    // If there is no p flag
    if (!p_bool)
        defFlag(s_bool,U_bool,S_bool,v_bool,c_bool);
    // If there is a p flag
    else if (p_bool)
        pFlag(pid,s_bool,U_bool,S_bool,v_bool,c_bool);

	return 0;
}