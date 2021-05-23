# soal-shift-sisop-modul-3-E07-2021

* Nizar Mayraldo	      05111940000004
* Rihan farih bunyamin	05111940000165 
* Fayha Syifa Qalbi   	05111940000185

## Soal
1. [soal2a](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021#2a)
2. [soal2b](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021#2b)
3. [soal2c](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021#2c)
4. [soal3](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021#soal-3)

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
```

Pertama deklarasikan dulu variabel global untuk memuat matriks A, B, dan hasil dari perkalian sekaligus struct untuk menunjuk index arraynya nanti.

```
void *operasi(void* arg){
    int i =((struct index*)arg)->i;
    int j =((struct index*)arg)->j;

    for (int x = 0; x < 3; x++) {
        hasil[i][j] += MA[i][x] * MB[x][j];
    }
}

```

pada fungsi operasi digunakan untuk memproses perkalian dari matariks A dan B menggunakan for dan dimasukkan ke array hasil. menggunakan fungsi struct dan argumen untuk menunjuk alamat array yang akan dioperasikan. Fungsi ini juga berguna pada proses thread sebagai argumen fungsi yang dijalankan.

```

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

kemudian fungsi input matriks sesuai pada soal yaitu array dimasukkan pada program sehingga meminta kita untuk menginput fungsi pada program saat dijalankan. Pada for di loop pertama dan cabangnya berfungsi untuk input nilai pada matriks A dan pada for kedua digunakan utuk menginput nilai pada matriks B.

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

pada fungsi main di awal deklarasikan dulu share memory untuk digunakan pada soal 2b. kemudian pthread digunakan untuk memproses hasil perkalian menggunakan thread sesuai dengan matriks hasil perkaliannya. Setelah itu dijalan fungsi inputmatriks untuk untuk menginput matriks A dan B, dengan menggunakan for disesuaikan dengan bentuk matriks hasilnya menggunakan struct index untuk menunjuk index matriks pada array dan menggunakan fungsi pthread join dengan tid yang sudah disesuaikan dan menggunakan fungsi operasi sebagai argumen fungsi juga void ke untuk argumen pada fungsi operasi sebagai nilai. Kemudian di akhir menampilkan hasil perkalian matriks dan memasukkan ke variabel pointer value agar dapat digunakan pada soal 2b sebagai jawaban dari share memory.

###### hasil:

![nomor2a](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021/blob/main/Screenshots/2a.png)

##### 2b

```
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

typedef struct index
{
  long long lama;
  long long baru;
}indexnya;
```

Pertama deklarasikan dulu variabel global untuk memuat tes yaitu matriks penguji faktorial, thread untuk memproses, dan int pointer value untuk mengambil nilai dari jawaban 2a, dan struct indexnya lama untuk nilai dari soal 2a dan baru sebagai batas faktorial nya.

```
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

kemudian pada faktorial ini digunakan untuk menghitung nilai, isi sebagai berapa banyak angka faktorial pertama yang ingin didapatkan dan x sebagai matriks dari soal 2a yang akan digunakan.

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

```

Pada fungsi ini digunakan untuk memanggil fungsi faktorial untuk menghitung, dan di soal dituliskan jika data 0 maka memunculkan nilai 0, begitu pula pada batasnya. Kemudian fungsi indexnya digunakan untuk menunjuk index value yaitu lama untuk matriks pada soal 2a dan baru adalah matriks penguji faktorialnya yang berarti mengimbil berapa kali faktorial pertama dari matriks soal 2a, kemudian variabel hasil untuk memuat hasil dari proses faktorialnya.

```

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

pada fungsi operasi digunakan untuk menghitung faktorial yang sudah dibuat dari 2 fungsi di atas, pointer lama digunakan untuk value dari hasil matriks 2a dan pointer bari tes adalah matriks pengujinya. Kemudian menjalankan fungsi thread dengan &thread di awal yang sudah didekrasikan dengan parameter NULL, dan menggunakan fungsi hitungfactorial sebagai argumen fungsi menghitung dan void pointer untuk menunjuk argumen nilai yang akan dioperasikan.

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

Di awal menggunakan fungsi share memory untuk menggunakan alamat memori yang sama pada soal 2a  dan mengambil value yang merupakan hasil dari perkalian di soal 2a sehingga hasil perkalian matriks tadi bisa digunakan sebagai matriks A pada soal. Setelah itu menggunakan for loop untuk menginput array penguji faktorial nya atau pada soal disebut sebagai matriks B. Kemudian untuk mengecek apakah sudah menggunakan memori yang sama di sini saya menampilkan output dari matriks sebelumnya yang disimpan pada variabel value. Untuk menampilkan array yang lurus tadi menjadi matriks 4 x 6 maka saya menggunakan index i x 6+j agar sesuai dengan output pada soal 2a. setelah itu memanggil fungsi operasi untuk menjalankan faktorial yang diminta pada soal.

###### hasil:

![nomor2a](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021/blob/main/Screenshots/2b.png)

##### 2c

###### hasil:

##### Kendala yang dialami
*kesulitan dalam memahami menggunkan fungsi dan algoritma apa pada soal apa
*tingkat soal yang lebih sulit dari materi dan contoh soal
*sering error tidak jelas pada program

### soal 3
Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
contoh program ketika dijalankan:
```
# Program soal3 terletak di /home/izone/soal3
$ ./soal3 -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
|-jpg
|--file1.jpg
|-c
|--file2.c
|-zip
|--file3.zip

```
* (a) Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna. 
Output yang dikeluarkan adalah seperti ini :
```
File 1 : Berhasil Dikategorikan (jika berhasil)
File 2 : Sad, gagal :( (jika gagal)
File 3 : Berhasil Dikategorikan
```
* (b) Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin. Contohnya adalah seperti ini:
```

$ ./soal3 -d /path/to/directory/

```
Perintah di atas akan mengkategorikan file di /path/to/directory, lalu hasilnya akan disimpan di working directory dimana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory).
Output yang dikeluarkan adalah seperti ini :
```
Jika berhasil, print “Direktori sukses disimpan!”
Jika gagal, print “Yah, gagal disimpan :(“

```
* (c) Selain menerima opsi-opsi di atas, program ini menerima opsi *, contohnya ada di bawah ini:
`$ ./soal3 \* `

Opsi ini akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut.

* (d) Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”.
* (e) Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

#### jawaban
Source Code : 

* (a) Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna. 
```
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
```
Pada __-f__ di perlukan fungsi fmove dan perintahf untuk menjalankannya. Kemudian di fungsi main pthread_create dan pthread_join dibuat untuk setiap path yang diinputkan. 

* (b) Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin. Pada kondisi ini digunakan strcmp untuk membandingkan argumen input apakah sesuai dengan argumen input yang diminta yaitu -d. Command -d akan dilaksanakan jika hanya memasukkan 1 path saja.

```
 else if(strcmp(argv[1],"-d")==0){
        char ndir[max];
        strcpy(ndir, argv[2]);
        cek(ndir);
```
Pada __-d__ diperlukan fungsi fsmove dan perintahd.Selain itu, sebelum masuk ke fungsi-fungsi tersebut, folder yang ingin dikelompokkan terlebih dahulu dibaca file per filenya melalui fungsi cek, yaitu sebagai berikut :

```
...
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
...
```


* (c) Selain menerima opsi-opsi di atas, program ini menerima opsi *, Opsi ini akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut.
```
...
else if(strcmp(argv[1],"*")==0)
    {
        char ndir[] = "/home/sfayha/soal3/";
        
        cek(ndir);
    }
...
```
Pada kondisi ini fungsi yang diperlukan sama dengan proses -d, hanya saja, alamat folder yang dikirim adalah alamat current working directorynya.

* (d) Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. 
* (e) Jika file hidden, masuk folder “Hidden”. Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

###### hasil:
![-f](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021/blob/main/Screenshots/-f.png)
![-d](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021/blob/main/Screenshots/-d.png)
![*](https://github.com/rihanfarih/soal-shift-sisop-modul-3-E07-2021/blob/main/Screenshots/*.png)

###### Kendala:
* Tingkat kesulitan soal sangat meningkat
* Terjadi beberapa kali error segmentation fault dan missing files

