#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_THREADS 3
uthread_t threads[NUM_THREADS];
uthread_mutex_t mutex;
uthread_cond_t  aHasGone;
int aFlag;

void randomStall() {
  int i, r = random() >> 16;
  while (i++<r);
}

void waitForAllOtherThreads() {
  if (aFlag != NUM_THREADS)
    uthread_cond_wait(aHasGone);
  else 
    uthread_cond_broadcast(aHasGone);

}

void* p(void* v) {
  uthread_mutex_lock (mutex);
  
  randomStall();
  printf("a\n");
    aFlag++;

  waitForAllOtherThreads();
  

  uthread_cond_signal(aHasGone);

  printf("b\n");
  
  uthread_mutex_unlock(mutex);

  return NULL;
}

int main(int arg, char** arv) {
  mutex = uthread_mutex_create();
  aHasGone = uthread_cond_create (mutex);
  aFlag = 0;


  uthread_init(4);
  for (int i=0; i<NUM_THREADS; i++)
    threads[i] = uthread_create(p, NULL);
  for (int i=0; i<NUM_THREADS; i++)
    uthread_join (threads[i], NULL);
  printf("------\n");
  uthread_mutex_destroy (mutex);
  uthread_cond_destroy (aHasGone);
}