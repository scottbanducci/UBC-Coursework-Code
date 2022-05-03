#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include <assert.h>
#include "uthread.h"
#include "queue.h"
#include "disk.h"

queue_t pending_read_queue;

void interrupt_service_routine() {
  // TODO
  void* val;
  void (*callback)(void*,void*);
  void* trigger;
  queue_dequeue (pending_read_queue, &val, &trigger, &callback);
  callback (val, trigger);
}

void handleOtherReads(void *resultv, void *countv) {
  // TODO
    *((int*) resultv) =  *((int*) resultv);

  *((int*) countv) = 1; //set trigger to 1
}

void handleFirstRead(void *resultv, void *countv) {
  // TODO
  *((int*) resultv) =  *((int*) resultv);
  *((int*) countv) = 1; //set trigger to 1
}

int main(int argc, char **argv) {
  // Command Line Arguments
  static char* usage = "usage: treasureHunt starting_block_number";
  int starting_block_number;
  char *endptr;
  if (argc == 2)
    starting_block_number = strtol (argv [1], &endptr, 10);
  if (argc != 2 || *endptr != 0) {
    printf ("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init (1);
  disk_start (interrupt_service_routine);
  pending_read_queue = queue_create();


  // Start the Hunt
  // TODO
  int firstNum;
  int finalAnswer;
  int trigger =0;

  disk_schedule_read(&firstNum, starting_block_number);
  queue_enqueue(pending_read_queue,&firstNum, &trigger, handleFirstRead);

while(trigger==0){};

int result[firstNum+1];
result[0] = firstNum;

for (int i = 1; i <= firstNum; i++){
  trigger =0;
  disk_schedule_read(&result[i], result[i-1]);
  queue_enqueue(pending_read_queue,&result[i], &trigger, handleOtherReads);
  while (trigger == 0){};
}

  while (trigger == 0){};
printf("%d\n",result[firstNum]);

exit(EXIT_SUCCESS);



  while (1); // infinite loop so that main doesn't return before hunt completes
}
