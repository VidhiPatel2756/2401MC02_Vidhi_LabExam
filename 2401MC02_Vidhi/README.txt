Name : Vidhi Patel
Roll Number : 2401MC02
Set Number : 1
Date : 17/11/2026

Question 1: Counting Semaphores for Process Synchronization 
sem.c : made a new file sem.c and generated semaphore function for question 1
defs.h : declared sem_init, sem_wait, sem_post
main.c: wrote seminit_lock to declare it
syscall.h: defined system call numbers to sem_init, sem_wait, sem_post
syscall.c: array mapping syscall numbers from syscall.h for sem_init, sem_wait, sem_post
sysproc.c: wrote the functions syscall.h for sem_init, sem_wait, sem_post
user.h: system calls int sem_init(int, int); int sem_wait(int); int sem_post(int);
usys.S: SYSCALL(sem_init), SYSCALL(sem_wait), SYSCALL(sem_post)
Makefile: declared synctest.c
synctest.c: wrote c program for applying question 1

Question 2: Memory Statistics and Address Translation
defs.h: declared freepages, va2pa
syscall.h: defined system call numbers to freepages, va2pa
syscall.c: array mapping syscall numbers from syscall.h for freepages, va2pa
sysproc.c: wrote the functions freepages, va2pa
user.h: system calls int sys_freepages(void)
usys.S: SYSCALL(freepages), SYSCALL(va2pa)
Makefile: declared memtest.c
kalloc.c: wrote the function int va2pa(int)
vm.c: more on function int va2pa(int)
memtest.c: wrote c program for applying question 2
