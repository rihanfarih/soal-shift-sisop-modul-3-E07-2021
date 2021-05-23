#include <stdio.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int tes[24];
int *value;
pthread_t thread;
int angka;

typedef struct matriks
{
  long long lama;
  long long baru;
} index;

void operasi(){
  for (int i = 0; i < 24; i++)
  {
    if (i%6==0)
    {
      printf("\n");
    }
    index *pointer = (index*)malloc(sizeof(*pointer));
    pointer->lama=value[i];
    pointer->baru=tes[i];
    pthread_create(&thread, NULL, factorial, (void*)pointer);
    pthread_join(thread,NULL);
  }
  
}

int faktorial(int x, int isi){
  int hasil = x;
  if (x==1)
  {
    return 1;
  }
  else if (x==2)
  {
    hasil *=((x-1));
  }
  else if(isi>x){
    for (int a = 1; a < isi; a++)
    {
      if(x-a==0){
        continue;
      }
      else if (x-a>0){
        hasil *= (x-a);
      }
    }
    
  }
  return hasil;
}

void *factorial(void* arg) {

  index *value = (index *)arg;
  int hasil;

  if (value->lama==0)
  {
    printf("0\t");
  }
  if (value->baru==0)
  {
    printf("0\t");
  }
  else
  {
    hasil = faktorial(value->lama,value->baru);
    printf("%d\t",hasil);
  }
  
  
}

int main() {
  key_t key = 1234;
  int shmid = shmget(key, sizeof(int)*6*4, IPC_CREAT | 0666);
  value = shmat(shmid, NULL, 0);

  for (int a = 0; a < 24; a++)
  {
    scanf("%d", &tes[a]);
  }
  
  printf("Matriks sebelumnya:\n");
    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
        printf("%d\t", value[i*6+j]);
        }
        printf("\n");
    }

  printf("setelah faktorial:\n");

  operasi();
  printf("\n");
  
  shmdt(value);
}
