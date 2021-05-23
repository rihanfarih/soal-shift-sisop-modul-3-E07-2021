#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <limits.h>
#define max 1000

pthread_t tid[500];
int flag=1;
//char p_dir[] = "/home/sfayha/soal3/";

typedef struct arg_struct {
    char ndir[max];
    char cwd[max];
}arg_struct;

//cek file or folder
int regularf(const char *path)
{
    struct stat path_stat;
    if(stat(path, &path_stat) != 0) return 0; 
    return S_ISREG(path_stat.st_mode);
}

void fmove(char *argv, char *cwd){
    int isHidden=0;
    char string[max];
    strcpy(string, argv);
    int isFile = regularf(string);// ngecek file/bukan

    char t = '.'; 
    char* tipe = strrchr(string, t); 

    char m = '/';
    char* nama = strrchr(string, m); //yang pertama
    char typeLow[100];
    if (nama[1]=='.'){
        isHidden = 1;
    }
    
    if(tipe)
    {
        if((tipe[strlen(tipe)-1] >= 'a' && tipe[strlen(tipe)-1] <= 'z') || (tipe[strlen(tipe)-1] >= 'A' && tipe[strlen(tipe)-1] <= 'Z'))
        {
            strcpy(typeLow, tipe);
            for(int i = 0; typeLow[i]; i++){
                typeLow[i] = tolower(typeLow[i]);
            }
        }
    }
    else
    {
        if(!isFile){
        printf("ini adalah folder\n");
        return;
        }
        else
        {
        strcpy(typeLow, " Unknown"); 
        }
    }
        if (isHidden) {
            strcpy (typeLow, " Hidden");
        }
        mkdir((typeLow+ 1), 0777); 

        size_t len = 0 ;
        char a[max] ;
        strcpy(a, argv);
        char b[max] ;

        strcpy(b, cwd);
        strcat(b, "/");
        strcat(b, typeLow+1);
        strcat(b, nama);
        if (!rename(a, b))printf("Berhasil Dikategorikan\n");
        else printf("Sad, Gagal :(\n");
        remove(a);
}

void fsmove(char *argv, char *cwd){
    int isHidden=0;
    char string[max];
    strcpy(string, argv);
    int isFile = regularf(string);

    char t = '.'; 
    char* tipe = strrchr(string, t); 

    char m = '/';
    char* nama = strrchr(string, m);
    char typeLow[100];
    if (nama[1]=='.'){
        isHidden = 1;
    }
    
    if(tipe)
    {
        if((tipe[strlen(tipe)-1] >= 'a' && tipe[strlen(tipe)-1] <= 'z') || (tipe[strlen(tipe)-1] >= 'A' && tipe[strlen(tipe)-1] <= 'Z'))
        {
            strcpy(typeLow, tipe);
            for(int i = 0; typeLow[i]; i++){
                typeLow[i] = tolower(typeLow[i]);
            }
        }
    }
    else
    {
        if(!isFile){
        printf("ini adalah folder, argumen salah\n");
        return;
        }
        else
        {
        strcpy(typeLow, " Unknown");
        }
    }
        if (isHidden) {
            strcpy (typeLow, " Hidden");
        }
        mkdir((typeLow+ 1), 0777); 

        size_t len = 0 ;
        char a[max] ;
        strcpy(a, argv);
        char b[max] ;

        strcpy(b, cwd);
        strcat(b, "/");
        strcat(b, typeLow+1);
        strcat(b, nama);
        if (rename(a,b)) flag=0;
        remove(a);
}

void *perintahd(void* arg){
    arg_struct args = *(arg_struct*) arg;
    fsmove(args.ndir, args.cwd);
    pthread_exit(0);
}

void *perintahf(void* arg){
    arg_struct args = *(arg_struct*) arg;
    fmove(args.ndir, args.cwd);
    pthread_exit(0);
}


void sortHere(char *ndir){
    arg_struct args;
    flag =1;
    
    char namaProgramIni[260];
    strcpy(namaProgramIni, "/home/sfayha/soal3");
    strcat(namaProgramIni, "3.c");
    
    strcpy(args.cwd,"/home/sfayha/soal3");
    DIR *dirp;
    struct dirent *entry;
    dirp = opendir(ndir);
    
    int index = 0;
    while((entry = readdir(dirp)) != NULL) {
        if(entry->d_type == DT_REG) {
            char namaFile[305];

            //strcat(namaFile, ndir);
            //strcat(namaFile, entry->d_name);
            sprintf(namaFile, "%s%s", ndir, entry->d_name);
            strcpy(args.ndir, namaFile);

            if(strcmp(namaFile, namaProgramIni) != 0) {
                pthread_create(&tid[index], NULL, perintahd, (void *)&args);
                printf("%s\n", namaFile);
                sleep(1);
                index++;
            }
        }
    }
    if (!flag) printf("Yah gagal disimpan\n");
    else printf("Direktori sudah disimpan\n");
}

int main(int argc, char* argv[]) 
{ 

    arg_struct args;
    getcwd(args.cwd, sizeof(args.cwd));
  
    if(strcmp(argv[1],"-f")==0)
    {
        int index = 0;
        for (int i = 2; i < argc; i++)
        {
        strcpy(args.ndir, argv[i]);
        pthread_create(&tid[index], NULL, perintahf, (void *)&args);
        sleep(1);
        index++;
        }
        for (int i = 0; i < index; i++) {
            pthread_join(tid[i], NULL);
        }
    }

    else if(strcmp(argv[1],"-d")==0){
        char ndir[max];
        strcpy(ndir, argv[2]);
        sortHere(ndir);
    }

    else if(strcmp(argv[1],"*")==0)
    {
        char ndir[] = "/home/sfayha/soal3/";
        
        sortHere(ndir);
    }
    else
    {
        printf("Argumen Salah\n");
        return 0;
    }
        return 0; 
} 
