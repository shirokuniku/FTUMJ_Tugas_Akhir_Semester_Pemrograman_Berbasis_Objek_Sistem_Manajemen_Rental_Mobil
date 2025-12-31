#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// -----------------------------
// Class Mobil
// -----------------------------
class Mobil {
private:
    string plat;
    string merk;
    string model;
    int harga_per_hari;
    bool tersedia;

public:
    Mobil(string p, string m, string mo, int harga) {
        plat = p;
        merk = m;
        model = mo;
        harga_per_hari = harga;
        tersedia = true;
    }

    string getInfo() {
        string status = tersedia ? "Tersedia" : "Disewa";
        return plat + " - " + merk + " " + model +
               " | " + status + " | Rp" + to_string(harga_per_hari) + "/hari";
    }

    string getPlat() {
        return plat;
    }

    int getHarga() {
        return harga_per_hari;
    }

    bool isTersedia() {
        return tersedia;
    }

    void sewa() {
        tersedia = false;
    }

    void kembalikan() {
        tersedia = true;
    }
};

// -----------------------------
// Class Pelanggan
// -----------------------------
class Pelanggan {
public:
    string nama;
    string ktp;

    Pelanggan(string n, string k) {
        nama = n;
        ktp = k;
    }

    string getInfo() {
        return nama + " (KTP: " + ktp + ")";
    }
};

// -----------------------------
// Class TransaksiRental
// -----------------------------
class TransaksiRental {
public:
    Pelanggan pelanggan;
    Mobil* mobil;
    int lama_sewa;
    time_t tanggal_mulai;
    int total_biaya;

    TransaksiRental(Pelanggan p, Mobil* m, int lama) 
        : pelanggan(p) {
        mobil = m;
        lama_sewa = lama;
        tanggal_mulai = time(nullptr);
        total_biaya = mobil->getHarga() * lama_sewa;
        mobil->sewa();
    }

    void tampilkanStruk() {
        cout << "\n====== STRUK RENTAL MOBIL ======\n";
        cout << "Pelanggan  : " << pelanggan.getInfo() << endl;
        cout << "Mobil      : " << mobil->getInfo() << endl;
        cout << "Lama Sewa  : " << lama_sewa << " hari\n";
        cout << "Total Biaya: Rp" << total_biaya << endl;
        cout << "Tanggal Mulai: " << ctime(&tanggal_mulai);
        cout << "================================\n";
    }
};

// -----------------------------
// Class SistemRental
// -----------------------------
class SistemRental {
private:
    vector<Mobil> daftar_mobil;
    vector<TransaksiRental> daftar_transaksi;

public:
    void tambahMobil(Mobil mobil) {
        daftar_mobil.push_back(mobil);
    }

    void tampilkanMobil() {
        cout << "\n=== DAFTAR MOBIL ===\n";
        for (auto &mobil : daftar_mobil) {
            cout << mobil.getInfo() << endl;
        }
    }

    void sewaMobil(string plat, Pelanggan pelanggan, int lama) {
        for (auto &mobil : daftar_mobil) {
            if (mobil.getPlat() == plat && mobil.isTersedia()) {
                TransaksiRental transaksi(pelanggan, &mobil, lama);
                daftar_transaksi.push_back(transaksi);
                transaksi.tampilkanStruk();
                return;
            }
        }
        cout << "Mobil tidak tersedia atau tidak ditemukan!\n";
    }

    void kembalikanMobil(string plat) {
        for (auto &mobil : daftar_mobil) {
            if (mobil.getPlat() == plat && !mobil.isTersedia()) {
                mobil.kembalikan();
                cout << "Mobil " << plat << " telah dikembalikan.\n";
                return;
            }
        }
        cout << "Mobil tidak ditemukan atau sudah tersedia.\n";
    }
};

// -----------------------------
// Main Program
// -----------------------------
int main() {
    SistemRental sistem;

    // Tambah mobil
    sistem.tambahMobil(Mobil("B1234AA", "Toyota", "Avanza", 350000));
    sistem.tambahMobil(Mobil("B5678BB", "Honda", "Brio", 300000));
    sistem.tambahMobil(Mobil("B9999CC", "Suzuki", "Ertiga", 400000));

    // Tampilkan mobil
    sistem.tampilkanMobil();

    // Buat pelanggan
    Pelanggan pelanggan1("Andi", "1234567890");

    // Sewa mobil
    sistem.sewaMobil("B1234AA", pelanggan1, 3);

    // Tampilkan mobil lagi
    sistem.tampilkanMobil();

    // Kembalikan mobil
    sistem.kembalikanMobil("B1234AA");

    // Tampilkan mobil lagi
    sistem.tampilkanMobil();

    return 0;
}
