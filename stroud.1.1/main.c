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
#include <sys/wait.h>

int main(int argc, char *argv[]){
        pid_t childpid = 0;
        int i;
        int nprocs = 4;
	int sleeptime = 3;
	int niters = 1;
	int nchars = 80;
	
	//command line arguments
	int opt;

	while((opt = getopt(argc, argv, ":hp:c:s:i:")) != -1){
		switch(opt){
printf("%d nprocs\n", nprocs);
                                printf("%d sleeptime\n", sleeptime);
                                printf("%d nchars\n", nchars);
			case 'h':
				printf("./chain [-h] [-p nprocs] [-s sleeptime] [-i niters] < textfile\n\n");
				printf("-p nprocs: number of processes\n");
				printf("-c nchars: number of characters read into the buffer\n");
				printf("-s sleeptime: time to sleep in each iteration\n");
				printf("-i niters: number of iterations in loop\n");
				printf("textfile: file to be used\n");
				break;

			case 'p'://number of procceses
				printf("in switch p\n");
				nprocs = atoi(optarg);

				printf("%d nprocs\n", nprocs);
				printf("%d sleeptime\n", sleeptime);
				printf("%d nchars\n", nchars);
				break;
			case 'c':// number of characters to read
				nchars = atoi(optarg);

				printf("%d nprocs\n", nprocs);
                                printf("%d sleeptime\n", sleeptime);
                                printf("%d nchars\n", nchars);
				break;
			case 's'://sleeptime
				sleeptime = atoi(optarg);

				printf("%d nprocs\n", nprocs);
                                printf("%d sleeptime\n", sleeptime);
                                printf("%d nchars\n", nchars);
				printf("%d niters\n", niters);
				break;
			case 'i':
				niters = atoi(optarg);
				break;
			default:
				printf("Usage: ./chain [-h] [-p nprocs] [-c nchars] [-s sleeptime] [-i niters] < textfile");
				perror("Error in switch: ");
				break;
			
		}
	}
        
	printf("out of while loop");

        for(i = 1; i < nprocs; i++){
		printf("in 1st for loop\n");
                if((childpid = fork()) <= 0){
                        break;
                }
        }
	
	int j;
	for(j = 0; j < niters; j++){
		printf("in second for\n");
		sleep(sleeptime);

		wait(NULL);
        //	fprintf(stderr, "i:%d process ID:%ld parent ID:%ld Child ID:%ld\n",
          //              i, (long)getpid(), (long)getppid(), (long)childpid);

		fprintf(stderr, "i:%d process ", i);
		fprintf(stderr, "process ID:%ld ", (long)getpid());
		fprintf(stderr, "parent ID:%ld \n ", (long)getppid());
		//fprintf(stderr, "child ID:%ld \n", (long)childpid);
		
		
		//loop that reads each character putting it into an array
	
	}

        return 0;
}



















