#include <stdio.h>
#include "../ADTWordMachine/charmachine.c"
#include "../ADTWordMachine/wordmachine.c"
#include "../ADTPoint/point.c"
#include "../ADTListDin/listdin.c"
#include "../ADTLokasi/lokasi.c"
#include "../ADTMatrix/matrix.c"
#include "../ADTQueue/prioqueue.c"
#include "../ADTStack/stackTas.c"
#include "../ADTList/listGadget.h"
#include "in_konfigurasi.c"

int main()
{
    // Kamus
    Loc mobita;                 // lokasi mobita
    int uang;                   // uang yang dimiliki mobita
    int waktu;                  // waktu secara keseluruhan
    float satuan_waktu;         // satuan waktu yang akan bertambah setiap mobita bergarak
    PrioQueue daftar_pesanan;     // seluruh daftar pesanan yang harus dikerjakan mobita agar game selesai
    //Pesanan to_do_list;         // pesanan yang dapat dikerjakan mobita
    //Pesanan in_progress_list;   // pesanan yang sedang dolakukan mobita
    StackTas tas;               // Tas mobita berisi item yang dipickup
    ListGadget inventory_gadget; // Daftar gadget yang dimiliki mobita
    Matrix adj_matrix;          // peta
    ListDin daftar_lokasi;      // lokasi-lokasi yang ada
    Pesanan pesanan;

    // input command user
    Word cexit;        // keluar (untuk sementara)
    Word cmove;        // mobita bergerak
    Word cpick_up;     // mobita mengambil barang
    Word cdrop_off;    // mobita menurunkan barang
    Word cmap;         // menampilkan peta
    Word cto_do;       // menampilkan pesanan yang ada di to_do_list
    Word cin_progress; // menampilkan pensanan yang ada di in_progress_list
    Word cbuy;         // mobita membeli gadget
    Word cinvetory;    // menampilkan gadget yang mobita punya
    Word chelp;        // menampilkan list command yang ada

    // input lainnya
    int main_menu = 0; // pilihan user di main menu

    // ============================================================Algoritma==============================================================
    printf("============GO MOBITA============\n");
    printf("Main Menu:\n");
    printf("1. New Game\n");
    printf("2. Exit\n");
    printf("3. Load Game\n");
    while (main_menu != 1 || main_menu != 2 || main_menu != 3)
    {
        printf("Masukkan Menu yang ingin dilakukan (1/2/3): ");
        scanf("%d", &main_menu);
    }
    switch (main_menu)
    {
    case 2:
        break;
    case 1:
        // inisialisasi ADT
        // Linked List
        //CreatePrioQueue(&to_do_list);
        //CreatePrioQueue(&in_progress_list);
        CreatePrioQueue(&daftar_pesanan);
        // inisialisasi Command
        cexit = makeWord("EXIT");              // keluar (untuk sementara)
        cmove = makeWord("MOVE");              // mobita bergerak
        cpick_up = makeWord("PICKUP");         // mobita mengambil barang
        cdrop_off = makeWord("DROPOFF");       // mobita menurunkan barang
        cmap = makeWord("MAP");                // menampilkan peta
        cto_do = makeWord("TODO");             // menampilkan pesanan yang ada di to_do_list
        cin_progress = makeWord("INPROGRESS"); // menampilkan pensanan yang ada di in_progress_list
        cbuy = makeWord("BUY");                // mobita membeli gadget
        cinvetory = makeWord("INVENTORY");     // menampilkan gadget yang mobita punya
        chelp = makeWord("HELP");

        printf("Masukkan File Konfigurasi: ");
        startWord();
        while (/*isEmpty(peta)||isEmpty(daftar_pesanan) sementara gini dulu:*/ main_menu == 0)
        {
            printf("File Konfigurasi tidak valid, mohon coba lagi\n");
            printf("Masukkan File Konfigurasi: ");
            advWord();
        }
        konfig(&adj_matrix, &daftar_lokasi, &daftar_pesanan);
        // inisialisasi lainnya
        waktu = 0; // mulai dari 1/0 ya?
        satuan_waktu = 1;
        mobita = MakeLoc(daftar_lokasi.buffer[0].locname, daftar_lokasi.buffer[0].coord.X, daftar_lokasi.buffer[0].coord.Y);
        // GAME START
        while (/*!isEmpty(daftar_pesanan) || mobita!=lokasi_HQ sementara gini*/ !isWordSame(currentWord, cexit))
        {
            printf("Lokasi Mobita   :");
            DispLoc(mobita);
            printf("\nUang Mobita     : %d\n", uang);
            printf("Waktu           : %d\n", waktu);
            printf("Masukkan Command: ");
            advWord();
            if (isWordSame(currentWord, cmove))
            {
                /* Masukin MOVE - Ilham
                  prosedur updateToDo (*PrioQueue daftar_pesanan, int waktu, *LinkedList Todo) - Akmal
                */
                // variabel yang terlibat: mobita, adj_matrix
                waktu += satuan_waktu;
            }
            else if (isWordSame(currentWord, cpick_up))
            {
                // variabel yang terlibat: mobita(lokasinya mobita), to_do_list & in_progress_list (update pesanan),satuan_waktu(kalo pickup heavy item)
            }
            else if (isWordSame(currentWord, cdrop_off))
            {
                // variabel yang terlibat: mobita(lokasi mobita), daftar_pesanan,to_do_list, & in_progress_list(update pesanan),uang, satuan_waktu, tas(kapasitasnya)
                // speed boost bakal berlaku 10 kali move harus dipikirin gimana (mungkin tambah variabel speed_boost di main.c)
                // speed boost bakal ngubah/nambah code di bagian move
            }
            else if (isWordSame(currentWord, cmap))
            {
                /* Tampilin map - Ilham*/
                // variabel yang terlibat: daftar_lokasi, mobita, to_do_list(mana aja yg bisa di pickup), tas(tujuan drop off paling atas),adj_matrix(lokasi yg bisa dicapai);
            }
            else if (isWordSame(currentWord, cto_do))
            {
                // fungsi display todo (to_do adalah daftar_pesanan yang waktu pesannya < waktu saat ini)
            }
            else if (isWordSame(currentWord, cin_progress))
            {
                // fungsi display in_progress (fungsi yang sama kaya todo)
                // variabel yang terlibat: in_progress_list, waktu(buat perishable item)
            }
            else if (isWordSame(currentWord, cbuy))
            {
                // - Fay
                // fungsi beli item (display ada apa aja, pas belu duit cukup/kaga, inventory_gadget mobita nambah kalo berhasil beli)
                // updet: belum control kalo inventory gadget penuh
                int opsi_beli;
                boolean opsi_valid = false;

                printf("Uang Anda sekarang: %d\n", uang);
                printf("Gadget yang tersedia:\n");
                printf("1. Kain Pembungkus Waktu (800 Yen)\n");
                printf("2. Senter Pembesar (1200 Yen)\n");
                printf("3. Pintu Kemana Saja (1500 Yen)\n");
                printf("4. Mesin Waktu (3000 Yen)\n");
                printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n\n");
                printf("ENTER COMMAND: ");
                opsi_beli = getAngka();
                printf("%d\n", opsi_beli);

                do{
                    if (opsi_beli == 1)
                    {
                        if (uang >= 800)
                        {
                            uang = uang - 800;
                            insertGadget(&inventory_gadget, opsi_beli);
                            printf("Kain Pembungkus Waktu berhasil dibeli!\n");
                            printf("Uang Anda sekarang: %d\n", uang);
                        }
                        else
                        {
                            printf("Uang tidak cukup untuk membeli gadget!\n");
                        }
                        opsi_beli = true;
                    }
                    else if (opsi_beli == 2)
                    {
                        if (uang >= 1200)
                        {
                            uang = uang - 1200;
                            insertGadget(&inventory_gadget, opsi_beli);
                            printf("Senter Pembesar berhasil dibeli!\n");
                            printf("Uang Anda sekarang: %d\n", uang);
                        }
                        else
                        {
                            printf("Uang tidak cukup untuk membeli gadget!\n");
                        }
                        opsi_beli = true;
                    }  
                    else if (opsi_beli == 3)
                    {
                        if (uang >= 1500)
                        {
                            uang = uang - 1500;
                            insertGadget(&inventory_gadget, opsi_beli);
                            printf("Pintu Kemana Saja berhasil dibeli!\n");
                            printf("Uang Anda sekarang: %d\n", uang);
                        }
                        else
                        {
                            printf("Uang tidak cukup untuk membeli gadget!\n");
                        }
                        opsi_beli = true;
                    }    
                    else if (opsi_beli == 4)
                    {
                        if (uang >= 3000)
                        {
                            uang = uang - 3000;
                            insertGadget(&inventory_gadget, opsi_beli);
                            printf("Mesin Waktu berhasil dibeli!\n");
                            printf("Uang Anda sekarang: %d\n", uang);
                        }
                        else
                        {
                            printf("Uang tidak cukup untuk membeli gadget!\n");
                        }
                        opsi_beli = true;
                    }
                    else if (opsi_beli == 0)
                    {
                        printf("Kembali ke menu awal...\n");
                        opsi_beli = true;
                    }                                        
                } while ((!opsi_valid));
            }
            else if (isWordSame(currentWord, cinvetory))
            {
                // TO Do List waktu itemnya ga usah diupdate
                // InProgress List update waktunya
                // fungsi display inventory
                // fungsi pas gadget dipake
                // variabel yang terlibat buat tiap gadget:
                // kain pembungkus waktu : tas,waktu
                // senter pembesar: tas, in_progress_list(maybe ga yakin juga)
                // pintu kemana saja: daftar_lokasi, mobita
                // mesin waktu: waktu (harus ditanya efeknya ke perishable item (waktunya bisa >dari waktu awal ga), to_do_list(bakal ngilang ga))
            }
            else if (isWordSame(currentWord, chelp))
            {
                printf("List Command: \n");
                printf("MOVE        --> menggerakan mobita\n");
                printf("PICKUP      --> mengambil pesanan (harus di lokasi yang ada pesanannya)\n");
                printf("DROPFF      --> mengantar pesanan (menurunkan barang terakhir yang di PICKUP dan harus di lokasi tujuan pesanan)\n");
                printf("MAP         --> menampilkan peta\n");
                printf("TODO        --> menampilkan daftar pesanan yang ada\n");
                printf("INPROGRESS  --> menampilkan daftar pesanan yang sedang dibawa mobita\n");
                printf("BUY         --> membeli gadget (harus di headquarter)\n");
                printf("INVENTORY   --> menampilkan dan menggunakan list gadget yang dimiliki mobita\n");
                printf("HELP        --> menampilkan list commbad yang dapat digunakan\n");
            }
            else if (isWordSame(currentWord, cexit))
            {
                break;
            }

            else
            {
                printf("Command Tidak Sesuai, masukkan HELP untuk melihat daftar command yang ada\n");
            }
        }
    }
}
