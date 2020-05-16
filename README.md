# Announcement

Beberapa file yang harus ada dalam repositori tersebut diantaranya:
* Direktori src yang berisi source code yang anda buat.
* File output yang berisi hasil uji dijkstra algorithm pada data uji.
* Makefile. Buatlah sehingga kompilasi program dapat dilakukan hanya dengan pemanggilan command ’make’ saja.
* File README.md yang berisi:
    * Petunjuk penggunaan program.
    * Pembagian tugas. Sampaikan dalam list pengerjaan untuk setiap mahasiswa. Sebagai contoh: XXXX mengerjakan fungsi YYYY, ZZZZ, dan YYZZ.
    * Laporan pengerjaan, dengan struktur laporan sesuai dengan deskripsi pada bagian sebelumnya.


# I. Petunjuk penggunaan program
    mpicc dijkstra.c -o [nama executable program]
    mpirun -np [process] [nama executable program] [jumlah node: 100, 500, 1000, 3000]

# II. Pembagian tugas
*  13517008 mengerjakan fungsi chooseNode, dijkstra
*  13517143 mengerjakan fungsi initGraf, initGraf2, initGraf3, printGraf, randomNumber, free2dint, main program

# III. Laporan pengerjaan
1.  Deskripsi solusi paralel<br/>
    Solusi yang digunakan adalah dengan menggunakan MPI Scatter yang akan membagi semua node dengan jumlah size processor yang digunakan misal ada 100 
    node maka processor yang dibutuhkan adalah bilangan yang bisa membagi habis 100 node tersebut, kemudian graph matriks awal dibroadcast ke semua process menggunakan MPI Broadcast dan hasil dijkstra dari setiap process dikumpulkan dengan menggunakan MPI Gather.

2.  Analisis solusi<br/>
    Solusi secara paralel menurut kami lebih cepat dibandingkan serial karena memaksimalkan jumlah processor yang ada untuk mengerjakan beberapa task.

3.  Jumlah thread yang digunakan<br/> 
    Jumlah thread yang digunakan adalah nilai yang dapat membagi habis jumlah node, dengan maksimal jumlah thread adalah 8 pada lokal, dan maksimal
    7 pada server.

4.  Pengukuran kinerja untuk tiap kasus uji (jumlah N pada graf) dibandingkan dengan dijkstra algorithm serial<br/>
    1. Node 100 :
     *  Serial : 18,711 ms
     *  Paralel, 5 thread : 13,003 ms
    2. Node 500 :
     *  Serial : 1058,18 ms
     *  Paralel, 5 thread: 401,895 ms
    3. Node 1000 :
     *  Serial : 8085,256 ms
     *  Paralel, 5 thread:  3071,912 ms
    4. Node 3000 :
     *  Serial : 220451,260 ms
     *  Paralel, 5 thread: 91620,524 ms
    <br/>
5.  Analisis perbandingan kinerja serial dan paralel<br/>
    Berdasarkan hasil setiap kasus uji menunjukkan bahwa algoritma paralel yang diterapkan lebih cepat dibandingkan dengan algoritma secara serial.

