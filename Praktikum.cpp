#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    TokoElektronik() {
        etalase[0] = "Laptop";
        etalase[1] = "Smartphone";
        etalase[2] = "Printer";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string("Gagal Mengambil Barang : Rak nomor " +
                         to_string(nomorRak) +
                         " kosong atau tidak tersedia!");
        }
    }
};

void tambahBarang() {
    ofstream file("gudang.txt", ios::app);

    string barang;
    cout << "Nama Barang: ";
    cin.ignore();
    getline(cin, barang);

    file << barang << endl;
    file.close();

    cout << "Barang berhasil ditambahkan.\n";
}

void tampilBarang() {
    ifstream file("gudang.txt");

    string barang;
    int no = 1;

    cout << "\n=== DAFTAR BARANG ===\n";

    while (getline(file, barang)) {
        cout << no++ << ". " << barang << endl;
    }

    file.close();
}

void updateBarang() {
    ifstream file("gudang.txt");
    vector<string> data;
    string barang;

    while (getline(file, barang))
        data.push_back(barang);

    file.close();

    int nomor;
    cout << "Nomor barang yang diubah: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    cout << "Nama baru: ";
    cin.ignore();
    getline(cin, data[nomor - 1]);

    ofstream out("gudang.txt");
    for (string x : data)
        out << x << endl;

    out.close();

    cout << "Data berhasil diupdate.\n";
}

void hapusBarang() {
    ifstream file("gudang.txt");
    vector<string> data;
    string barang;

    while (getline(file, barang))
        data.push_back(barang);

    file.close();

    int nomor;
    cout << "Nomor barang yang dihapus: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Data tidak ditemukan!\n";
        return;
    }

    data.erase(data.begin() + nomor - 1);

    ofstream out("gudang.txt");
    for (string x : data)
        out << x << endl;

    out.close();

    cout << "Data berhasil dihapus.\n";
}

void simulasiEtalase() {
    TokoElektronik toko;

    try {
        cout << "\nSkenario 1\n";
        cout << "Barang: " << toko.ambilProduk(1) << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }

    try {
        cout << "\nSkenario 2\n";
        cout << "Barang: " << toko.ambilProduk(5) << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }
}

int main() {
    int pilih;

    do {
        cout << "\n===== MENU GUDANG =====\n";
        tampilBarang();

        cout << "\n1. Tambah Barang\n";
        cout << "2. Update Barang\n";
        cout << "3. Hapus Barang\n";
        cout << "4. Simulasi Etalase\n";
        cout << "0. Keluar\n";
        cout << "Pilihan: ";
        cin >> pilih;

        switch (pilih) {
        case 1:
            tambahBarang();
            break;
        case 2:
            updateBarang();
            break;
        case 3:
            hapusBarang();
            break;
        case 4:
            simulasiEtalase();
            break;
        case 0:
            cout << "Program selesai.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 0);

    return 0;
}