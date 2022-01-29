/*
 * Author: Laura Stroud
 * Date: 1/24/2022
 *
 * References:
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]){
        pid_t childpid = 0;
        int i, nprocs, sleeptime, niters, nchars;
	
        if(argc < 2){//checks for valid number
                fprintf(stderr, "Usage: %s processes \n, argv[0]");
                return 1;
        }

        nprocs = atoi(argv[1]);
        for(i = 1; i < nprocs; i++){
                if((childpid = fork()) <= 0){
                        break;
                }
        }

	//sleeptime default is three unless stated otherwise
	if(argc > 2){
		sleeptime = atoi(argv[2]);
	}else{
		sleeptime = 3;
	}
	
	//declare the number of iterations
	niters = atoi(argv[3]);
	int j;
	for(j = 0; i < niters; i++){
		sleep(sleeptime);
        	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld Child ID:%ld\n",
                        i, (long)getpid(), (long)getppid(), (long)childpid);
	}

        return 0;
}

