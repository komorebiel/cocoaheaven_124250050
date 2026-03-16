# cocoaheaven_124250050
Sistem manajemen toko berbasis C++ console yang menangani pengelolaan data karyawan dan barang di toko Cocoa Heaven. Dibangun sebagai implementasi praktis dari konsep-konsep dasar pemrograman seperti struct, pointer, array, file handling, serta algoritma sorting dan searching.

Terdapat dua hak akses dalam sistem ini. Admin masuk melalui proses login dan bertanggung jawab atas data karyawan, mulai dari menambah, melihat, hingga mencari berdasarkan ID. Sementara karyawan dapat langsung mengakses pengelolaan data barang, termasuk menambah, melihat, mengedit, dan mencari barang yang tersedia.

Seluruh data disimpan secara persisten ke file eksternal. Data karyawan ditulis ke karyawan.txt dan data barang ke barang.txt menggunakan fungsi file handling C-style (fopen, fscanf, fprintf, fclose).

Algoritma yang diimplementasikan dalam program ini meliputi:
- Bubble Sort untuk menampilkan data barang dari harga termurah (ascending)
- Quick Sort untuk menampilkan data barang dari harga termahal (descending)
- Sequential Search untuk pencarian data barang secara linear
- Binary Search untuk pencarian data barang setelah data diurutkan secara alfabetis

Project ini dikerjakan sebagai tugas kuliah pada mata kuliah Algoritma dan Struktur Data, dengan tujuan mengasah pemahaman terhadap penerapan konsep-konsep tersebut dalam sebuah program yang fungsional.
