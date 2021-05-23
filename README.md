# soal-shift-sisop-modul-3-E07-2021

* Nizar Mayraldo	      05111940000004
* Rihan farih bunyamin	05111940000165 
* Fayha Syifa Qalbi   	05111940000185

### Soal 1
Keverk adalah orang yang cukup ambisius dan terkenal di angkatannya. Sebelum dia menjadi ketua departemen di HMTC, dia pernah mengerjakan suatu proyek dimana keverk tersebut meminta untuk membuat server database buku. Proyek ini diminta agar dapat digunakan oleh pemilik aplikasi dan diharapkan bantuannya dari pengguna aplikasi ini. 

Di dalam proyek itu, Keverk diminta: 
* (a) Pada saat client tersambung dengan server, terdapat dua pilihan pertama, yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. User juga dapat melakukan login. Login berhasil jika id dan password yang dikirim dari aplikasi client sesuai dengan list akun yang ada didalam aplikasi server. Sistem ini juga dapat menerima multi-connections. Koneksi terhitung ketika aplikasi client tersambung dengan server. Jika terdapat 2 koneksi atau lebih maka harus menunggu sampai client pertama keluar untuk bisa melakukan login dan mengakses aplikasinya. Keverk menginginkan lokasi penyimpanan id dan password pada file bernama akun.txt dengan format :
```
akun.txt
id:password
id2:password2
```

* (b)Sistem memiliki sebuah database yang bernama files.tsv. Isi dari files.tsv ini adalah path file saat berada di server, publisher, dan tahun publikasi. Setiap penambahan dan penghapusan file pada folder file yang bernama  FILES pada server akan memengaruhi isi dari files.tsv. Folder FILES otomatis dibuat saat server dijalankan. 
* (c) Tidak hanya itu, Keverk juga diminta membuat fitur agar client dapat menambah file baru ke dalam server. Direktori FILES memiliki struktur direktori kemudian , dari aplikasi client akan dimasukan data buku tersebut (perlu diingat bahwa Filepath ini merupakan path file yang akan dikirim ke server). Lalu client nanti akan melakukan pengiriman file ke aplikasi server dengan menggunakan socket. Ketika file diterima di server, maka row dari files.tsv akan bertambah sesuai dengan data terbaru yang 
ditambahkan.
* (d) Dan client dapat mendownload file yang telah ada dalam folder FILES di server, sehingga sistem harus dapat mengirim file ke client. Server harus melihat dari files.tsv untuk melakukan pengecekan apakah file tersebut valid. Jika tidak valid, maka mengirimkan pesan error balik ke client. Jika berhasil, file akan dikirim dan akan diterima ke client di folder client tersebut. 
* (e) Setelah itu, client juga dapat menghapus file yang tersimpan di server. Akan tetapi, Keverk takut file yang dibuang adalah file yang penting, maka file hanya akan diganti namanya menjadi ‘old-NamaFile.ekstensi’. Ketika file telah diubah namanya, maka row dari file tersebut di file.tsv akan terhapus.
* (f) Client dapat melihat semua isi files.tsv dengan memanggil suatu perintah yang bernama see. Output dari perintah tersebut keluar dengan format
```  
Nama:
Publisher:
Tahun publishing:
Ekstensi File : 
Filepath : 

Nama:
Publisher:
Tahun publishing:
Ekstensi File : 
Filepath : 

```
* (g) Aplikasi client juga dapat melakukan pencarian dengan memberikan suatu string. Hasilnya adalah semua nama file yang mengandung string tersebut. Format output seperti format output
*  (h) Dikarenakan Keverk waspada dengan pertambahan dan penghapusan file di server, maka Keverk membuat suatu log untuk server yang bernama running.log. Contoh isi dari log ini adalah

```
Tambah : File1.ektensi (id:pass)
Hapus : File2.ektensi (id:pass)

```



### soal 2
Crypto (kamu) adalah teman Loba. Suatu pagi, Crypto melihat Loba yang sedang kewalahan mengerjakan tugas dari bosnya. Karena Crypto adalah orang yang sangat menyukai tantangan, dia ingin membantu Loba mengerjakan tugasnya. Detil dari tugas tersebut adalah:
* (a) Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).
* (b) Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (Catatan!: gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang a	da. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya matri(dari paling besar ke paling kecil)
*  (c) Karena takut lag dalam pengerjaannya membantu Loba, Crypto juga membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 | head -5”

#### Jawab
##### 2a
```
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
```
```
int main()
{
        //update
    key_t key = 1234;
      int *value;

      int shmid = shmget(key, sizeof(hasil)*6*4, IPC_CREAT | 0666);
      value = shmat(shmid, NULL, 0);
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
        value[i*6+j]=hasil[i][j];
        }
        printf("\n");
    }
      shmdt(value);
      
      return 0;
}
```
###### hasil:
##### 2b

```
int tes[24];
int *value;
pthread_t thread;
int angka;

typedef struct index
{
  long long lama;
  long long baru;
}indexnya;

unsigned long long faktorial(unsigned long long x, int isi){
  unsigned long long hasil = x;
  if (x==1)
  {
    return 1;
  }
  else if (x==2)
  {
    hasil *=((x-1));
  }
  else if(isi>x){
    for (long long a = 1; a < isi; a++){
      {
        hasil *= (x-a);
      }
    }
  }
  else{
    for (long long a = 0; a < isi; a++)
    {
      if (x-a==0)
      {
        continue;
      }
      else if (x-a>0)
      {
        hasil *=(x-a);
      }
    }
  }
  return hasil;
}
```

```
void *hitungfactorial(void* arg) {

  indexnya *value = (indexnya *)arg;
  unsigned long long hasil;

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
    printf("%llu\t",hasil);
  }
  
  
}

void operasi(){
  for (int i = 0; i < 24; i++)
  {
    if (i%6==0)
    {
      printf("\n");
    }
    indexnya *pointer = (indexnya*)malloc(sizeof(*pointer));

    pointer->lama=value[i];
    pointer->baru=tes[i];

    pthread_create(&thread, NULL, hitungfactorial, (void*)pointer);

    pthread_join(thread,NULL);
  }
}

```

```
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

  printf("\nsetelah faktorial:");

  operasi();
  printf("\n");
  
  shmdt(value);
}
```

###### hasil:
##### 2c
##### Kendala yang dialami
