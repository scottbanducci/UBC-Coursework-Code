#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/errno.h>
#include <assert.h>
#include "queue.h"
#include "disk.h"
#include "uthread.h"

queue_t pending_read_queue;
unsigned int sum = 0;
int counter = 0;

void interrupt_service_routine()
{
  // TODO

  void *val;
  void (*callback)(void *, void *);
  uthread_t *currThread;
  queue_dequeue(pending_read_queue, &val, &currThread, &callback);
  callback(val, NULL);
  uthread_unblock(*currThread);

}

void handle_read(void *resultv, void *not_used)
{
  sum = sum + *((int *)resultv);

}

void *read_block(void *blocknov)
{
  // TODO schedule read and the update (correctly)
  disk_schedule_read(blocknov, counter);
  counter++;
  uthread_block();
  return NULL;
}

int main(int argc, char **argv)
{

  // Command Line Arguments
  static char *usage = "usage: tRead num_blocks";
  int num_blocks;
  char *endptr;
  if (argc == 2)
    num_blocks = strtol(argv[1], &endptr, 10);
  if (argc != 2 || *endptr != 0)
  {
    printf("argument error - %s \n", usage);
    return EXIT_FAILURE;
  }

  // Initialize
  uthread_init(1);
  disk_start(interrupt_service_routine);
  pending_read_queue = queue_create();

  // Sum Blocks
  // TODO
  int result[num_blocks];
  uthread_t threadArr[num_blocks];

  for (int blockno = 0; blockno < num_blocks; blockno++)
  {
    threadArr[blockno] = uthread_create(read_block, &result[blockno]);
    queue_enqueue(pending_read_queue, &result[blockno], &threadArr[blockno], handle_read);
  }


  for (int blockno = 0; blockno < num_blocks; blockno++)
  {
    threadArr[blockno] = uthread_join(threadArr[blockno], 0);
  }
  
  printf("%d\n", sum);
}
