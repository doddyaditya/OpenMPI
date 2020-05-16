# I. Petunjuk penggunaan program
    mpicc dijkstra.c -o [nama executable program]
    mpirun -np [process] [nama executable program] [jumlah node: 100, 500, 1000, 3000]
    
# II. Laporan pengerjaan
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

