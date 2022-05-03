#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include "uthread.h"
#include "uthread_sem.h"

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
#endif

#define MAX_OCCUPANCY  3
#define NUM_ITERATIONS 100
#define NUM_CARS       20

// These times determine the number of times yield is called when in
// the street, or when waiting before crossing again.
#define CROSSING_TIME             NUM_CARS
#define WAIT_TIME_BETWEEN_CROSSES NUM_CARS

/**
 * You might find these declarations useful.
 */
enum Direction {EAST = 0, WEST = 1};
const static enum Direction oppositeEnd [] = {WEST, EAST};

static int cars_in_Block = 0;

static int total_cars_east = 0;
static int total_cars_west = 0;

static int total_trips_east = 0;
static int total_trips_west = 0;

struct Street {
  // TODO
  uthread_sem_t create;
  uthread_sem_t exit;
  uthread_sem_t enter;

  uthread_sem_t entry_success;
  uthread_sem_t go_East;
  uthread_sem_t go_West;
  uthread_sem_t proceed;
  uthread_sem_t flaggers;

  uthread_sem_t block_is_free;
  uthread_sem_t block_is_full;

  uthread_sem_t dead;
  uthread_sem_t all_created;
  uthread_sem_t exit_success;



} Street;

void initializeStreet(void) {
  // TODO
  Street.create = uthread_sem_create(1);
  Street.flaggers = uthread_sem_create(1);
  Street.exit = uthread_sem_create(1);
  Street.enter = uthread_sem_create(1);

  Street.entry_success = uthread_sem_create(1);
  Street.go_East = uthread_sem_create(0);
  Street.go_West = uthread_sem_create(0);
  Street.proceed = uthread_sem_create(0);
  Street.block_is_free = uthread_sem_create(1);
  Street.block_is_full = uthread_sem_create(0);
  Street.exit_success = uthread_sem_create(1);

  Street.dead = uthread_sem_create(0);
  Street.all_created = uthread_sem_create(0);
}

#define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_CARS)
int             entryTicker;                                          // incremented with each entry
int             waitingHistogram [WAITING_HISTOGRAM_SIZE];
int             waitingHistogramOverflow;
uthread_sem_t   waitingHistogramLock;
int             occupancyHistogram [2] [MAX_OCCUPANCY + 1];

void enterStreet (enum Direction g) {
  // TODO
  uthread_sem_wait(Street.enter);

  entryTicker++;
  cars_in_Block++;
  
  if (g==EAST)
  {
    occupancyHistogram[EAST][cars_in_Block]++;
    total_trips_east--;
  }
  if (g==WEST)
  {
    occupancyHistogram[WEST][cars_in_Block]++;
    total_trips_west--;
  }

  for (int i = 0; i < CROSSING_TIME; i++)
    uthread_yield();


  if (cars_in_Block == 3){
    uthread_sem_signal(Street.block_is_full);
  }
  uthread_sem_signal(Street.entry_success);

  uthread_sem_signal(Street.enter);


}

void leaveStreet(void) {
  // TODO
  uthread_sem_wait(Street.exit);

  cars_in_Block--;

  for (int i = 0; i < WAIT_TIME_BETWEEN_CROSSES; i++)
    uthread_yield();



  uthread_sem_signal(Street.exit_success);

  if (cars_in_Block == 0){
    uthread_sem_signal(Street.block_is_free);
  }
  uthread_sem_signal(Street.exit);


}

void recordWaitingTime (int waitingTime) {
  uthread_sem_wait (waitingHistogramLock);
  if (waitingTime < WAITING_HISTOGRAM_SIZE)
    waitingHistogram [waitingTime] ++;
  else
    waitingHistogramOverflow ++;
  uthread_sem_signal (waitingHistogramLock);
  
}

void send_west()
{
  int last_Trips=0;

  if (total_trips_west > 0 && total_cars_west>0)
  {
  last_Trips = 1;

  uthread_sem_signal(Street.go_West);
  uthread_sem_wait(Street.entry_success);
  }
  if (total_trips_west > 0 && total_cars_west > 1)
  {
        last_Trips = 2;

  uthread_sem_signal(Street.go_West);
  uthread_sem_wait(Street.entry_success);
  }
  if (total_trips_west > 0 && total_cars_west > 2)
  {
        last_Trips = 3;

  uthread_sem_signal(Street.go_West);
  uthread_sem_wait(Street.entry_success);
  }

  if (total_cars_west >2)
    uthread_sem_wait(Street.block_is_full);
  
if (last_Trips >= 1){
  uthread_sem_signal(Street.proceed);
  uthread_sem_wait(Street.exit_success);
  }
  if (last_Trips >= 2){
  uthread_sem_signal(Street.proceed);
  uthread_sem_wait(Street.exit_success);
  }
  if (last_Trips >= 3){
  uthread_sem_signal(Street.proceed);
  uthread_sem_wait(Street.exit_success);
  }

}

void send_east()
{
  int last_Trips=0;
  if (total_trips_east > 0 && total_cars_east>0)
  {
    last_Trips = 1;

    uthread_sem_signal(Street.go_East);
    uthread_sem_wait(Street.entry_success);
  }
  if (total_trips_east > 0 && total_cars_east > 1)
  {
  last_Trips = 2;
  uthread_sem_signal(Street.go_East);
  uthread_sem_wait(Street.entry_success);

  }
  if (total_trips_east > 0 && total_cars_east >2)
  {
  last_Trips = 3;

  uthread_sem_signal(Street.go_East);
  uthread_sem_wait(Street.entry_success);
  }
  
  if (total_cars_east >2)
    uthread_sem_wait(Street.block_is_full);

  if (last_Trips >= 1){
  uthread_sem_signal(Street.proceed);
  uthread_sem_wait(Street.exit_success);
  }
  if (last_Trips >= 2){
  uthread_sem_signal(Street.proceed);
  uthread_sem_wait(Street.exit_success);
  }
  if (last_Trips >= 3){
  uthread_sem_signal(Street.proceed);
  uthread_sem_wait(Street.exit_success);
  }
}

void *flaggers_Thread(void *v)
{
  while (entryTicker < (NUM_CARS * NUM_ITERATIONS))
  {
    if (total_cars_east>0)
      uthread_sem_wait(Street.block_is_free);
      send_east();

    

    if (total_cars_west>0)
      uthread_sem_wait(Street.block_is_free);
      send_west();

  }

}


void *car_Thread(void *v)
{
  uthread_sem_wait(Street.create);

  int car_direction;
  if (random() % 2 == 1)
  {
    car_direction = EAST;
    total_cars_east++;
    total_trips_east = total_trips_east + NUM_ITERATIONS;
  }
  else
  {
    car_direction = WEST;
    total_cars_west++;
    total_trips_west = total_trips_west + NUM_ITERATIONS;

  }
  int crossings_count = 0;
  int wait_time_start;
  int wait_time_final;

  uthread_sem_signal(Street.create);
  uthread_sem_wait(Street.all_created);

  while (crossings_count < NUM_ITERATIONS)
  {
    wait_time_start = entryTicker;

    if (car_direction == EAST)
    {


      uthread_sem_wait(Street.go_East);

      if (cars_in_Block < 3)
      {
        wait_time_final = entryTicker - wait_time_start;
        recordWaitingTime(wait_time_final);

        enterStreet(EAST);
      }
      else
      {
        while (cars_in_Block == 3)
        {
        };
        wait_time_final = entryTicker - wait_time_start;
        recordWaitingTime(wait_time_final);
        enterStreet(EAST);
      }
    }
    else if (car_direction == WEST)
    {


      uthread_sem_wait(Street.go_West);

      if (cars_in_Block < 3)
      {
        wait_time_final = entryTicker - wait_time_start;
        recordWaitingTime(wait_time_final);
        enterStreet(WEST);
      }
      else
      {
        while (cars_in_Block == 3)
        {
        };
        wait_time_final = entryTicker - wait_time_start;
        recordWaitingTime(wait_time_final);
        enterStreet(WEST);
      }
    }

    uthread_sem_wait(Street.proceed);
    // uthread_sem_signal(Street.exit_);

    leaveStreet();
    // uthread_sem_wait(Street.exit_success);

    crossings_count++;

  }

  if (car_direction == EAST)
    total_cars_east--;
  else
    total_cars_west--;
  uthread_sem_signal(Street.dead);

  return NULL;
}

//
// TODO
// You will probably need to create some additional procedures etc.
//

int main (int argc, char** argv) {
  
  uthread_init(8);

  waitingHistogramLock = uthread_sem_create(1);

  initializeStreet();
  uthread_t pt [NUM_CARS];
  uthread_t flaggers;

  for (int i = 0; i < NUM_CARS; i++)
  {
    pt[i] = uthread_create(car_Thread, NULL);
  }

  flaggers = uthread_create(flaggers_Thread, NULL);

  for (int i = 0; i < NUM_CARS; i++)
  {
    uthread_sem_signal(Street.all_created);
  }  

  uthread_join(flaggers, NULL);
  for (int i = 0; i< NUM_CARS;i++)
    uthread_sem_wait(Street.dead);


  printf ("Times with 1 car  going east: %d\n", occupancyHistogram [EAST] [1]);
  printf ("Times with 2 cars going east: %d\n", occupancyHistogram [EAST] [2]);
  printf ("Times with 3 cars going east: %d\n", occupancyHistogram [EAST] [3]);
  printf ("Times with 1 car  going west: %d\n", occupancyHistogram [WEST] [1]);
  printf ("Times with 2 cars going west: %d\n", occupancyHistogram [WEST] [2]);
  printf ("Times with 3 cars going west: %d\n", occupancyHistogram [WEST] [3]);

  printf ("Waiting Histogram\n");
  for (int i=0; i < WAITING_HISTOGRAM_SIZE; i++)
    if (waitingHistogram [i])
      printf ("  Cars waited for           %4d car%s to enter: %4d time(s)\n",
        i, i==1 ? " " : "s", waitingHistogram [i]);
  if (waitingHistogramOverflow)
    printf ("  Cars waited for more than %4d cars to enter: %4d time(s)\n",
      WAITING_HISTOGRAM_SIZE, waitingHistogramOverflow);
}
