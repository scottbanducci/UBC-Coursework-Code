#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include "uthread.h"
#include "uthread_mutex_cond.h"

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf(S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void)0) // do nothing
#endif

#define MAX_OCCUPANCY 3
#define NUM_ITERATIONS 100
#define NUM_CARS 20

// These times determine the number of times yield is called when in
// the street, or when waiting before crossing again.
#define CROSSING_TIME NUM_CARS
#define WAIT_TIME_BETWEEN_CROSSES NUM_CARS

/**
 * You might find these declarations useful.
 */
enum Direction
{
  EAST = 0,
  WEST = 1
};
const static enum Direction oppositeEnd[] = {WEST, EAST};

static int cars_in_Block = 0;

static int total_cars_east = 0;
static int total_cars_west = 0;

static int total_trips_east = 0;
static int total_trips_west = 0;

static int block_is_free_FLAG = 0;

struct Street
{
  // TODO
  uthread_mutex_t mutex;
  uthread_mutex_t enter_exit;

  uthread_cond_t go_East;
  uthread_cond_t go_West;
  uthread_cond_t block_is_free;
  uthread_cond_t car_entry_success;
  uthread_cond_t proceed;



} Street;

void initializeStreet(void)
{
  // TODO
  Street.mutex = uthread_mutex_create();
  Street.enter_exit =  uthread_mutex_create();

  Street.go_East = uthread_cond_create(Street.mutex);
  Street.go_West = uthread_cond_create(Street.mutex);
  Street.block_is_free = uthread_cond_create(Street.mutex);
  Street.car_entry_success = uthread_cond_create(Street.mutex);
  Street.proceed = uthread_cond_create(Street.mutex);
}

#define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_CARS)
int entryTicker; // incremented with each entry
int waitingHistogram[WAITING_HISTOGRAM_SIZE];
int waitingHistogramOverflow;
uthread_mutex_t waitingHistogramLock;
int occupancyHistogram[2][MAX_OCCUPANCY + 1];

void enterStreet(enum Direction g)
{
  // TODO  
  uthread_mutex_lock(Street.enter_exit);

  block_is_free_FLAG = 0;

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

  uthread_cond_signal(Street.car_entry_success);

 

  for (int i = 0; i < CROSSING_TIME; i++)
    uthread_yield();

  uthread_mutex_unlock(Street.enter_exit);

}

void leaveStreet(void)
{
  // TODO
  uthread_mutex_lock(Street.enter_exit);

  cars_in_Block--;

  if (cars_in_Block == 0){
    block_is_free_FLAG = 1;
    uthread_cond_signal(Street.block_is_free);
  }

  for (int i = 0; i < WAIT_TIME_BETWEEN_CROSSES; i++)
    uthread_yield();

  uthread_mutex_unlock(Street.enter_exit);

}

void recordWaitingTime(int waitingTime)
{
  uthread_mutex_lock(waitingHistogramLock);
  if (waitingTime < WAITING_HISTOGRAM_SIZE)
    waitingHistogram[waitingTime]++;
  else
    waitingHistogramOverflow++;
  uthread_mutex_unlock(waitingHistogramLock);
}

//
// TODO
// You will probably need to create some additional procedures etc.
//

void send_east()
{
  if (total_trips_east > 0 && total_cars_east>0)
  {
  uthread_cond_signal(Street.go_East);
  uthread_cond_wait(Street.car_entry_success);
  }
  if (total_trips_east > 0 && total_cars_east > 1)
  {

  uthread_cond_signal(Street.go_East);
  uthread_cond_wait(Street.car_entry_success);
  }
  if (total_trips_east > 0 && total_cars_east >2)
  {

  uthread_cond_signal(Street.go_East);
  uthread_cond_wait(Street.car_entry_success);
  }

  uthread_cond_broadcast(Street.proceed);
  if (block_is_free_FLAG == 0){
    uthread_cond_wait(Street.block_is_free);
  }
}
void send_west()
{
  if (total_trips_west > 0 && total_cars_west>0)
  {
  uthread_cond_signal(Street.go_West);
  uthread_cond_wait(Street.car_entry_success);
  }
  if (total_trips_west > 0 && total_cars_west > 1)
  {
    uthread_cond_signal(Street.go_West);
    uthread_cond_wait(Street.car_entry_success);
  }
  if (total_trips_west > 0 && total_cars_west > 2)
  {
  uthread_cond_signal(Street.go_West);
  uthread_cond_wait(Street.car_entry_success);
  }

  uthread_cond_broadcast(Street.proceed);
  if (block_is_free_FLAG == 0){
    uthread_cond_wait(Street.block_is_free);
}
}


void *flaggers_Thread(void *v)
{
  uthread_mutex_lock(Street.mutex);

  while (entryTicker < (NUM_CARS * NUM_ITERATIONS))
  {
    if (total_cars_east>0)
     send_east();
    

    if (total_cars_west>0)
     send_west();


  }
  uthread_mutex_unlock(Street.mutex);

}

void *car_Thread(void *v)
{
  uthread_mutex_lock(Street.mutex);

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

  while (crossings_count < NUM_ITERATIONS)
  {
    if (car_direction == EAST)
    {

      wait_time_start = entryTicker;
      uthread_cond_wait(Street.go_East);

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

      wait_time_start = entryTicker;
      uthread_cond_wait(Street.go_West);

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
    uthread_cond_wait(Street.proceed);
    leaveStreet();
    crossings_count++;

  }

  if (car_direction == EAST)
    total_cars_east--;
  else
    total_cars_west--;
  uthread_mutex_unlock(Street.mutex);

  return NULL;
}

int main(int argc, char **argv)
{

  uthread_init(8);

  waitingHistogramLock = uthread_mutex_create();

  initializeStreet();
  uthread_t pt[NUM_CARS];
  uthread_t flaggers;

  // TODO
  for (int i = 0; i < NUM_CARS; i++)
  {
    pt[i] = uthread_create(car_Thread, NULL);
  }

  flaggers = uthread_create(flaggers_Thread, NULL);

  // for (int k = 0; k < NUM_CARS; ++k)
  // {
  //        printf("joined\n");

  //   uthread_join(pt[k], NULL);

  // }
 uthread_join(flaggers, NULL);

  printf("Times with 1 car  going east: %d\n", occupancyHistogram[EAST][1]);
  printf("Times with 2 cars going east: %d\n", occupancyHistogram[EAST][2]);
  printf("Times with 3 cars going east: %d\n", occupancyHistogram[EAST][3]);
  printf("Times with 1 car  going west: %d\n", occupancyHistogram[WEST][1]);
  printf("Times with 2 cars going west: %d\n", occupancyHistogram[WEST][2]);
  printf("Times with 3 cars going west: %d\n", occupancyHistogram[WEST][3]);

  printf("Waiting Histogram\n");
  for (int i = 0; i < WAITING_HISTOGRAM_SIZE; i++)
    if (waitingHistogram[i])
      printf("  Cars waited for           %4d car%s to enter: %4d time(s)\n",
             i, i == 1 ? " " : "s", waitingHistogram[i]);
  if (waitingHistogramOverflow)
    printf("  Cars waited for more than %4d cars to enter: %4d time(s)\n",
           WAITING_HISTOGRAM_SIZE, waitingHistogramOverflow);
}
