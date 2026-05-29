#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

string namaFile;

struct data_motor{
    long no_stnk, no_hp;
    int tanggal_masuk, bulan_masuk, tahun_masuk, tanggal_keluar, bulan_keluar, tahun_keluar;
    string merek_motor, nama_pemilik, warna_motor, no_plat;
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

void inputData(int *jumlahData){
    int tambah;
    *jumlahData = 0;

    cout << "\nINPUT DATA" << endl;
    cout << setw(30) << setfill('=') << "=" << endl;
    cout << "Disimpan di file bernama (tanpa spasi) : ";
    cin >> namaFile;
    cin.ignore();

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

void updateData(int *jumlahData){
    int update;
    char tanggal_keluar[11];
    string plat_update;

    cout << "No. Plat motor yang diupdate : ";
    cin.ignore();
    getline(cin, plat_update);

    for(int i = 0; i < *jumlahData; i++){
        if(motor[i].no_plat == plat_update){
            update = i;
            break;
        }
    }

    cout << "Tanggal Keluar (dd/mm/yyyy) : ";
    cin >> tanggal_keluar;
    sscanf(tanggal_keluar, "%d/%d/%d", 
            &motor[update].tanggal_keluar,
            &motor[update].bulan_keluar,
            &motor[update].tahun_keluar);
    
    cout << "Tanggal keluar telah diupdate.\n";
}

void hapusData(){
    //grace smangat
}

void cetakTabel(int jumlahData){
    //grace smangat
}

void tampilData(){
    //grace smangit
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
        cout<<"1. Ascending\n";
        cout<<"2. Descending\n";
        cout<<"Pilih : ";
        cin>>sortOrder;

        system("cls");
        
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

void searching(){
    //grace smungut
}


int main(){
    int menu_utama, jumlah_data = 0, mode;
    char kembali;
    
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
                        updateData(&jumlah_data);
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
                tampilData();
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
                searching();
                system("cls");
            break;
            case 4:
                sorting(jumlah_data);
                system("cls");
            break;
            case 5:
                hapusData();
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