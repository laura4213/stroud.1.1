/*
 * Author: Laura Stroud
 * Date: 1/24/2022
 *
 * References:
 *	Perror: 
	https://man7.org/linux/man-pages/man3/perror.3.html

	Getopt:
	https://www.tutorialspoint.com/getopt-function-in-c-to-parse-command-line-arguments
	https://stackoverflow.com/questions/19604413/getopt-optional-arguments


	How to do ssh key with git:
	https://linuxkamarada.com/en/2019/07/14/using-git-with-ssh-keys/#.Ye72durMI2w

	Makefile:
	https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

	Read each character
	https://www.codevscolor.com/c-program-read-file-contents-character
	https://stackoverflow.com/questions/38621938/using-fgetc-for-reading-into-an-array-in-c


	Push to github
	https://www.datacamp.com/community/tutorials/git-push-pull

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

	//All for reading the characters/ putting into mybuf
        int n = 0;
        char string[200];
        char *delim = " \n";
        char *word;
        char line[200];
        int length;
        int y;
	char ch;

	//command line argument
	int opt;

	while((opt = getopt(argc, argv, ":hp:c:s:i:f:")) != -1){
		switch(opt){
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
				perror("Chain: Error in switch: ");
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

		fprintf(stderr, "i:%d process ", i);
		fprintf(stderr, "process ID:%ld ", (long)getpid());
		fprintf(stderr, "parent ID:%ld \n ", (long)getppid());
		//fprintf(stderr, "child ID:%ld \n", (long)childpid);
	 //END OF FOR LOOP

	
		//open file
        	file = fopen(filename, "r");
        	if(file == NULL){
                perror("Error opening file: ");
        	}
		//initalize array
		char *mybuf = malloc(sizeof *mybuf *  nchars);
		
		/* For splitting up the file I first seperated into words then into each character. I referenced one of my old projects from 4280 to help with this part */
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

		printf("%ld: %s \n\n", (long)getpid(), mybuf);

		

		fclose(file);
		free(mybuf);//free memory
	}///////
        return 0;
}



















