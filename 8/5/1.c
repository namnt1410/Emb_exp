#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <pthread.h>

#define SHIMSIZE 1024
#define KEYFILE_PATH "keyfilepath"
#define PROJ_CHAR    'S'

int main()
{
  int i;
  int shm_id;
  pthread_mutex_t *pm, *ptr;

  printf ("writer started.\n");

  key_t shm_key = ftok( KEYFILE_PATH,(int)PROJ_CHAR);
  const int shm_size = SHIMSIZE;

  /* Allocate a shared memory segment. */
  shm_id = shmget (shm_key, shm_size, IPC_CREAT | S_IRUSR | S_IWUSR);

  /* Attach the shared memory segment. */
  pm = (pthread_mutex_t *) shmat (shm_id, 0, 0);

  //pthread_mutex_t pm ;
  pthread_mutexattr_t pmattr;

  // Initialize the mutex attribute object
  pthread_mutexattr_init(&pmattr);

  // Set mutex attribute(Setting for using mutex to inter process)
  if (pthread_mutexattr_setpshared(&pmattr, PTHREAD_PROCESS_SHARED) != 0) {
    perror("pthread_mutexattr_setpshared");
    exit(1);
  }
  // Initialize mutex
  pthread_mutex_init(pm, &pmattr);

  // Lock mutex
  if (pthread_mutex_lock(pm) != 0) {
    perror("pthread_mutex_lock");
    exit(1);
  }

  printf("mutex lock\n");

  printf("Press any key to continue...");
  char c=getchar();
  printf("Enter is input\n");

  // Unlock mutex
  if (pthread_mutex_unlock(pm) != 0) {
    perror("pthread_mutex_unlock");
    exit(1);
  }
  printf("mutex unlock\n");

  /* Detach the shared memory segment. */
  shmdt (pm);
  /* Deallocate the shared memory segment.*/
  shmctl (shm_id, IPC_RMID, 0);

  return 0;
}
