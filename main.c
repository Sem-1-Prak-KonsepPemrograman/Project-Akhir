#include <stdio.h>
#include <string.h>

// Struktur untuk menyimpan data mahasiswa
struct mahasiswa {
    int nrp;                       // Nomor Registrasi Pokok mahasiswa
    char nama[50];                 // Nama mahasiswa
    int nilai[4];                  // Array untuk menyimpan nilai evaluasi (0-2) dan UAS (3)
                                   // nilai[0] = evaluasi 1, nilai[1] = evaluasi 2,
                                   // nilai[2] = evaluasi 3, nilai[3] = UAS
    float total;                   // Total dari seluruh nilai mahasiswa
    float rataRata;                // Rata-rata nilai mahasiswa
    char nilaiHuruf[2];            // Nilai huruf (A, B, C, dst.)
    float nilaiAngka;              // Nilai angka (4.0, 3.5, dst.)
    char kategori[20];             // Kategori nilai (Istimewa, Sangat Baik, dst.)
    int maks;                      // Nilai tertinggi
    int min;                       // Nilai terendah
} data_mhs[100], all_mhs;          // Array data mahasiswa, all_mhs digunakan untuk kalkulasi umum

// Struktur untuk menyimpan informasi tentang nilai tertinggi dan terendah
struct all_mhs {
    char nama_T[50];               // Nama mahasiswa dengan nilai tertinggi
    char nama_R[50];               // Nama mahasiswa dengan nilai terendah
    float tinggi;                  // Nilai tertinggi
    float rendah;                  // Nilai terendah
} rataRata, eval_1, eval_2, eval_3, uas; // Digunakan untuk berbagai evaluasi

int index = 0; // Indeks mahasiswa (jumlah data yang telah dimasukkan)

// Fungsi untuk memasukkan data mahasiswa
void inputDataMhs(struct mahasiswa *data_mhs) {
    char pilihan;

    do {
        // Input data untuk satu mahasiswa
        printf("Data mahasiswa ke-%d\n", index + 1);
        printf("Masukkan NRP: ");
        scanf("%d", &data_mhs[index].nrp);
        fflush(stdin); // Membersihkan buffer input

        printf("Masukkan Nama: ");
        fgets(data_mhs[index].nama, sizeof(data_mhs[index].nama), stdin);
        data_mhs[index].nama[strcspn(data_mhs[index].nama, "\n")] = '\0'; // Menghapus karakter newline

        // Input nilai evaluasi dan menghitung total
        for (int i = 0; i < 3; i++) {
            printf("Masukkan nilai evaluasi ke-%d: ", i + 1);
            scanf("%d", &data_mhs[index].nilai[i]);
            data_mhs[index].rataRata += data_mhs[index].nilai[i];
        }
        printf("Masukkan nilai UAS: ");
        scanf("%d", &data_mhs[index].nilai[3]);
        data_mhs[index].rataRata += data_mhs[index].nilai[3];

        // Menghitung rata-rata
        data_mhs[index].rataRata /= 4.0;
        all_mhs.total += data_mhs[index].rataRata;

        // Menentukan nilai huruf berdasarkan rata-rata
        cekNilaiHuruf(data_mhs, index);

        // Menentukan nilai maksimum dan minimum
        data_mhs[index].maks = data_mhs[index].nilai[0];
        data_mhs[index].min = data_mhs[index].nilai[0];
        for (int i = 1; i < 4; i++) { // Iterasi untuk mencari max dan min
            if (data_mhs[index].maks < data_mhs[index].nilai[i]) {
                data_mhs[index].maks = data_mhs[index].nilai[i];
            }
            if (data_mhs[index].min > data_mhs[index].nilai[i]) {
                data_mhs[index].min = data_mhs[index].nilai[i];
            }
        }

        // Tanya apakah ingin memasukkan data lagi
        printf("Masukkan data lagi? (y/n): ");
        scanf(" %c", &pilihan);
        while (getchar() != '\n'); // Membersihkan buffer input
        printf("-----------------------------------------------\n\n");
        index++; // Menambah indeks mahasiswa
    } while (pilihan == 'y'); // Loop bila pilihan 'y'
}

// Fungsi untuk menentukan nilai huruf, angka, dan kategori
void cekNilaiHuruf(struct mahasiswa *data_mhs, int index) {
    if(data_mhs[index].rataRata <= 100 && data_mhs[index].rataRata >= 86){
        strcpy(data_mhs[index].nilaiHuruf, "A"); //menyalin A ke variabel nilaiHuruf
        data_mhs[index].nilaiAngka = 4;
        strcpy(data_mhs[index].kategori, "Istimewa"); //menyalin "Istimewa" ke variabel "kategori"
    }
    else if(data_mhs[index].rataRata >= 81){
        strcpy(data_mhs[index].nilaiHuruf, "A-");
        data_mhs[index].nilaiAngka = 3.75;
        strcpy(data_mhs[index].kategori, "Istimewa");
    }
    else if(data_mhs[index].rataRata >= 76){
        strcpy(data_mhs[index].nilaiHuruf, "AB");
        data_mhs[index].nilaiAngka = 3.5;
        strcpy(data_mhs[index].kategori, "Sangat Baik");
    }
    else if(data_mhs[index].rataRata >= 71){
        strcpy(data_mhs[index].nilaiHuruf, "B+");
        data_mhs[index].nilaiAngka = 3.25;
        strcpy(data_mhs[index].kategori, "Sangat Baik");
    }
    else if(data_mhs[index].rataRata >= 66){
        strcpy(data_mhs[index].nilaiHuruf, "B");
        data_mhs[index].nilaiAngka = 3;
        strcpy(data_mhs[index].kategori, "Baik");
    }
    else if(data_mhs[index].rataRata >= 61){
        strcpy(data_mhs[index].nilaiHuruf, "BC");
        data_mhs[index].nilaiAngka = 2.5;
        strcpy(data_mhs[index].kategori, "Cukup Baik");
    }
    else if(data_mhs[index].rataRata >= 56){
        strcpy(data_mhs[index].nilaiHuruf, "C");
        data_mhs[index].nilaiAngka = 2;
        strcpy(data_mhs[index].kategori, "Cukup");
    }
    else if(data_mhs[index].rataRata >= 41){
        strcpy(data_mhs[index].nilaiHuruf, "D");
        data_mhs[index].nilaiAngka = 1;
        strcpy(data_mhs[index].kategori, "Kurang");
    }
    else if(data_mhs[index].rataRata >= 0){
        strcpy(data_mhs[index].nilaiHuruf, "E");
        data_mhs[index].nilaiAngka = 0;
        strcpy(data_mhs[index].kategori, "Sangat Kurang");
    }
}

// Fungsi untuk menampilkan data mahasiswa dan statistik
void tampilkanNilai(struct mahasiswa *data_mhs) {
    // Header tabel
    printf("No.\tNRP\t\tNama\t\t\tEval 1\tEval 2\tEval 3\tUAS\tRata-rata\tMax\tMin\tHuruf\n");
    printf("----------------------------------------------------------------------------------------------------------------------\n");

    // Menampilkan setiap mahasiswa
    for (int i = 0; i < index; i++) {
        printf("%d\t%d\t\t%s\t\t\t%d\t%d\t%d\t%d\t%.2f\t\t%d\t%d\t%s\n", i + 1, data_mhs[i].nrp,
                                                                                data_mhs[i].nama,
                                                                                data_mhs[i].nilai[0],
                                                                                data_mhs[i].nilai[1],
                                                                                data_mhs[i].nilai[2],
                                                                                data_mhs[i].nilai[3],
                                                                                data_mhs[i].rataRata,
                                                                                data_mhs[i].maks,
                                                                                data_mhs[i].min,
                                                                                data_mhs[i].nilaiHuruf);
    }

    printf("\n\n\n----------------------------------------------------------------------------------------------------------------------\n");

    // Menghitung rata-rata seluruh nilai mahasiswa dengan membagi total nilai dengan jumlah data
    all_mhs.rataRata = all_mhs.total / index;

    // Mencari nilai rata-rata tertinggi dan terendah
    // Inisialisasi nilai tertinggi dan terendah menggunakan data mahasiswa pertama
    rataRata.tinggi = data_mhs[0].rataRata;
    rataRata.rendah = data_mhs[0].rataRata;
    strcpy(rataRata.nama_T, data_mhs[0].nama); // Menyalin nama mahasiswa ke nama_T (tertinggi)
    strcpy(rataRata.nama_R, data_mhs[0].nama); // Menyalin nama mahasiswa ke nama_R (terendah)

    // Loop untuk membandingkan rata-rata masing-masing mahasiswa
    for (int i = 0; i < index - 1; i++) {
        if (rataRata.tinggi < data_mhs[i + 1].rataRata) {
            rataRata.tinggi = data_mhs[i + 1].rataRata;
            strcpy(rataRata.nama_T, data_mhs[i + 1].nama);
        }
        if (rataRata.rendah > data_mhs[i + 1].rataRata) {
            rataRata.rendah = data_mhs[i + 1].rataRata;
            strcpy(rataRata.nama_R, data_mhs[i + 1].nama);
        }
    }

    // Mencari nilai tertinggi dan terendah untuk Eval 1
    eval_1.tinggi = data_mhs[0].nilai[0];
    eval_1.rendah = data_mhs[0].nilai[0];
    strcpy(eval_1.nama_T, data_mhs[0].nama);
    strcpy(eval_1.nama_R, data_mhs[0].nama);
    for (int i = 0; i < index - 1; i++) {
        if (eval_1.tinggi < data_mhs[i + 1].nilai[0]) {
            eval_1.tinggi = data_mhs[i + 1].nilai[0];
            strcpy(eval_1.nama_T, data_mhs[i + 1].nama);
        }
        if (eval_1.rendah > data_mhs[i + 1].nilai[0]) {
            eval_1.rendah = data_mhs[i + 1].nilai[0];
            strcpy(eval_1.nama_R, data_mhs[i + 1].nama);
        }
    }

    // Mencari nilai tertinggi dan terendah untuk Eval 2
    eval_2.tinggi = data_mhs[0].nilai[1];
    eval_2.rendah = data_mhs[0].nilai[1];
    strcpy(eval_2.nama_T, data_mhs[0].nama);
    strcpy(eval_2.nama_R, data_mhs[0].nama);
    for (int i = 0; i < index - 1; i++) {
        if (eval_2.tinggi < data_mhs[i + 1].nilai[1]) {
            eval_2.tinggi = data_mhs[i + 1].nilai[1];
            strcpy(eval_1.nama_T, data_mhs[i + 1].nama);
        }
        if (eval_2.rendah > data_mhs[i + 1].nilai[1]) {
            eval_2.rendah = data_mhs[i + 1].nilai[1];
            strcpy(eval_2.nama_R, data_mhs[i + 1].nama);
        }
    }

    // Mencari nilai tertinggi dan terendah untuk Eval 3
    eval_3.tinggi = data_mhs[0].nilai[2];
    eval_3.rendah = data_mhs[0].nilai[2];
    strcpy(eval_3.nama_T, data_mhs[0].nama);
    strcpy(eval_3.nama_R, data_mhs[0].nama);
    for (int i = 0; i < index - 1; i++) {
        if (eval_3.tinggi < data_mhs[i + 1].nilai[2]) {
            eval_3.tinggi = data_mhs[i + 1].nilai[2];
            strcpy(eval_1.nama_T, data_mhs[i + 1].nama);
        }
        if (eval_3.rendah > data_mhs[i + 1].nilai[2]) {
            eval_3.rendah = data_mhs[i + 1].nilai[2];
            strcpy(eval_3.nama_R, data_mhs[i + 1].nama);
        }
    }

    // Mencari nilai tertinggi dan terendah untuk UAS
    uas.tinggi = data_mhs[0].nilai[3];
    uas.rendah = data_mhs[0].nilai[3];
    strcpy(uas.nama_T, data_mhs[0].nama);
    strcpy(uas.nama_R, data_mhs[0].nama);
    for (int i = 0; i < index - 1; i++) {
        if (uas.tinggi < data_mhs[i + 1].nilai[3]) {
            uas.tinggi = data_mhs[i + 1].nilai[3];
            strcpy(uas.nama_T, data_mhs[i + 1].nama);
        }
        if (uas.rendah > data_mhs[i + 1].nilai[3]) {
            uas.rendah = data_mhs[i + 1].nilai[3];
            strcpy(uas.nama_R, data_mhs[i + 1].nama);
        }
    }

    // Menampilkan hasil rata-rata dan data nilai tertinggi/terendah untuk setiap evaluasi
    printf("Nilai rata-rata seluruh mahasiswa:\t\t%.2f\n", all_mhs.rataRata);
    printf("Nilai Mahasiswa tertinggi:\t\t\t%s dengan nilai %.2f\n", rataRata.nama_T, rataRata.tinggi);
    printf("Nilai Mahasiswa terendah:\t\t\t%s dengan nilai %.2f\n\n", rataRata.nama_R, rataRata.rendah);

    printf("Nilai Mahasiswa dengan Eval 1 tertinggi:\t%s dengan nilai %.0f\n", eval_1.nama_T, eval_1.tinggi);
    printf("Nilai Mahasiswa dengan Eval 1 terendah:\t\t%s dengan nilai %.0f\n\n", eval_1.nama_R, eval_1.rendah);

    printf("Nilai Mahasiswa dengan Eval 2 tertinggi:\t%s dengan nilai %.0f\n", eval_2.nama_T, eval_2.tinggi);
    printf("Nilai Mahasiswa dengan Eval 2 terendah:\t\t%s dengan nilai %.0f\n\n", eval_2.nama_R, eval_2.rendah);

    printf("Nilai Mahasiswa dengan Eval 3 tertinggi:\t%s dengan nilai %.0f\n", eval_3.nama_T, eval_3.tinggi);
    printf("Nilai Mahasiswa dengan Eval 3 terendah:\t\t%s dengan nilai %.0f\n\n", eval_3.nama_R, eval_3.rendah);

    printf("Nilai Mahasiswa dengan UAS tertinggi:\t\t%s dengan nilai %.0f\n", uas.nama_T, uas.tinggi);
    printf("Nilai Mahasiswa dengan UAS terendah:\t\t%s dengan nilai %.0f\n\n", uas.nama_R, uas.rendah);

    printf("\n\n----------------------------------------------------------------------------------------------------------------------\n\n");

}

// Fungsi utama
int main() {
    int pilihan;
    do {
        // Menu utama
        printf("Silahkan pilih menu anda: \n");
        printf("1. Menambah mahasiswa dan nilai\n");
        printf("2. Menampilkan data mahasiswa\n");
        printf("3. Selesai\n");
        printf("------------------------------------\n");
        printf("Pilihan anda: ");
        scanf("%d", &pilihan);
        printf("\n\n");
        // Pilihan menu
        switch (pilihan) {
            case 1:
                inputDataMhs(data_mhs); // Tambah data
                break;
            case 2:
                tampilkanNilai(data_mhs); // Tampilkan data
                break;
            case 3:
                break; // Keluar
        }
    } while (pilihan != 3); // Ulang hingga pilihan '3'

    return 0;
}
