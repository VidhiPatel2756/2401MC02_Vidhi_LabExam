#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  // Given 3 semaphores: sem 0 = 1, sem 1 = 0, sem 2 = 0
  if(sem_init(0, 1) < 0 || sem_init(1, 0) < 0 || sem_init(2, 0) < 0)
  {
    printf(1, "sem_init failed\n");
    exit();
  }

  // Child 1: prints A 5 times
  if(fork() == 0)
  {
    for(int i = 0; i < 5; i++)
    {
      sem_wait(0);
      printf(1, "A ");
      sem_post(1);
    }
    exit();
  }

  // Child 2: prints B 5 times
  if(fork() == 0)
  {
    for(int i = 0; i < 5; i++)
    {
      sem_wait(1);
      printf(1, "B ");
      sem_post(2);
    }
    exit();
  }

  // Child 3: prints C 5 times
  if(fork() == 0)
  {
    for(int i = 0; i < 5; i++)
    {
      sem_wait(2);
      printf(1, "C ");
      sem_post(0);
    }
    exit();
  }

  // Parent waits for all 3 children
  for(int i = 0; i < 3; i++)
  {
    wait();
  }

  printf(1, "\nDone\n");
  exit();
}
