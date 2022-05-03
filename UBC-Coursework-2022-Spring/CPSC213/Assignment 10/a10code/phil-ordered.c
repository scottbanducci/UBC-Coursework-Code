#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define MAX_THINKING_TIME 25000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
#endif

typedef struct fork {
  uthread_mutex_t lock;
  uthread_cond_t forfree;
  long free;
} fork_t;

int num_phils, num_meals;    
fork_t *forks;

void deep_thoughts() {
  usleep(random() % MAX_THINKING_TIME);
}

void initfork(int i) {
  forks[i].lock    = uthread_mutex_create();
  forks[i].forfree = uthread_cond_create(forks[i].lock);
  forks[i].free    = 1;
}

long getfork(long i) {
  /* TO BE IMPLEMENTED BY THE STUDENTS. */
  uthread_mutex_lock (forks[i].lock);

  if (forks[i].free = 0){
    uthread_mutex_unlock(forks[i].lock);
    return 0;
  }
  
  forks[i].free = 0;
  uthread_mutex_unlock(forks[i].lock);


  return 1;
}

void putfork(long i) {
  /* TO BE IMPLEMENTED BY THE STUDENTS. */
  uthread_mutex_lock (forks[i].lock);
  forks[i].free = 1;
  uthread_cond_signal(forks[i].forfree);
  uthread_mutex_unlock(forks[i].lock);
}

int leftfork(long i) {
  return i;
}

int rightfork(long i) {
  return (i + 1) % num_phils;
}

void *phil_thread(void *arg) {
  uintptr_t id = (uintptr_t) arg;
  int mealsEaten=0;



  while (mealsEaten < num_meals) {
    /* TO BE IMPLEMENTED BY THE STUDENTS. */
    usleep(random() % MAX_THINKING_TIME);

    int minForkid;
    int maxForkid;
    if (rightfork(id)<leftfork(id)){
        minForkid = rightfork(id);
        maxForkid = leftfork(id);
    }
    else {
        minForkid = leftfork(id);
        maxForkid = rightfork(id);
    }


    int firstFork=getfork(minForkid);
    if (firstFork =0){
        uthread_cond_wait(forks[minForkid].forfree);
        firstFork=getfork(minForkid);
    }
    usleep(random() % MAX_THINKING_TIME);

    int secondFork=getfork(maxForkid);
    if (secondFork =0){
        uthread_cond_wait(forks[maxForkid].forfree);
        secondFork=getfork(maxForkid);
    }
    usleep(random() % MAX_THINKING_TIME);
    mealsEaten++;

    putfork(rightfork(id));
    putfork(leftfork(id));
    usleep(random() % MAX_THINKING_TIME);

  }
  printf("%d\n", mealsEaten);
  return 0;
}

int main(int argc, char **argv) {

  uthread_t *p;
  uintptr_t i;
  
  if (argc != 3) {
    fprintf(stderr, "Usage: %s num_philosophers num_meals\n", argv[0]);
    return 1;
  }

  num_phils = strtol(argv[1], 0, 0);
  num_meals = strtol(argv[2], 0, 0);
  
  forks = malloc(num_phils * sizeof(fork_t));
  p = malloc(num_phils * sizeof(pthread_t));

  uthread_init(num_phils);
  
  srandom(time(0));
  for (i = 0; i < num_phils; ++i) {
    initfork(i);
  }

  /* TODO: Create num_phils threads, all calling phil_thread with a
   * different ID, and join all threads.
   */

  uintptr_t j;

  for (j = 0; j<num_phils; ++j){
      p[j] = uthread_create(phil_thread, j);
  }

  uintptr_t k;
  for (k=0; k<num_phils; ++k){
    uthread_join(p[k],NULL);
  }

  
  return 0;
}
