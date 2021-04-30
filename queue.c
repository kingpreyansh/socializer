#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 1024

/////////////////QUEUE CODE///////////////////////
typedef struct Queue{
	//A FIFI queue of integers
	int contents[MAX_SIZE];
	int size;
}Queue;

void initialize_queue(Queue *my_queue){
	//set up a new queue
	//(must be called on all newly created queues)
	my_queue->size = 0;
}

void enqueue(Queue *my_queue, int new_data){
	//add new_data to the end of the queue
	my_queue->contents[my_queue->size] = new_data;
	my_queue->size += 1;
}

int dequeue(Queue *my_queue){
	//remove and return the first item in the queue
	int ret_item = my_queue->contents[0];
	for(int i = 0; i < (my_queue->size -1); i++){
		my_queue->contents[i] = my_queue->contents[i + 1];
	}
	my_queue->size -= 1;
	return ret_item;
}

bool is_queue_empty(Queue *my_queue){
	//return true iff the queue is empty
	return my_queue->size == 0;
}
int main(){

	///////CODE BELOW THIS LINE SHOULD NOT
	///////NEED TO CHANGE TO ACCOMMODATE CHANGES TO STACK/QUEUE
	
	//create a queue 
	Queue my_queue;
	initialize_queue(&my_queue);
	//add some items
	enqueue(&my_queue, 1);
	enqueue(&my_queue, 2);
	enqueue(&my_queue, 3);
	//print until the queue is empty
	while(!is_queue_empty(&my_queue)){
		printf("%d\n",dequeue(&my_queue));
	}
}