//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 

#include "cs392_exec.h"

int numberofWords;

//This function will parse the command line and take each 
//command that the user will supply and separate them so that 
//they can be logged in the future. 
char** eachWord(char* str){
    numberofWords = 1;
    //this for loop will loop through each of the letters in a word. 
    //when there is a space that means that the word has finished so the 
    //counter will increment. The for loop will stop at the null byte. 
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == ' '){
            ++numberofWords;
        }
    }
    //creating a char array and mallocing enough 
    //space to deal with the longest possible word
    char** wordArr = malloc(256 * sizeof(char*));
    //this for loop is inserting each word into the array 
    for(int i = 0; i < numberofWords; i++) {
        wordArr[i] = malloc(sizeof(char) * numberofWords);
    }

    //This is breaking the str into tokens with the deliminter being 
    //and empty space to signify the end of a word. 
    char* commandWord = strtok(str, " ");
    int position = 0;
    //while the word is not NULL we are copying the tokens into the 
    //specific position in the array and incrementing the index. 
    while(commandWord != NULL){
        strcpy(wordArr[position], commandWord);
        commandWord = strtok(NULL, " ");
        position = position + 1; 
    }
    wordArr[position] = NULL;
    
    return wordArr;
}

void execCommand(char* str) {
	char** diff_words = eachWord(str);
    int pid; 

    //We are comparing two strings to see if they are both the exit 
    //command. If this is true then we exit the shell and return to the 
    //normal command line. 
    if(strcmp(diff_words[0], "exit") == 0) { 

    	printf("Now exiting shell.\n");
    	for(int i = 0; i < numberofWords; i++) { 
    		free(diff_words[i]); 
    	}
    	free(diff_words); 
    	exit(0); 

    //The free funciton displays the total amount of unused memory
    //in the system. 
    } else {
    	if((pid = fork()) < 0 ) {
    		printf("There was an error while forking.  \n"); 
    		for(int i = 0; i < numberofWords; i++) {
    			free(diff_words[i]); 
    		}
    		free(diff_words); 
    		exit(1); 
    		//The parent function will now wait for the termination of the 
    		//child process before executing. This will eleimate any zombie processes.
    	} else if(pid > 0) {
    		wait(NULL); 
    	} else {
    		int childsWork; 
    		//The execvp will replace the current process image with a new one. 
    		if((childsWork = execvp(diff_words[0], diff_words)) < 0) {
    			printf("%s: the command could not be found.\n", diff_words[0]);
    			for(int i = 0; i < numberofWords; i++) {
    				free(diff_words[i]);
    			}
    			free(diff_words); 
    			exit(1); 
    		}
    	}
    }
    //freeing each word in the array and then freeing the array as a whole.
    for(int i = 0; i < numberofWords; i++) {
    	free(diff_words[i]); 
    }
    free(diff_words); 


    
}