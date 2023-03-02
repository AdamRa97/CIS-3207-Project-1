# Project-1-S23  The /PROC File System 
There are several goals for this assignment.
1.	Continue to familiarize yourself with the C programming language. Dealing with separate compilation is likely to be new to some of you.
2.	Learn how to use some of the I/O facilities and library functions provided by UNIX and C. There are likely to be some new functions that you have not seen yet.
3.	Get experience with some of the system level interfaces provided in Linux. Operating systems have many interesting dark corners, and you will get a chance to peek around one of them.
4.	Get some insights as to how an important Linux utility works.
5.	Learn about the /proc filesystem.
6.	Get more experience with separate compilation, makefiles, and the Linux gdb debugger.

### Tasks
A.	Warmup/Introduction to /proc filesystem. These are short, specific tasks to probe the /proc filesystem.  
•	write a program to report the number of processors and the amount of cache in each CPU.  
•	Write a program to report the free memory in the system and the number of memory buffers 
 
B.	Primary Assignment:  
Your assignment is to write a simple version of the ps command. Your version of ps, called MYps will be executed from a command line. It will read a variety of information about one or more running programs (processes) on the computer, and then display that information. As an example of what your program will do, consider a command such as:  

   **MYps -p 1234 -s -U -c**

This runs your ps command, and displays the status letter (in this case, running), amount of user time, and the command line for process 1234. You might expect the output to look like:  
   **1234: R utime=150 [myprog -x -y file1 myoption]**

### The /proc Filesystem 
The /proc file system provides access to the state of each active process and thread in the system. The /proc file system contains a directory entry for each process running on the Linux system. The name of each directory in the filesystem is the process ID of the corresponding process. These directories appear and disappear dynamically as processes start and terminate on the system. Each directory contains several entries providing access to information about the running process. From these process directories the /proc file system gets its name. 

These entries are subdirectories and the owner of each is determined by the user ID (PID) of the process. Access to the process state is provided by additional files contained within each subdirectory. Except where otherwise specified, the term /proc file is meant to refer to a non-directory file within the file hierarchy rooted at /proc.  

/proc is known as a “pseudo-filesystem”, which means it is not a true filesystem that is consuming disk storage. The files and directories in /proc are entry points into kernel tables, such as the open file table or the process table.  

Some of the directories in the /proc filesystem are:  

| directory		| 	description   |  
| ------------- | ------------------- |
| /proc/PID/cmdline	| 	Command line arguments |  
| /proc/PID/cpu	|	Current and last cpu in which it was executed|
| /proc/PID/cwd	|	Link to the current working directory |  
| /proc/PID/environ	 |	Values of environment variables |
| /proc/PID/exe	|	Link to the executable of this process | 
| /proc/PID/fd		| 	Directory, which contains all file descriptors | 
| /proc/PID/maps	|	Memory maps to executables and library files |
| /proc/PID/mem	 |	Memory held by this process |
| /proc/PID/root	|	Link to the root directory of this process | 
| /proc/PID/stat	|	Process status | 
| /proc/PID/statm	|	Process memory status information | 
| /proc/PID/status	|	Process status in human readable form | 

### Project Features 
Your program will implement the features triggered by the following options for the ps command. 

|  &nbsp;&nbsp;     OPTION &nbsp;&nbsp;		| 	DESCRIPTION   |  
| ------------- | ------------------- |
| -p  \<pid\>| Display process information only for the process whose number is pid. It does not matter if the specified process is owned by the current user. If this option is not present, then display information for all processes of the current user (and only of the current user). You only need to support a single -p option.  |  	
| -s | Display the single-character state information about the process. This information is found in the stat file in the process’s directory, by looking at the third (“state”) field. Note that the information that you read from the stat file is a character string.  |
| -U | DO NOT Display the amount of user time consumed by this process. This information is found in the stat file in the process’s directory, by looking at the “utime” field. If this option is not present, then user time information is displayed.  |
| -S | Display the amount of system time consumed so far by this process. This information is found in the stat file in the process’s directory, by looking at the “stime” field.  |
| -v | Display the amount of virtual memory currently used (in pages) by this program. This information is found in the statm file in the process’s directory, by looking at the  first (“size”) field.  |
| -c | DO NOT Display the command-line that started this program. This information is found in the  cmdline file in the process’s directory. Be careful with this one, because this file contains a list of null (zero byte) terminated strings. If this option is not present, then command line information is displayed.  |

The output of MYps is a display of the information, similar to that of the output of ps.  

### Deliverables:  
Week 1 (MISSED):   
* Investigate /proc file system  
* Design and implementation of parsers to extract from the various /proc files  
* Parsing the command line  
====================================================================================
### Research on /proc file system (Week 1)
* man pages are amazing and very helpful in finding information related to the fields
* stat, statm, and status are all very important /proc files that need to be parsed

### Design and Implement Parsers for /proc files (Week 1)
* probably will just go through all the necessary /proc files and take all the information needed
* possibly need dynamic programming / interpolation
* maybe a struct can be used for all the properties

### Parsing command line (Week 1)
* use argv[] to parse through the command line
* getopt() is great
====================================================================================

Week 2 (MISSED):  
* Code to process and display the /proc/cpuinfo and /proc/meminfo files  
* Makefile as defined in the project	
* Code to get the process list  
====================================================================================
### Process (Week 2)

### Design Reasons (Week 2)

### Testing and Struggles (Week 2)

====================================================================================

Week 3(ON TIME):  
* Implementation of the specified options  
* Design and implementation of the display formats  
* Complete documentation of code and testing

====================================================================================
### Implementation (Week 3)
* Used a switch case with getopt() in the "myps.c"(The main file)
   * This checks for the flags given as well as none
   * Depending on which flags are given, set a boolean variable corresponding to that flag as "True" otherwise false;
* There are 2 .c files that are considered "Helper" files "myps_pFlag.c" and "myps_default.c"
   * These are combined into "myps.c" with "myps.h" a custom made header file
   * These 2 files take care of all the possible combination of flags via "if-else" statements

### Design of display format (Week 3)
* Decided to print out via "hard code" depending on the booleans given
   * I know it's not efficient and ugly / bad code but it works
* I know a way to string format with f-strings in Python with interpolation but C doesn't have the same functionality (from what I know)
* Tried replicating the same display format as seen in powerpoint slides
* If the display format was just a single line divided up by "|", can most likely dynamically program the display with interpolation

### Testing and Struggles (Week 3)
* Tested a lot via "printf" in intervals to track steps
* Using local / global variables to test what works better
* Tested to see if all combinations would work
   * Need to enter in flags in correct order or program doesn't work
* Printed out boolean values at specific intervals to make sure they were working as intended
* Struggled on how to figure out what needed to be compared or matched in terms of UID / PID (friends and Parth helped explained this to me)
* Tried utilizing a function at first and made it within the same "myps.c" file but realized there were better options (utilizing custom .h files and functions)
*Utilized a lot of the makefile commands to test
*Decided to setup SSH and GitHub for VSCode for more convenience in testing and git updates
====================================================================================