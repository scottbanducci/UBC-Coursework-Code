#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_ITERATIONS 1000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
#endif

int sum = 0;
uthread_cond_t match_Paper;
uthread_cond_t paper_Tobacco;
uthread_cond_t match_Tobacco;


struct Agent {
  uthread_mutex_t mutex;
  uthread_cond_t  match;
  uthread_cond_t  paper;
  uthread_cond_t  tobacco;
  uthread_cond_t  smoke;
};

struct Agent* createAgent() {
  struct Agent* agent = malloc (sizeof (struct Agent));
  agent->mutex   = uthread_mutex_create();
  agent->paper   = uthread_cond_create(agent->mutex);
  agent->match   = uthread_cond_create(agent->mutex);
  agent->tobacco = uthread_cond_create(agent->mutex);
  agent->smoke   = uthread_cond_create(agent->mutex);
  return agent;
}


// TODO
// You will probably need to add some procedures and struct etc.
//

/**
 * You might find these declarations helpful.
 *   Note that Resource enum had values 1, 2 and 4 so you can combine resources;
 *   e.g., having a MATCH and PAPER is the value MATCH | PAPER == 1 | 2 == 3
 */
enum Resource            {    MATCH = 1, PAPER = 2,   TOBACCO = 4};
char* resource_name [] = {"", "match",   "paper", "", "tobacco"};

// # of threads waiting for a signal. Used to ensure that the agent
// only signals once all other threads are ready.
int num_active_threads = 0;

int signal_count [5];  // # of times resource signalled
int smoke_count  [5];  // # of times smoker with resource smoked

/**
 * This is the agent procedure.  It is complete and you shouldn't change it in
 * any material way.  You can modify it if you like, but be sure that all it does
 * is choose 2 random resources, signal their condition variables, and then wait
 * wait for a smoker to smoke.
 */
void* agent (void* av) {
  struct Agent* a = av;
  static const int choices[]         = {MATCH|PAPER, MATCH|TOBACCO, PAPER|TOBACCO};
  static const int matching_smoker[] = {TOBACCO,     PAPER,         MATCH};

  srandom(time(NULL));
  
  uthread_mutex_lock (a->mutex);
  // Wait until all other threads are waiting for a signal
  while (num_active_threads < 3)
    uthread_cond_wait (a->smoke);

  for (int i = 0; i < NUM_ITERATIONS; i++) {
    int r = random() % 6;
    switch(r) {
    case 0:
      signal_count[TOBACCO]++;
      VERBOSE_PRINT ("match available\n");
      uthread_cond_signal (a->match);
      VERBOSE_PRINT ("paper available\n");
      uthread_cond_signal (a->paper);
      break;
    case 1:
      signal_count[PAPER]++;
      VERBOSE_PRINT ("match available\n");
      uthread_cond_signal (a->match);
      VERBOSE_PRINT ("tobacco available\n");
      uthread_cond_signal (a->tobacco);
      break;
    case 2:
      signal_count[MATCH]++;
      VERBOSE_PRINT ("paper available\n");
      uthread_cond_signal (a->paper);
      VERBOSE_PRINT ("tobacco available\n");
      uthread_cond_signal (a->tobacco);
      break;
    case 3:
      signal_count[TOBACCO]++;
      VERBOSE_PRINT ("paper available\n");
      uthread_cond_signal (a->paper);
      VERBOSE_PRINT ("match available\n");
      uthread_cond_signal (a->match);
      break;
    case 4:
      signal_count[PAPER]++;
      VERBOSE_PRINT ("tobacco available\n");
      uthread_cond_signal (a->tobacco);
      VERBOSE_PRINT ("match available\n");
      uthread_cond_signal (a->match);
      break;
    case 5:
      signal_count[MATCH]++;
      VERBOSE_PRINT ("tobacco available\n");
      uthread_cond_signal (a->tobacco);
      VERBOSE_PRINT ("paper available\n");
      uthread_cond_signal (a->paper);
      break;
    }
    VERBOSE_PRINT ("agent is waiting for smoker to smoke\n");

    uthread_cond_wait (a->smoke);

  }
  
  uthread_mutex_unlock (a->mutex);

  return NULL;
}

//smoker activation function//////////////////////////////////////////////////////////////////

void activate_Smoker(int *sum){
  switch(*sum){
    case (PAPER+MATCH):
      *sum =0;
      uthread_cond_signal(match_Paper);
      break;
    case (PAPER+TOBACCO):
      *sum =0;
      uthread_cond_signal(paper_Tobacco);

      break;
    case (MATCH+TOBACCO):
      *sum =0;
      uthread_cond_signal(match_Tobacco);

      break;
    default:
      break;
  }
}
///////////////////////////

//smoker Functions themselves/////////////////////////////////////////////////////////////////
void tobaccoSmoker(void* av){
  num_active_threads++;
  struct Agent* a = av;
  uthread_mutex_lock(a->mutex);

  while(1){
    uthread_cond_wait(match_Paper);
    uthread_cond_signal (a->smoke);
    smoke_count[TOBACCO]++;
  }
  uthread_mutex_unlock(a->mutex);
}

void paperSmoker(void* av){
  num_active_threads++;

  struct Agent* a = av;
  uthread_mutex_lock(a->mutex);

  while(1){
    uthread_cond_wait(match_Tobacco);
    uthread_cond_signal (a->smoke);
    smoke_count[PAPER]++;

  }
  uthread_mutex_unlock(a->mutex);
}

void matchSmoker(void* av){
  num_active_threads++;

  struct Agent* a = av;
  uthread_mutex_lock(a->mutex);

  while(1){
    uthread_cond_wait(paper_Tobacco);
    uthread_cond_signal (a->smoke);
    smoke_count[MATCH]++;

  }
  uthread_mutex_unlock(a->mutex);
}

/////////////////////


//checkers////////////////////////////////////////////////////////////////////////////////////
void* paperChecker(void* av){
  num_active_threads++;

  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);

  while(1)
  {
    uthread_cond_wait (a->paper);
    sum = sum + PAPER;
    activate_Smoker(&sum);

  }
  uthread_mutex_unlock(a->mutex);
}

void* tobaccoChecker(void* av){
  num_active_threads++;

  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);

  while(1)
  {
    uthread_cond_wait (a->tobacco);
    sum = sum + TOBACCO;
    activate_Smoker(&sum);

  }
  uthread_mutex_unlock(a->mutex);
}

void* matchChecker(void* av){
  num_active_threads++;

  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);

  while(1)
  {
    uthread_cond_wait (a->match);
    sum = sum + MATCH;
    activate_Smoker(&sum);

  }
  uthread_mutex_unlock(a->mutex);
}
/////////////////////////

int main (int argc, char** argv) {
  
  struct Agent* a = createAgent();
  uthread_t agent_thread;

  uthread_init(4);
  
  // TODO
  match_Paper = uthread_cond_create(a->mutex);
  paper_Tobacco = uthread_cond_create(a->mutex);
  match_Tobacco = uthread_cond_create(a->mutex);

  uthread_create(paperChecker, a);
  uthread_create(tobaccoChecker, a);
  uthread_create(matchChecker, a);
  uthread_create(matchSmoker, a);
  uthread_create(paperSmoker, a);
  uthread_create(tobaccoSmoker, a);
  agent_thread = uthread_create(agent, a);
  uthread_join(agent_thread, NULL);


  assert (signal_count [MATCH]   == smoke_count [MATCH]);
  assert (signal_count [PAPER]   == smoke_count [PAPER]);
  assert (signal_count [TOBACCO] == smoke_count [TOBACCO]);
  assert (smoke_count [MATCH] + smoke_count [PAPER] + smoke_count [TOBACCO] == NUM_ITERATIONS);

  printf ("Smoke counts: %d matches, %d paper, %d tobacco\n",
          smoke_count [MATCH], smoke_count [PAPER], smoke_count [TOBACCO]);

  return 0;
}
