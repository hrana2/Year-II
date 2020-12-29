//"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2

//create three global variables 
//create three p_thread variables t1, t2, t3

//pthread_create(&t1, NULL, run_thread(), ____ this is something that will be passed into run_thread)
//do this for all three p_thread variables 


//run_thread(void* path) {
//fopen(__ path)
//pthread_mutez_lock(__ mutex)
//	item1_counter++
//pthread_mutex_unlock(__mutex)
//pthread_exit()
//	
//}


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>



//The creation of three global variables item_counters, pthread_t, and pthread_mutex_t, respectively 
//The item_counter keeps track of the total of each based on the given files


int item1_counter = 0, item2_counter = 0, item3_counter = 0; 
pthread_t thread1, thread2, thread3; 
pthread_mutex_t lock1, lock2, lock3; 



void *cs392_thread_run(void* arg) {
	//creation of a file pointer with the "r" description because all we need 
	//to do is read the three files 
	FILE *fp = fopen((char*)arg, "r"); 
	if(fp == NULL){
		printf("cannot open file%d\n", errno);
	}
	//created a buffer array with size 256 just in case to handle large characters
	char buff_arr[256]; 
	//using a while loop that loops through the whole file 
	//and stopping when it reaches a null byte signifying an EOF
	while(fgets(buff_arr, sizeof(buff_arr), fp) != '\0') {
		//checking the 5th index because that gives the detail of which 
		//item_counter to adjust and we lock this thread
		if(buff_arr[5] == '1'){
			pthread_mutex_lock(&lock1); 
			//checking the 0 index to see whether or not to add or 
			//subtract from the counter
			if(buff_arr[0] == '+') {
				item1_counter++; 
			}
			else if(buff_arr[0] == '-') {
				item1_counter--; 
			}
			pthread_mutex_unlock(&lock1); 
		}
		//checking the 5th index because that gives the detail of which 
		//item_counter to adjust and we lock this thread
		else if(buff_arr[5] == '2') {
			pthread_mutex_unlock(&lock2); 
			//checking the 0 index to see whether or not to add or 
			//subtract from the counter
			if(buff_arr[0] == '+') {
				item2_counter++; 
			}
			else if(buff_arr[0] == '-') {
				item2_counter--; 
			}
			pthread_mutex_unlock(&lock2);

		}
		//checking the 5th index because that gives the detail of which 
		//item_counter to adjust and we lock this thread
		else if(buff_arr[5] == '3') {
			pthread_mutex_unlock(&lock3); 
			//checking the 0 index to see whether or not to add or 
			//subtract from the counter
			if(buff_arr[0] == '+') {
				item3_counter++; 
			}
			else if(buff_arr[0] == '-') {
				item3_counter--; 
			}
			pthread_mutex_unlock(&lock3);
		}
	}
	//properly close file
	fclose(fp); 

	return NULL; 
}


int main(int argc, char** argv) {
	//checking to see if the user has inputting four arguements
	//if not an error message will be displayed 
	if(argc != 4) {
		perror("wrong number of arguments."); 
	}

	if(pthread_mutex_init(&lock1, NULL) != 0) {
		perror("cannot create mutex 1");

	}
	if(pthread_mutex_init(&lock2, NULL) != 0) {
		perror("cannot create mutex 2");

	}
	if(pthread_mutex_init(&lock3, NULL) != 0) {
		perror("cannot create mutex 3");

	}
	//creating and starting three new threads in the process
	if(pthread_create(&thread1, NULL, cs392_thread_run, argv[1]) != 0) {
		perror("cannot create thread 1.\n");

	}
	if(pthread_create(&thread2, NULL, cs392_thread_run, argv[2]) != 0) {
		perror("cannot create thread 2.\n");

	}
	if(pthread_create(&thread3, NULL, cs392_thread_run, argv[3]) != 0) {
		perror("cannot create thread 3.\n");
	
	}

	//these functions wait for the thread to terminate 
	//since the return value is NULL the function does not copy the exit 
	//status of the target thread.
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	pthread_mutex_destroy(&lock3);

	printf("Final scores - item1_counter: %d, item2_counter: %d, item3_counter: %d\n", item1_counter, item2_counter, item3_counter);
	//exiting out of each child thread
	pthread_exit(NULL); 
	return 0; 

}