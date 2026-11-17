#include "types.h"
#include "defs.h"
#include "param.h"
#include "spinlock.h"

#define NSEM 8

struct semaphore {
  int value;
  int in_use;
};

struct {
  struct spinlock lock;
  struct semaphore sem[NSEM];
} semtable;

// Called once at kernel startup in main.c
void
seminit_lock(void)
{
  initlock(&semtable.lock, "semtable");
  for(int i = 0; i < NSEM; i++){
    semtable.sem[i].value = 0;
    semtable.sem[i].in_use = 0;
  }
}

int
sem_init(int id, int value)
{
  if(id < 0 || id >= NSEM || value < 0)
    return -1;

  acquire(&semtable.lock);
  semtable.sem[id].value = value;
  semtable.sem[id].in_use = 1;
  release(&semtable.lock);
  return 0;
}

int
sem_wait(int id)
{
  if(id < 0 || id >= NSEM)
    return -1;

  acquire(&semtable.lock);
  if(semtable.sem[id].in_use == 0){
    release(&semtable.lock);
    return -1;
  }

  // Re-check condition after every wakeup to prevent lost/spurious wakeups
  while(semtable.sem[id].value == 0){
    sleep(&semtable.sem[id], &semtable.lock);
    // Guard in case semaphore was re-initialized/invalidated while sleeping
    if(semtable.sem[id].in_use == 0){
      release(&semtable.lock);
      return -1;
    }
  }

  semtable.sem[id].value--;
  release(&semtable.lock);
  return 0;
}

int
sem_post(int id)
{
  if(id < 0 || id >= NSEM)
    return -1;

  acquire(&semtable.lock);
  if(semtable.sem[id].in_use == 0){
    release(&semtable.lock);
    return -1;
  }

  semtable.sem[id].value++;
  wakeup(&semtable.sem[id]);
  release(&semtable.lock);
  return 0;
}
