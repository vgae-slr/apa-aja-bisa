#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <sstream>
using namespace std;

string namaFile;

struct data_motor{
    int tanggal_masuk, bulan_masuk, tahun_masuk, tanggal_keluar, bulan_keluar, tahun_keluar;
    string merek_motor, nama_pemilik, warna_motor, no_plat, no_hp, no_stnk;
} motor[1000];

void daftarFile(){
    int urutan = 1;
    WIN32_FIND_DATAA daftar;
    
    cout << "Daftar file:\n";
    cout << setfill('=') << setw(30) << "=" << endl;
    cout << setfill(' ');

    HANDLE cari1 = FindFirstFileA("*.txt", &daftar);
    if(cari1 != INVALID_HANDLE_VALUE){
        do {
            cout << urutan << ". " << daftar.cFileName << endl;
            urutan++;
        } while(FindNextFileA(cari1, &daftar));
        FindClose(cari1);
    } else {
        cout << "Tidak ada file.\n";
    }
}

void muatData(string fileDipilih, int *jumlahData){
    *jumlahData = 0;
    string baris, masuk, keluar;
    
    ifstream file(fileDipilih);

    if(!file.is_open()){
        cout << "File tidak ditemukan!\n";
        return;
    }

    while(getline(file, baris)){
        if(!baris.empty() && baris.back() == '\r'){
			baris.pop_back();
		}
        
        if(baris.empty()){
				continue;
		}
        
        stringstream ss(baris);
        char garing;

        if(getline(ss, masuk, '|') &&
			getline(ss, keluar, '|') &&
            getline(ss, motor[*jumlahData].no_plat, '|') &&
            getline(ss, motor[*jumlahData].no_stnk, '|') &&
            getline(ss, motor[*jumlahData].merek_motor, '|') &&
            getline(ss, motor[*jumlahData].warna_motor, '|') &&
            getline(ss, motor[*jumlahData].nama_pemilik, '|') &&
            getline(ss, motor[*jumlahData].no_hp, '|') )
        {
            stringstream(masuk) >> motor[*jumlahData].tanggal_masuk >> garing
                                >> motor[*jumlahData].bulan_masuk >> garing
                                >> motor[*jumlahData].tahun_masuk;
            
            stringstream(keluar) >> motor[*jumlahData].tanggal_keluar >> garing
                                 >> motor[*jumlahData].bulan_keluar >> garing
                                 >> motor[*jumlahData].tahun_keluar;

			(*jumlahData)++;
        }

    }

    file.close();
}

void inputData(int *jumlahData){
    int tambah, pilihan;
    *jumlahData = 0;

    cout << "\nINPUT DATA" << endl;
    cout << setw(30) << setfill('=') << "=" << endl;

    cout << "1. Tambah data\n";
    cout << "2. File baru\n";
    cout << "Pilih : ";
    cin >> pilihan;

    if(pilihan == 2){
        cout << "Disimpan di file bernama (tanpa spasi) : ";
        cin >> namaFile;
    } else {
        daftarFile();
        cout << "Nama file : ";
        cin >> namaFile;
    }

    cin.ignore();
    system("pause");
    system("cls");

    fstream file(namaFile, ios::app);
    if(!file.is_open()){
        cout << "Gagal membuka file!\n";
        system("pause");
        return;
    } else {
        cout << "Jumlah data motor yang ingin ditambahkan : ";
        cin >> tambah;

        cin.ignore();

        for(int i = 0; i < tambah; i++){
            char tanggal_masuk[11], tanggal_keluar[11];
            cout << "\nData motor ke-" << *jumlahData + 1 << endl;

            cout << "Tanggal Masuk (dd/mm/yyyy) : ";
            cin>> tanggal_masuk;
            sscanf(tanggal_masuk, "%d/%d/%d", 
                    &motor[*jumlahData].tanggal_masuk,
                    &motor[*jumlahData].bulan_masuk,
                    &motor[*jumlahData].tahun_masuk);
            cout << "Isi dengan 0 jika belum keluar.\nTanggal Keluar (dd/mm/yyyy) : ";
            cin >> tanggal_keluar;
            sscanf(tanggal_keluar, "%d/%d/%d", 
                    &motor[*jumlahData].tanggal_keluar,
                    &motor[*jumlahData].bulan_keluar,
                    &motor[*jumlahData].tahun_keluar);
            cin.ignore();

            cout << "No. Plat : ";
            getline(cin, motor[*jumlahData].no_plat);
            cout << "No. STNK : ";
            cin >> motor[*jumlahData].no_stnk;
            cin.ignore();
            cout << "Merek Motor : ";
            getline(cin, motor[*jumlahData].merek_motor);
            cout << "Warna Motor : ";
            getline(cin, motor[*jumlahData].warna_motor);

            cout << "Nama Pemilik : ";
            getline(cin, motor[*jumlahData].nama_pemilik);
            cout << "No. HP : ";
            cin >> motor[*jumlahData].no_hp;
            
            cin.ignore();

            file << motor[*jumlahData].tanggal_masuk << "/"
                 << motor[*jumlahData].bulan_masuk << "/"
                 << motor[*jumlahData].tahun_masuk << "|"
                 << motor[*jumlahData].tanggal_keluar << "/"
                 << motor[*jumlahData].bulan_keluar << "/"
                 << motor[*jumlahData].tahun_keluar << "|"
                 << motor[*jumlahData].no_plat << "|"
                 << motor[*jumlahData].no_stnk << "|"
                 << motor[*jumlahData].merek_motor << "|"
                 << motor[*jumlahData].warna_motor << "|"
                 << motor[*jumlahData].nama_pemilik << "|"
                 << motor[*jumlahData].no_hp << endl;
            (*jumlahData)++;
        }
    
        file.close();
    }
}

void updateData(string fileUp, int *jumlahData){
    int update;
    string plat_update, keluar;

    cout << "No. Plat motor yang diupdate : ";
    cin.ignore();
    getline(cin, plat_update);

    for(int i = 0; i < *jumlahData; i++){
        if(motor[i].no_plat == plat_update){
            update = i;
            break;
        }
    }

    cout << "Motor ber-plat " << motor[update].no_plat << " :\n";
    cout << "Tanggal Keluar (dd/mm/yyyy) : ";
    getline(cin, keluar);

    stringstream ss(keluar);
    char garing;

    ss >> motor[update].tanggal_keluar >> garing
        >> motor[update].bulan_keluar >> garing
        >> motor[update].tahun_keluar;
    
    cout << "Tanggal keluar telah diupdate.\n";

    ofstream file(fileUp);
    if(!file.is_open()){
        cout << "Gagal buka file.\n";
        return;
    } else {
        for(int i = 0; i < *jumlahData; i++){
            file << motor[i].tanggal_masuk << "/"
                 << motor[i].bulan_masuk << "/"
                 << motor[i].tahun_masuk << "|"
                 << motor[i].tanggal_keluar << "/"
                 << motor[i].bulan_keluar << "/"
                 << motor[i].tahun_keluar << "|"
                 << motor[i].no_plat << "|"
                 << motor[i].no_stnk << "|"
                 << motor[i].merek_motor << "|"
                 << motor[i].warna_motor << "|"
                 << motor[i].nama_pemilik << "|"
                 << motor[i].no_hp << endl;
        }

        file.close();
    }
}

void cetakTabel(int jumlahData){
    cout << left
         << setw(12) << "TglMasuk"
         << setw(12) << "Plat"
         << setw(15) << "STNK"
         << setw(15) << "Merek"
         << setw(15) << "Warna"
         << setw(15) << "Pemilik"
         << setw(15) << "HP"
         << setw(12) << "TglKeluar"
         << endl;

    cout << string(116,'-') << endl;

    for(int i = 0; i < jumlahData; i++){
        cout << setw(2) << motor[i].tanggal_masuk << "/"
             << setw(2) << motor[i].bulan_masuk << "/"
             << setw(4) << motor[i].tahun_masuk << " ";

        cout << setw(13) << motor[i].no_plat
             << setw(15) << motor[i].no_stnk
             << setw(15) << motor[i].merek_motor
             << setw(15) << motor[i].warna_motor
             << setw(15) << motor[i].nama_pemilik
             << setw(15) << motor[i].no_hp;

        cout << motor[i].tanggal_keluar << "/"
             << motor[i].bulan_keluar << "/"
             << motor[i].tahun_keluar
             << endl;
    }
}

void tampilData(int *jumlahData){

    cout << "\nISI FILE\n";
    cout << setfill('=') << setw(116) << "=" << endl;
    cout << setfill(' ');

    cetakTabel(*jumlahData);
}

void hapusData(string fileDipilih, int *jumlahData){
    string plat, baris;

    fstream file(fileDipilih, ios::in);
    fstream temp("temp.txt", ios::out);
    
    cout << string(116,'-') << endl;
    cetakTabel(*jumlahData);

    cout << "\nMasukkan No. Plat dari data motor yang ingin dihapus : ";
    cin.ignore();
    getline(cin, plat);

    while(getline(file, baris)){
        if(baris.empty()){
            continue;
        }

        stringstream ss(baris);
        string masuk, keluar, no_plat, no_stnk, merek, warna, pemilik, no_hp;

        if(getline(ss, masuk, '|') &&
			getline(ss, keluar, '|') &&
            getline(ss, no_plat, '|') &&
            getline(ss, no_stnk, '|') &&
            getline(ss, merek, '|') &&
            getline(ss, warna, '|') &&
            getline(ss, pemilik, '|') &&
            getline(ss, no_hp, '|') ){

            if(no_plat != plat){
                temp << baris << endl;
            }
        }
    }

    file.close();
    temp.close();

    remove(fileDipilih.c_str());
    rename("temp.txt", fileDipilih.c_str());

    cout << "Berhasil.\n";
    system("pause");
}

bool sortedBy(data_motor a, data_motor b, int sortBy, int sortOrder){
    if(sortOrder == 1){
        switch(sortBy){
            case 1:
                if(a.tahun_masuk != b.tahun_masuk){
                    return a.tahun_masuk < b.tahun_masuk;
                } else if(a.bulan_masuk != b.bulan_masuk) {
                    return a.bulan_masuk < b.bulan_masuk;
                } else {
                    return a.tanggal_masuk < b.tanggal_masuk;
                }
            case 2:
                return a.no_plat < b.no_plat;
            case 3:
                return a.no_stnk < b.no_stnk;
            case 4:
                return a.merek_motor < b.merek_motor;
            case 5:
                return a.warna_motor < b.warna_motor;
            case 6:
                return a.nama_pemilik < b.nama_pemilik;
            case 7:
                return a.no_hp < b.no_hp;
            case 8:
                if(a.tahun_keluar != b.tahun_keluar){
                    return a.tahun_keluar < b.tahun_keluar;
                } else if(a.bulan_keluar != b.bulan_keluar) {
                    return a.bulan_keluar < b.bulan_keluar;
                } else {
                    return a.tanggal_keluar < b.tanggal_keluar;
                }
            default:
                return false;
        }
    } else {
        switch(sortBy){
            case 1:
                if(a.tahun_masuk != b.tahun_masuk)
                    return a.tahun_masuk > b.tahun_masuk;
                else if(a.bulan_masuk != b.bulan_masuk)
                    return a.bulan_masuk > b.bulan_masuk;
                else
                    return a.tanggal_masuk > b.tanggal_masuk;
            break;
            case 2:
                return a.no_plat > b.no_plat;
            break;
            case 3:
                return a.no_stnk > b.no_stnk;
            break;
            case 4:
                return a.merek_motor > b.merek_motor;
            break;
            case 5:
                return a.warna_motor > b.warna_motor;
            break;
            case 6:
                return a.nama_pemilik > b.nama_pemilik;
            break;
            case 7:
                return a.no_hp > b.no_hp;
            break;
            case 8:
                if(a.tahun_keluar != b.tahun_keluar)
                    return a.tahun_keluar > b.tahun_keluar;
                else if(a.bulan_keluar != b.bulan_keluar)
                    return a.bulan_keluar > b.bulan_keluar;
                else
                    return a.tanggal_keluar > b.tanggal_keluar;
            default:
                return false;
        }
    }
}

void insertionSort(int jumlahData, int sortBy, int sortOrder){
    for (int i = 1; i < jumlahData; i++){
		data_motor temp = motor[i]; 
		int j = i - 1;
		while (j >= 0 && sortedBy(motor[j], temp, sortBy, sortOrder)){
			motor[j + 1] = motor[j];
			j--;
		}
		motor[j + 1] = temp;
   	}
}

void sorting(int jumlahData){
    int sortBy, sortOrder;
    char repeatSort, kembali;
	
	system("cls");
	
    do{
        cout<<"Sorting berdasarkan: \n";
        cout<<"1. Tanggal Masuk\n";
        cout<<"2. No. Plat\n";
        cout<<"3. No. STNK\n";
        cout<<"4. Merek Motor\n";
        cout<<"5. Warna Motor\n";
        cout<<"6. Nama Pemilik\n";
        cout<<"7. No. HP Pemilik\n";
        cout<<"8. Tanggal Keluar\n";
        cout<<"Pilih : ";
        cin>>sortBy;

        cout<<endl<<endl;

        cout<<"Urutan secara:\n";
        cout<<"1. Descending\n";
        cout<<"2. Ascending\n";
        cout<<"Pilih : ";
        cin>>sortOrder;
        
        cout << string(116,'-') << endl;
        
        insertionSort(jumlahData, sortBy, sortOrder);
        cetakTabel(jumlahData);
        system("pause");

        cout<<"Ulang sorting? (y/t): ";
        cin>>repeatSort;
        if(repeatSort == 't'){
            cout<<"\nKembali ke menu utama? (y/t) : ";
            cin>>kembali;
            if(kembali == 'y'){
                return;
            } else {
                cout<<"Keluar dari program...\n\n";
                system("pause");
                exit(0);
            }
            return;
        }
    } while((sortBy <= 8) && (sortBy >= 1));
}

void searching(int jumlahData){
    string cari;
    bool ditemukan = false;

    cout << "Masukkan No. Plat yang dicari : ";
    cin.ignore();
    getline(cin, cari);

    for(int i = 0; i < jumlahData; i++){
        if(motor[i].no_plat == cari){

            cout << "\nDATA DITEMUKAN\n";
            cout << "No. Plat      : " << motor[i].no_plat << endl;
            cout << "No. STNK      : " << motor[i].no_stnk << endl;
            cout << "Merek Motor   : " << motor[i].merek_motor << endl;
            cout << "Warna Motor   : " << motor[i].warna_motor << endl;
            cout << "Nama Pemilik  : " << motor[i].nama_pemilik << endl;
            cout << "No. HP        : " << motor[i].no_hp << endl;

            ditemukan = true;
            break;
        }
    }

    if(!ditemukan){
        cout << "Data tidak ditemukan.\n";
    }

    system("pause");
}


int main(){
    int menu_utama, jumlah_data = 0, mode;
    char kembali;
    string fileDipilih, fileCari, fileUrut;
    
    char exePath[MAX_PATH];
	GetModuleFileNameA(NULL, exePath, MAX_PATH);
	string dir(exePath);
	dir = dir.substr(0, dir.find_last_of("\\/"));
	SetCurrentDirectoryA(dir.c_str());

    do{
		cout<<setfill('=')<<setw(27)<<"="<<endl;
        cout<<" DATA PENITIPAN MOTOR\n";
        cout<<setfill('=')<<setw(27)<<"="<<endl;
		
		cout << "1. ISI DATA MOTOR\n";
		cout << "2. TAMPIL DATA MOTOR\n";
		cout << "3. CARI MOTOR\n";
		cout << "4. URUTKAN DATA MOTOR\n";
        cout << "5. HAPUS DATA MOTOR\n";
		cout << "6. KELUAR\n";
        cout<<setfill('=')<<setw(27)<<"="<<endl;
		cout << "Pilih menu : ";
		cin >> menu_utama;
		cout<<setfill('=')<<setw(27)<<"="<<endl;
		
		system("cls");
		
		switch(menu_utama){
            case 1:
                cout << "1. Isi data baru\n";
                cout << "2. Update tanggal keluar\n";
                cout << "Pilih : ";
                cin>> mode;
                switch(mode){
                    case 1:
                        inputData(&jumlah_data);
                    break;
                    case 2:
						daftarFile();
						cout << "Update data dari file : ";
						cin >> fileDipilih;
                        muatData(fileDipilih, &jumlah_data);
                        updateData(fileDipilih, &jumlah_data);
                    break;
                    default:
                        cout << "Pilihan tidak valid!\n";
                        system("pause");
                        system("cls");
                    break;
                }
                cout<<setfill('=')<<setw(27)<<"="<<endl;
                cout<<"Kembali ke menu utama? (y/t) : ";
                cin>>kembali;
                if(kembali == 'y'){
                    system("cls");
                } else {
                    cout<<"Keluar dari program...\n\n";
                    system("pause");
                    return 0;
                }
            break;
            case 2:
                daftarFile();
                cout << "\nNama file yang ingin dibuka : ";
                cin >> fileDipilih;
                muatData(fileDipilih, &jumlah_data);
                tampilData(&jumlah_data);
                cout<<"\nKembali ke menu utama? (y/t) : ";
                cin>>kembali;
                if(kembali == 'y'){
                    system("cls");
                } else {
                    cout<<"Keluar dari program...\n\n";
                    system("pause");
                    return 0;
                }
            break;
            case 3:
                daftarFile();
                cout << "\nCari data dari file : ";
                cin >> fileCari;    
                muatData(fileCari, &jumlah_data);
                searching(jumlah_data);
                system("cls");
            break;
            case 4:
                daftarFile();
                cout << "\nUrutkan data pada file : ";
                cin >> fileUrut;
                muatData(fileUrut, &jumlah_data);    
                sorting(jumlah_data);
                system("cls");
            break;
            case 5:
                daftarFile();
                cout << "\nHapus data dari file : ";
                cin >> fileDipilih;
                muatData(fileDipilih, &jumlah_data);
                hapusData(fileDipilih, &jumlah_data);
                system("cls");
            break;
            case 6:
                cout<<"Keluar dari program...\n\n";
                system("pause");
                return 0;
            break;
            default :
				cout<<"Menu tidak tersedia.\n";
                cout<<"Kembali ke menu utama? (y/t) : ";
                cin>>kembali;
                if(kembali == 't'){
                    cout<<"Keluar dari program...\n\n";
                    system("pause");
                    return 0;
                }
                system("cls");
			break;
        }
    } while ((menu_utama >= 1) && (menu_utama <= 6));
    
}
