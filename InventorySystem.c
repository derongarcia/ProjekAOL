
#include <stdio.h>

#define Max_Items 50

typedef struct{
int ID;
char Barang[50];
float harga;
int JumlahBarang;
}Item;

Item inventory[Max_Items];
int ItemCount = 0;


void addItem(){
if(ItemCount >= Max_Items){
    printf("Inventory sudah penuh\n"); return;

}
Item NewItem;
printf("Masukan ID: ");
scanf("%d", &NewItem.ID);getchar();
printf("Nama Barang: ");
scanf("%[^\n]", NewItem.Barang);getchar();
printf("Masukan Jumlah Harga: ");
scanf("%f", &NewItem.harga);getchar();
printf("Masukan Jumlah Barang: ");
scanf("%d", &NewItem.JumlahBarang);getchar();

inventory[ItemCount] = NewItem;
ItemCount++;
printf("Item Berhasil Ditambahkan!\n");
}

void ViewItem(){
if(ItemCount == 0){
    printf("Inventory Kosong!\n");return;
}
printf("ID\tNama\t\tKuantitas\tHarga\n");
printf("========================================================================\n");
for(int i = 0; i < ItemCount; i++){
    printf("%d\t%s\t\t%d\t\t%.2f\n", inventory[i].ID, inventory[i].Barang, inventory[i].JumlahBarang, inventory[i].harga);
    }
}

void SearchItem(){
if(ItemCount == 0){
    printf("Inventory Kosong!\n");return;
}
int SearchItemID;
printf("Masukkan ID yang ingin dicari: ");
    scanf("%d", &SearchItemID);

    for (int i = 0; i < ItemCount; i++) {
        if (inventory[i].ID == SearchItemID) {
            printf("Item ditemukan!\n");
            printf("ID: %d\n", inventory[i].ID);
            printf("Nama: %s\n", inventory[i].Barang);
            printf("Kuantitas: %d\n", inventory[i].JumlahBarang);
            printf("Harga: %.2f\n", inventory[i].harga);
            return;
        }
    }
    printf("Item dengan ID %d tidak ditemukan.\n", SearchItemID);
}

void writeToFile(){
FILE *file = fopen("History.txt", "w");
if(file == NULL){
    printf("File gagal untuk dibuka.\n"); return;
}
for(int i = 0; i < ItemCount; i++){
    fprintf(file, "ID barang: %d\nNama barang: %s\nJumlah barang: %d\n Harga barang: %.2f\n", inventory[i].ID, inventory[i].Barang, inventory[i].JumlahBarang, inventory[i].harga);
}
fclose(file);
}

void readFromFile(){
FILE *file = fopen("History.txt", "r");
if(file == NULL){
    printf("File tidak dapat ditemukan.\n");return;
}
ItemCount = 0;
while(fscanf(file, "ID barang: %d\nNama barang: %[^\n]\nJumlah barang: %d\n Harga barang: %f\n", &inventory[ItemCount].ID, inventory[ItemCount].Barang, &inventory[ItemCount].JumlahBarang, &inventory[ItemCount].harga)!= EOF){
    ItemCount++;
}
fclose(file);
}



void sortByName(Item items[], int count) {
    Item temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(items[j].Barang, items[j + 1].Barang) > 0) {
                temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

}



int main() {
    int choice;

    while (1) {
    	readFromFile();
        printf("\n=== Sistem Inventori ===\n");
        printf("1. Tambah Item\n");
        printf("2. Lihat Semua Item\n");
        printf("3. Cari Item\n");
        printf("4. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                writeToFile();
                break;
            case 2:
              sortByName(inventory, ItemCount);
                ViewItem();
                break;
            case 3:
                SearchItem();
                break;
            case 4:
                printf("Terima Kasih Telah Menggunakan Inventory.\n");
                return 0;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
    return 0;
}
