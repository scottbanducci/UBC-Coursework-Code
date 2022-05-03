#include <stdlib.h>
#include <stdio.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

const int N = 100000;
int cnt = 0;
uthread_mutex_t mutex;
uthread_cond_t  upHasGone;
int upFlag;

uthread_t t0, t1, t2;

void countUp() {
  uthread_mutex_lock (mutex);

  for (int i=0; i<N; i++)
    cnt += 1;

  upFlag = 1;
  uthread_cond_signal(upHasGone);
  uthread_mutex_unlock(mutex);

}

void countDown() {
  uthread_mutex_lock (mutex);
  if (upFlag == 0)
    uthread_cond_wait(upHasGone);
  for (int i=0; i<N; i++)
    cnt -= 1;

  upFlag = 0;
  uthread_mutex_unlock(mutex);
}

void* count(void* v) {
  countUp();
  countDown();
  return NULL;
}

int main(int arg, char** arv) {
  mutex = uthread_mutex_create();
  upHasGone = uthread_cond_create (mutex);
  upFlag = 0;

  uthread_init(4);
  t0 = uthread_create(count, NULL);
  t1 = uthread_create(count, NULL);
  t2 = uthread_create(count, NULL);
  uthread_join (t0, NULL);
  uthread_join (t1, NULL);
  uthread_join (t2, NULL);
  printf("cnt = %d %s\n", cnt, cnt==0? "": "XXX");
  uthread_mutex_destroy (mutex);
  uthread_cond_destroy (upHasGone);
}