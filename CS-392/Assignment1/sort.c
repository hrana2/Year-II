/*Author: Himanshu Rana - hrana2*/
/*"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana*/


#include "sort.h"

/*This function compares two adjacent numbers and is used in 
the qsort function.*/
int compare(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
} 

/*This function reads each line of strings and converts then 
into integers. Then it sorts those integers and saves them 
into another file in the form of binary.*/
void convertToBin(FILE	*x, FILE *y) {
	char *z = malloc(11); 
	if(!z) {
		perror("There is a malloc error"); 
		exit(1); 
	}

	/*Counts the number of lines by using the 
	enf-of-file indicator*/
	int num_lines = 0; 
	while(!feof(x)) {
		char space = fgetc(x); 
		if(space == '\n') {
			num_lines = num_lines + 1;  
		}
	}

	int arr[num_lines]; 
	int count = 0; 

	/*Uses atoi to convert each string to an int.*/
	rewind(x); 
	while(fgets(z, 11, x)) {
		int temp = atoi(z); 
		arr[count] = temp; 
		count = count + 1; 
	}

	/*Uses the built in qsort function to sort the integers
	and prints each integer on a seperate line in the output file.*/
	qsort(arr, num_lines, sizeof(int), compare); 
	for(int i = 0; i < num_lines; i++) {
		fprintf(y, "%d", arr[i]);
		fputs("\n", y); 
	}
}

/*This is the main function that handles all the error checking. */
int main(int argc, char** argv) { 
	
	/*Makes sures that there are exactly three arguements in the command line.*/
	if(argc != 3) {
		perror("Error: Invalid number of arguements."); 
		exit(1);
	}

	FILE *x, *y; 
	char *c; 

	x = fopen(argv[1], "r"); 
	y = fopen(argv[2], "wb"); 

	if(x == NULL) {
		perror("The file cannot be opened."); 
		exit(1); 
	}

	if(y == NULL) {
		perror("The file cannot be opened."); 
		exit(1); 
	}

	/*Calls the convertToBin function and then properly 
	closes and cleans up all data that's been opened.*/
	convertToBin(x,y); 
	fclose(x); 
	return 0; 


}
