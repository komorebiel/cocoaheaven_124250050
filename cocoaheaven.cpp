#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

// ================================================
//   COCOA HEAVEN - Sistem Manajemen Toko
// ================================================

#define MAKS_BARANG  100
#define MAKS_NAMA    50

struct Karyawan {
    int  id;
    char nama[MAKS_NAMA];
};

struct Barang {
    char nama[MAKS_NAMA];
    int  harga;
    int  stok;
};

// ----------- PROTOTYPE -----------

void menuUtama();
void loginAdmin();
void menuAdmin();
void menuKaryawan();

// karyawan
bool idSudahAda(int idCek);
void tambahKaryawan();
void lihatKaryawan();
void cariKaryawan();

// barang
void tambahBarang();
void lihatBarang();
void editBarang();
void cariBarang();

// sorting
void bubbleSortAsc(Barang lst[], int jml);
void quickSortDesc(Barang lst[], int bawah, int atas);
int  partisiDesc(Barang lst[], int bawah, int atas);

// searching
void urutNamaAZ(Barang lst[], int jml);
int  sequentialSearch(Barang lst[], int jml, const char cari[]);
int  binarySearch(Barang lst[], int jml, const char cari[]);

// utilitas
void jedaLanjut();

// ================================================
//  MAIN
// ================================================

int main() {
    menuUtama();
    return 0;
}

// ================================================
//  UTILITAS
// ================================================

void jedaLanjut() {
    cout << "Press any key to continue . . . ";
    cin.ignore();
    cin.get();
}

// ================================================
//  MENU UTAMA
// ================================================

void menuUtama() {
    int pilih;

    do {
        cout << "\n=========== WELCOME TO COCOA HEAVEN ===========\n";
        cout << "  1. Login Admin\n";
        cout << "  2. Karyawan\n";
        cout << "  3. Keluar\n";
        cout << "================================================\n";
        cout << "Masukkan pilihan menu: ";
        cin  >> pilih;

        if      (pilih == 1) loginAdmin();
        else if (pilih == 2) menuKaryawan();
        else if (pilih == 3) cout << "\nSampai Jumpa\n\n";
        else                 cout << "\nPilihan tidak tersedia!\n";

    } while (pilih != 3);
}

// ================================================
//  LOGIN ADMIN  (loop sampai benar)
// ================================================

void loginAdmin() {
    char usr[30], sandi[30];

    while (true) {
        cout << "\nMasukkan Username anda: ";
        cin  >> usr;
        cout << "Masukkan Password anda: ";
        cin  >> sandi;

        if (strcmp(usr, "admin") == 0 && strcmp(sandi, "123") == 0) {
            cout << "\nLogin berhasil!\n";
            menuAdmin();
            return;
        } else {
            cout << "\nKamu bukan Admin!\n";
            jedaLanjut();
        }
    }
}

// ================================================
//  MENU ADMIN
// ================================================

void menuAdmin() {
    int pilih;

    do {
        cout << "\n========================\n";
        cout << "        Halo Admin!\n";
        cout << "========================\n";
        cout << "  1. Tambah data karyawan\n";
        cout << "  2. Lihat data karyawan\n";
        cout << "  3. Searching data karyawan\n";
        cout << "  4. Logout\n";
        cout << "========================\n";
        cout << "Pilih menu: ";
        cin  >> pilih;

        if      (pilih == 1) tambahKaryawan();
        else if (pilih == 2) lihatKaryawan();
        else if (pilih == 3) cariKaryawan();
        else if (pilih != 4) cout << "\nPilihan tidak tersedia!\n";

    } while (pilih != 4);
}

// ================================================
//  TAMBAH KARYAWAN  (array + pointer)
// ================================================

// cek apakah ID sudah ada di file karyawan.txt
bool idSudahAda(int idCek) {
    FILE *fp = fopen("karyawan.txt", "r");
    if (fp == NULL) return false;   // file belum ada = belum ada data

    Karyawan k;
    while (fscanf(fp, "%d %s", &k.id, k.nama) != EOF) {
        if (k.id == idCek) {
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

void tambahKaryawan() {
    int jml;

    cout << "\nMasukkan jumlah karyawan: ";
    cin  >> jml;

    if (jml <= 0) {
        cout << "Jumlah tidak valid!\n";
        jedaLanjut();
        return;
    }

    Karyawan data[jml];
    Karyawan *ptr = data;          // pointer ke array

    // input semua data dulu, cek duplikasi sebelum disimpan
    for (int x = 0; x < jml; x++) {
        while (true) {
            cout << "\nID karyawan: ";
            cin  >> (ptr + x)->id;

            // cek duplikasi di file
            if (idSudahAda((ptr + x)->id)) {
                cout << "ID " << (ptr + x)->id << " sudah terdaftar, masukkan ID lain.\n";
                continue;
            }

            // cek duplikasi di input sesi ini (data yang belum tersimpan)
            bool dupSesi = false;
            for (int y = 0; y < x; y++) {
                if ((ptr + y)->id == (ptr + x)->id) {
                    dupSesi = true;
                    break;
                }
            }

            if (dupSesi) {
                cout << "ID " << (ptr + x)->id << " sudah dipakai di input ini, masukkan ID lain.\n";
                continue;
            }

            break;  // ID valid
        }

        cout << "Nama karyawan: ";
        cin  >> (ptr + x)->nama;
    }

    FILE *fp = fopen("karyawan.txt", "a");
    if (fp == NULL) {
        cout << "Gagal membuka file karyawan.txt!\n";
        jedaLanjut();
        return;
    }

    for (int x = 0; x < jml; x++) {
        fprintf(fp, "%d %s\n", (ptr + x)->id, (ptr + x)->nama);
    }

    fclose(fp);
    cout << "\nData berhasil disimpan!\n";
    jedaLanjut();
}

// ================================================
//  LIHAT KARYAWAN
// ================================================

void lihatKaryawan() {
    FILE *fp = fopen("karyawan.txt", "r");

    if (fp == NULL) {
        cout << "\nBelum ada data karyawan.\n";
        jedaLanjut();
        return;
    }

    Karyawan k;
    int urut = 1;

    cout << "\n===== DATA KARYAWAN =====\n";

    while (fscanf(fp, "%d %s", &k.id, k.nama) != EOF) {
        cout << "Karyawan ke-" << urut << "\n";
        cout << "ID   : " << k.id   << "\n";
        cout << "Nama : " << k.nama << "\n\n";
        urut++;
    }

    fclose(fp);
    jedaLanjut();
}

// ================================================
//  CARI KARYAWAN
// ================================================

void cariKaryawan() {
    int kode;

    cout << "\nMasukkan ID karyawan yang dicari: ";
    cin  >> kode;

    FILE *fp = fopen("karyawan.txt", "r");
    if (fp == NULL) {
        cout << "Data tidak tersedia.\n";
        jedaLanjut();
        return;
    }

    Karyawan k;
    bool ketemu = false;

    while (fscanf(fp, "%d %s", &k.id, k.nama) != EOF) {
        if (k.id == kode) {
            cout << "\nData ditemukan!\n";
            cout << "ID   : " << k.id   << "\n";
            cout << "Nama : " << k.nama << "\n";
            ketemu = true;
            break;
        }
    }

    if (!ketemu)
        cout << "\nData tidak ditemukan.\n";

    fclose(fp);
    jedaLanjut();
}

// ================================================
//  MENU KARYAWAN
// ================================================

void menuKaryawan() {
    int pilih;

    do {
        cout << "\n========================\n";
        cout << "      Halo Karyawan!\n";
        cout << "  ========================\n";
        cout << "  1. Tambah data barang\n";
        cout << "  2. Lihat data barang\n";
        cout << "  3. edit data barang\n";
        cout << "  4. cari data barang\n";
        cout << "  5. Logout\n";
        cout << "========================\n";
        cout << "Pilih menu: ";
        cin  >> pilih;

        if      (pilih == 1) tambahBarang();
        else if (pilih == 2) lihatBarang();
        else if (pilih == 3) editBarang();
        else if (pilih == 4) cariBarang();
        else if (pilih != 5) cout << "\nPilihan tidak tersedia!\n";

    } while (pilih != 5);
}

// ================================================
//  TAMBAH BARANG  (array struct + pointer)
// ================================================

void tambahBarang() {
    int jml;

    cout << "\nMasukkan jumlah barang: ";
    cin  >> jml;

    if (jml <= 0) {
        cout << "Jumlah tidak valid!\n";
        jedaLanjut();
        return;
    }

    Barang data[jml];
    Barang *ptr = data;            // pointer ke array struct

    FILE *fp = fopen("barang.txt", "a");
    if (fp == NULL) {
        cout << "Gagal membuka file barang.txt!\n";
        jedaLanjut();
        return;
    }

    for (int x = 0; x < jml; x++) {
        cout << "\nbarang ke- " << x + 1 << "\n";
        cout << "Nama Barang : ";
        cin  >> (ptr + x)->nama;
        cout << "Harga Barang: ";
        cin  >> (ptr + x)->harga;
        cout << "Stok Barang : ";
        cin  >> (ptr + x)->stok;

        fprintf(fp, "%s %d %d\n",
                (ptr + x)->nama,
                (ptr + x)->harga,
                (ptr + x)->stok);
    }

    fclose(fp);
    cout << "\nData berhasil disimpan!\n";
    jedaLanjut();
}

// ================================================
//  LIHAT BARANG  (dengan sorting)
// ================================================

void lihatBarang() {
    FILE *fp = fopen("barang.txt", "r");

    if (fp == NULL) {
        cout << "\nBelum ada data barang.\n";
        jedaLanjut();
        return;
    }

    Barang lst[MAKS_BARANG];
    int jml = 0;

    while (jml < MAKS_BARANG &&
           fscanf(fp, "%s %d %d",
                  lst[jml].nama,
                  &lst[jml].harga,
                  &lst[jml].stok) != EOF) {
        jml++;
    }
    fclose(fp);

    if (jml == 0) {
        cout << "\nData kosong.\n";
        jedaLanjut();
        return;
    }

    int urut;
    cout << "\n  1. Ascending\n";
    cout << "  2. Descending\n";
    cout << "Pilih sorting: ";
    cin  >> urut;

    if      (urut == 1) bubbleSortAsc(lst, jml);
    else if (urut == 2) quickSortDesc(lst, 0, jml - 1);
    else                cout << "\nPilihan tidak valid, tampil urutan asli.\n";

    cout << "\n";
    for (int x = 0; x < jml; x++) {
        cout << "Data barang ke- " << x + 1 << "\n";
        cout << lst[x].nama  << "\n";
        cout << lst[x].harga << "\n";
        cout << lst[x].stok  << "\n";
        cout << "========================\n\n";
    }

    jedaLanjut();
}

// ================================================
//  EDIT BARANG
// ================================================

void editBarang() {
    FILE *fp = fopen("barang.txt", "r");
    if (fp == NULL) {
        cout << "\nData belum tersedia.\n";
        jedaLanjut();
        return;
    }

    Barang lst[MAKS_BARANG];
    int jml = 0;

    while (jml < MAKS_BARANG &&
           fscanf(fp, "%s %d %d",
                  lst[jml].nama,
                  &lst[jml].harga,
                  &lst[jml].stok) != EOF) {
        jml++;
    }
    fclose(fp);

    char cari[MAKS_NAMA];
    cout << "\nMasukkan nama barang yang ingin diedit: ";
    cin  >> cari;

    int posisi = -1;
    for (int x = 0; x < jml; x++) {
        if (strcmp(lst[x].nama, cari) == 0) {
            posisi = x;
            break;
        }
    }

    if (posisi == -1) {
        cout << "\nData tidak ditemukan.\n";
        jedaLanjut();
        return;
    }

    cout << "\nData ditemukan!\n";
    cout << "Nama  : " << lst[posisi].nama  << "\n";
    cout << "Harga : " << lst[posisi].harga << "\n";
    cout << "Stok  : " << lst[posisi].stok  << "\n";

    cout << "\nMasukkan data baru\n";
    cout << "Nama Barang : ";
    cin  >> lst[posisi].nama;
    cout << "Harga Barang: ";
    cin  >> lst[posisi].harga;
    cout << "Stok Barang : ";
    cin  >> lst[posisi].stok;

    fp = fopen("barang.txt", "w");
    if (fp == NULL) {
        cout << "\nGagal menyimpan perubahan!\n";
        jedaLanjut();
        return;
    }

    for (int x = 0; x < jml; x++) {
        fprintf(fp, "%s %d %d\n",
                lst[x].nama,
                lst[x].harga,
                lst[x].stok);
    }
    fclose(fp);

    cout << "\nData berhasil diupdate!\n";
    jedaLanjut();
}

// ================================================
//  CARI BARANG
// ================================================

void cariBarang() {
    FILE *fp = fopen("barang.txt", "r");
    if (fp == NULL) {
        cout << "\nData belum tersedia.\n";
        jedaLanjut();
        return;
    }

    Barang lst[MAKS_BARANG];
    int jml = 0;

    while (jml < MAKS_BARANG &&
           fscanf(fp, "%s %d %d",
                  lst[jml].nama,
                  &lst[jml].harga,
                  &lst[jml].stok) != EOF) {
        jml++;
    }
    fclose(fp);

    if (jml == 0) {
        cout << "\nData kosong.\n";
        jedaLanjut();
        return;
    }

    int metode;
    cout << "\n  1. Sequential Search\n";
    cout << "  2. Binary Search\n";
    cout << "Pilih metode: ";
    cin  >> metode;

    char cari[MAKS_NAMA];
    cout << "Masukkan nama barang: ";
    cin  >> cari;

    int posisi = -1;

    if (metode == 1) {
        posisi = sequentialSearch(lst, jml, cari);
    } else if (metode == 2) {
        urutNamaAZ(lst, jml);
        posisi = binarySearch(lst, jml, cari);
    } else {
        cout << "\nPilihan tidak valid.\n";
        jedaLanjut();
        return;
    }

    if (posisi != -1) {
        cout << "\nBarang ditemukan!\n";
        cout << "Nama  : " << lst[posisi].nama  << "\n";
        cout << "Harga : " << lst[posisi].harga << "\n";
        cout << "Stok  : " << lst[posisi].stok  << "\n";
    } else {
        cout << "\nBarang tidak ditemukan.\n";
    }

    jedaLanjut();
}

// ================================================
//  BUBBLE SORT  - harga naik (ascending)
// ================================================

void bubbleSortAsc(Barang lst[], int jml) {
    for (int i = 0; i < jml - 1; i++) {
        for (int j = 0; j < jml - i - 1; j++) {
            if (lst[j].harga > lst[j + 1].harga) {
                Barang tmp  = lst[j];
                lst[j]      = lst[j + 1];
                lst[j + 1]  = tmp;
            }
        }
    }
}

// ================================================
//  QUICK SORT  - harga turun (descending)
// ================================================

int partisiDesc(Barang lst[], int bawah, int atas) {
    int pivot = lst[atas].harga;
    int kiri  = bawah - 1;

    for (int k = bawah; k < atas; k++) {
        if (lst[k].harga > pivot) {
            kiri++;
            Barang tmp   = lst[kiri];
            lst[kiri]    = lst[k];
            lst[k]       = tmp;
        }
    }

    Barang tmp     = lst[kiri + 1];
    lst[kiri + 1]  = lst[atas];
    lst[atas]      = tmp;

    return kiri + 1;
}

void quickSortDesc(Barang lst[], int bawah, int atas) {
    if (bawah < atas) {
        int tengah = partisiDesc(lst, bawah, atas);
        quickSortDesc(lst, bawah, tengah - 1);
        quickSortDesc(lst, tengah + 1, atas);
    }
}

// ================================================
//  SORT NAMA A-Z  (untuk binary search)
// ================================================

void urutNamaAZ(Barang lst[], int jml) {
    for (int i = 0; i < jml - 1; i++) {
        for (int j = 0; j < jml - i - 1; j++) {
            if (strcmp(lst[j].nama, lst[j + 1].nama) > 0) {
                Barang tmp  = lst[j];
                lst[j]      = lst[j + 1];
                lst[j + 1]  = tmp;
            }
        }
    }
}

// ================================================
//  SEQUENTIAL SEARCH
// ================================================

int sequentialSearch(Barang lst[], int jml, const char cari[]) {
    for (int x = 0; x < jml; x++) {
        if (strcmp(lst[x].nama, cari) == 0)
            return x;
    }
    return -1;
}

// ================================================
//  BINARY SEARCH
// ================================================

int binarySearch(Barang lst[], int jml, const char cari[]) {
    int kiri  = 0;
    int kanan = jml - 1;

    while (kiri <= kanan) {
        int tengah = (kiri + kanan) / 2;
        int cek    = strcmp(lst[tengah].nama, cari);

        if      (cek == 0) return tengah;
        else if (cek  < 0) kiri  = tengah + 1;
        else               kanan = tengah - 1;
    }

    return -1;
}
