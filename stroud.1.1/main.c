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
#include <string.h>
int main(int argc, char *argv[]){
        pid_t childpid = 0;
        int i;
        int nprocs = 4;
	int sleeptime = 3;
	int niters = 1;
	int nchars = 80;
        FILE *file;
        char *filename;
	int j;
	char ch;

	//command line arguments
	int opt;

	while((opt = getopt(argc, argv, ":hp:c:s:i:f:")) != -1){
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
				nprocs = atoi(optarg);
				break;
			case 'c':// number of characters to read
				nchars = atoi(optarg);
				break;
			case 's'://sleeptime
				sleeptime = atoi(optarg);
				break;
			case 'i':
				niters = atoi(optarg);
				break;
			case 'f'://file name
				filename = optarg;
				break;
			default:
				printf("Usage: ./chain [-h] [-p nprocs] [-c nchars] [-s sleeptime] [-i niters] < textfile\n");
				perror("Error in switch: ");
				break;
			
		}
	}



        for(i = 1; i < nprocs; i++){
                if((childpid = fork()) <= 0){
                        break;
                }
        }

	for(j = 0; j < niters; j++){
		sleep(sleeptime);

		wait(NULL);
        	//fprintf(stderr, "i:%d process ID:%ld parent ID:%ld Child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)childpid);

//		fprintf(stderr, "i:%d process ", i);
//		fprintf(stderr, "process ID:%ld ", (long)getpid());
//		fprintf(stderr, "parent ID:%ld \n ", (long)getppid());
		//fprintf(stderr, "child ID:%ld \n", (long)childpid);
	} //END OF FOR LOOP

	
	//open file
        file = fopen(filename, "r");
        if(file == NULL){
                perror("Error opening file: ");
        }else{
                printf("opened file");
        }
	
	//initalize array
	char *mybuf = malloc(sizeof *mybuf *  nchars);
	int n = 0;
	char string[200];
	char *delim = " \n";
	char *word;
	char line[200];
	int length;
	int y;
		while(fgets(string, sizeof string, file)){ //loop through file
			if(strstr(string, line)){
				//do nothing
			}
			for(word = strtok(string, delim);word;  word = strtok(NULL, delim)){
				length = strlen(word);
				for(y=0; y < length; y++){
					//printf("%c \n ", word[y]);
					mybuf[n] = word[y];
					//printf("%c \n", mybuf[n]);
					n++;
				}
			}
		}
		mybuf[n] = '\0';

		fclose(file);

		int x;
		//print array
		for(x = 0; x < n; x++){
			printf("%c \n", mybuf[x]);
		}

		free(mybuf);//free memory

        return 0;
}



















