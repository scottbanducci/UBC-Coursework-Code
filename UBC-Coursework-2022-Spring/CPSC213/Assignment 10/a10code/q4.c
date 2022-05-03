#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

uthread_t t0, t1, t2;
uthread_mutex_t mutex;
uthread_cond_t  pHasGone;
int pFlag;

void randomStall() {
  int i, r = random() >> 16;
  while (i++<r);
}

void* p0(void* v) {
  uthread_mutex_lock (mutex);

  if (pFlag != 0)
    uthread_cond_wait(pHasGone);

  randomStall();
  printf("zero\n");

  pFlag = 1;
  uthread_cond_signal(pHasGone);
  uthread_mutex_unlock(mutex);

  return NULL;
}

void* p1(void* v) {
  uthread_mutex_lock (mutex);
  
  if (pFlag != 1)
    uthread_cond_wait(pHasGone);

  randomStall();
  printf("one\n");

  pFlag = 2;
  uthread_cond_signal(pHasGone);
  uthread_mutex_unlock(mutex);

  return NULL;
}

void* p2(void* v) {
  uthread_mutex_lock (mutex);
  
  if (pFlag != 2)
    uthread_cond_wait(pHasGone);

  randomStall();
  printf("two\n");

  pFlag = 3;
  uthread_cond_signal(pHasGone);
  uthread_mutex_unlock(mutex);

  return NULL;
}

int main(int arg, char** arv) {
  mutex = uthread_mutex_create();
  pHasGone = uthread_cond_create (mutex);
  pFlag = 0;
  
  uthread_init(4);
  t0 = uthread_create(p0, NULL);
  t1 = uthread_create(p1, NULL);
  t2 = uthread_create(p2, NULL);
  randomStall();
  uthread_join (t0, NULL);
  uthread_join (t1, NULL);
  uthread_join (t2, NULL);
  printf("three\n");
  printf("------\n");

  uthread_mutex_destroy (mutex);
  uthread_cond_destroy (pHasGone);
}

