#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int opt;
	
	while((opt = getopt(argc, argv, "psUSvc")) != -1)
	{
		switch(opt)
		{
			case 'p':
                printf("p\n");
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
