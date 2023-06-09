#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SHM_SIZE 1024

int main() {

  int shmid;
  key_t key;
  char *shm, *s;

  key = ftok(".", 1);

  shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

  if(shmid < 0) {
    perror("shmget error");
    exit(-1);
  }

  shm = shmat(shmid, NULL, 0);

  if(shm == (char *) -1) {
    perror("shmat error");
    exit(-1);
  }

  s = shm;
  for(char c = 'a'; c <= 'z'; c++) {

    *s++ = c;

  }

  *s++ = '\0';


  printf("Data read from shared memory: %s\n", shm);

  if(shmdt(shm) == -1) {

    perror("shmdt error");
    exit(-1);
  }


  return 0;
}
