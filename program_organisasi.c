#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum untuk jabatan dosen
enum jabatan { Asisten, Dosen_Muda, Dosen_Senior };

// Struktur untuk menyimpan data dosen
struct Dosen {
    char nama[50];
    int usia;
    enum jabatan
     jabatanDosen;
    float gaji;
};

// Union untuk menyimpan data dosen
union Data {
    struct Dosen dosen;
};

// Fungsi untuk memasukkan data dosen
void inputDosenData(union Data *data) {
    printf("Masukkan nama dosen: ");
    scanf(" %[^\n]", data->dosen.nama);  // Input nama
    printf("Masukkan usia dosen: ");
    scanf("%d", &data->dosen.usia);      // Input usia
    printf("Masukkan jabatan (0=Asisten, 1=Dosen Muda, 2=Dosen Senior): ");
    scanf("%d", &data->dosen.jabatanDosen);  // Input jabatan
    printf("Masukkan gaji dosen: ");
    scanf("%f", &data->dosen.gaji);  // Input gaji
}

// Fungsi untuk menampilkan data dosen
void tampilkanDosenData(union Data data) {
    printf("\nData Dosen:\n");
    printf("Nama: %s\n", data.dosen.nama);
    printf("Usia: %d\n", data.dosen.usia);

    // Menampilkan jabatan dosen berdasarkan enum
    switch (data.dosen.jabatanDosen) {
        case Asisten:
            printf("Jabatan: Asisten\n");
            break;
        case Dosen_Muda:
            printf("Jabatan: Dosen Muda\n");
            break;
        case Dosen_Senior:
            printf("Jabatan: Dosen Senior\n");
            break;
        default:
            printf("Jabatan: Tidak diketahui\n");
    }

    printf("Gaji: %.2f\n", data.dosen.gaji);
}

// Fungsi untuk menambahkan dosen
void tambahDosen(union Data **dataList, int *count) {
    union Data *tempList;  // Pointer sementara untuk data baru

    // Mengalokasikan memori baru untuk array yang lebih besar
    tempList = (union Data *)malloc((*count + 1) * sizeof(union Data));
    if (tempList == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        exit(1);
    }

    // Menyalin data lama ke dalam array baru
    for (int i = 0; i < *count; i++) {
        tempList[i] = (*dataList)[i];
    }

    // Memasukkan data dosen baru
    printf("Menambah data dosen:\n");
    inputDosenData(&tempList[*count]);  // Memasukkan data dosen baru

    // Membebaskan memori dari list lama
    free(*dataList);

    // Mengupdate pointer dataList untuk menunjuk ke array yang baru
    *dataList = tempList;
    (*count)++;  // Increment jumlah dosen
}

// Fungsi untuk menampilkan semua data dosen
void tampilkanSemuaDosen(union Data *dataList, int count) {
    if (count == 0) {
        printf("Tidak ada data dosen.\n");
        return;
    }

    printf("\nDaftar Dosen:\n");
    for (int i = 0; i < count; i++) {
        printf("\nDosen %d:\n", i + 1);
        tampilkanDosenData(dataList[i]);
    }
}

// Fungsi untuk memperbarui data dosen
void updateDosen(union Data *dataList, int count) {
    int index;
    printf("Masukkan nomor dosen yang ingin diperbarui (1-%d): ", count);
    scanf("%d", &index);
    index--;  // Mengubah ke index array (dimulai dari 0)

    if (index < 0 || index >= count) {
        printf("Dosen tidak ditemukan.\n");
        return;
    }

    printf("Memperbarui data dosen nomor %d:\n", index + 1);
    inputDosenData(&dataList[index]);  // Mengupdate data dosen
}

// Fungsi untuk menghapus data dosen
void hapusDosen(union Data **dataList, int *count) {
    int index;
    printf("Masukkan nomor dosen yang ingin dihapus (1-%d): ", *count);
    scanf("%d", &index);
    index--;  // Mengubah ke index array (dimulai dari 0)

    if (index < 0 || index >= *count) {
        printf("Dosen tidak ditemukan.\n");
        return;
    }

    // Menggeser data dosen setelah yang dihapus
    for (int i = index; i < *count - 1; i++) {
        (*dataList)[i] = (*dataList)[i + 1];
    }

    // Membebaskan memori dari list lama
    union Data *tempList = (union Data *)malloc((*count - 1) * sizeof(union Data));
    if (tempList == NULL) {
        printf("Gagal mengalokasikan memori.\n");
        exit(1);
    }

    // Menyalin data yang sudah digeser ke array baru
    for (int i = 0; i < *count - 1; i++) {
        tempList[i] = (*dataList)[i];
    }

    // Membebaskan memori list lama
    free(*dataList);

    // Mengupdate pointer dataList untuk menunjuk ke array yang baru
    *dataList = tempList;
    (*count)--;  // Decrement jumlah dosen
    printf("Dosen nomor %d telah dihapus.\n", index + 1);
}

int main() {
    union Data *dataList = NULL;  // Pointer ke list data dosen
    int count = 0;  // Jumlah dosen

    int pilihan;
    do {
        printf("\nMenu CRUD Dosen:\n");
        printf("1. Tambah Dosen\n");
        printf("2. Tampilkan Semua Dosen\n");
        printf("3. Update Data Dosen\n");
        printf("4. Hapus Data Dosen\n");
        printf("5. Keluar\n");
        printf("Pilih opsi (1-5): ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahDosen(&dataList, &count);
                break;
            case 2:
                tampilkanSemuaDosen(dataList, count);
                break;
            case 3:
                updateDosen(dataList, count);
                break;
            case 4:
                hapusDosen(&dataList, &count);
                break;
            case 5:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 5);

    // Membebaskan memori sebelum keluar
    free(dataList);

    return 0;
}
