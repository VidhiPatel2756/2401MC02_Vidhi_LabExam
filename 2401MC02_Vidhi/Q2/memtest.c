#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int gvar = 100;

int
main(int argc, char *argv[])
{
  uint64 start_pages, after_sbrk, before_fork, after_wait;
  uint64 va, pa;
  int pid;

  // (i) Free pages at start-up
  start_pages = freepages();
  printf("Free pages initially: %d\n", (int)start_pages);

  // (ii) Allocate 10 pages using sbrk and check free pages again
  if(sbrk(10 * 4096) == (char*)-1){
    printf("sbrk failed\n");
    exit(1);
  }
  after_sbrk = freepages();
  printf("Free pages after sbrk(10 * 4096): %d\n", (int)after_sbrk);

  // (iii) Virtual and physical address of global variable
  va = (uint64)&gvar;
  pa = va2pa(va);
  printf("Global var -> VA: %p, PA: %p\n", (void*)va, (void*)pa);

  // (iv) Invalid/unmapped user address check
  printf("va2pa(0x7FFFFFFF): %d\n", (int)va2pa(0x7FFFFFFF));

  // (v) Check addresses and free pages across fork and wait
  before_fork = freepages();
  printf("Free pages before fork: %d\n", (int)before_fork);

  pid = fork();
  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0){
    printf("Child  -> VA: %p, PA: %p, Free pages: %d\n",
           (void*)&gvar, (void*)va2pa((uint64)&gvar), (int)freepages());
    exit(0);
  } else {
    printf("Parent -> VA: %p, PA: %p\n",
           (void*)&gvar, (void*)va2pa((uint64)&gvar));
    wait(0);
    after_wait = freepages();
    printf("Free pages after wait: %d\n", (int)after_wait);
  }

  exit(0);
}
