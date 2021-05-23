#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //library thread
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

struct index
{
    int i,j;
};

int MA[4][3];

int MB[3][6];

int hasil[4][6];

void *operasi(void* arg){
    int i =((struct index*)arg)->i;
    int j =((struct index*)arg)->j;

    for (int x = 0; x < 3; x++) {
        hasil[i][j] += MA[i][x] * MB[x][j];
    }
}

void inputmatriks(){
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &MA[i][j]);
        }
        
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            scanf("%d", &MB[i][j]);
        }
        
    }
    
}

int main()
{
    pthread_t tid[4][6];

    inputmatriks();

    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {

        struct index *ke = (struct index *)malloc(sizeof(struct index));
        ke->i = i;
        ke->j = j;
        pthread_create(&tid[i][j], NULL, &operasi, (void *)ke);
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
        pthread_join(tid[i][j], NULL);
        }
    }

    printf("Matriks :\n");
    for (int i=0; i<4; i++) {
        for (int j=0; j<6; j++) {
        printf("%d ", hasil[i][j]);
        }
        printf("\n");
    }
    //update
    key_t key = 1234;
      int *value;

      int shmid = shmget(key, sizeof(hasil), IPC_CREAT | 0666);
      value = shmat(shmid, NULL, 0);

      int* p = (int *)value;

      memcpy(p, hasil, 80);

      shmdt(value);
}
