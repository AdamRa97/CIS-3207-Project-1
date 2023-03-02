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

int main(int argc, char *argv[]){
    int pid,opt;
    bool p_bool, s_bool, U_bool, S_bool, v_bool, c_bool = false;

    // Going through the flags given via case switches
	while((opt = getopt(argc, argv, "p:sUSvc")) != -1)
	{
		switch(opt)
		{
			case 'p':
                pid = atoi(optarg);
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
    else
        pFlag(pid,s_bool,U_bool,S_bool,v_bool,c_bool);

	return 0;
}