#include <stdio.h>
#include "../ADTWordMachine/charmachine.c"
#include "../ADTWordMachine/wordmachine.c"
#include "../ADTPoint/point.c"
#include "../ADTListDin/listdin.c"
#include "../ADTLokasi/lokasi.c"
#include "../ADTMatrix/matrix.c"
#include "../ADTQueue/prioqueue.c"
#include "../ADTStack/stackTas.c"
#include "../ADTList/listGadget.c"
#include "../ADTLinkedList/list_linked.c"
#include "../ADTMap/map.c"
#include "in_konfigurasi.c"

int main()
{
    // Kamus
    Loc mobita;                  // lokasi mobita
    int uang;                    // uang yang dimiliki mobita
    int waktu;                   // waktu secara keseluruhan
    float waktu_speed;           // waktu saat speed up aktif
    float satuan_waktu;          // satuan waktu yang akan bertambah setiap mobita bergarak
    int speed_up;                // lama speed_up berefek
    PrioQueue daftar_pesanan;    // seluruh daftar pesanan yang harus dikerjakan mobita agar game selesai
    LinkedList to_do_list;       // pesanan yang dapat dikerjakan mobita
    LinkedList in_progress_list; // pesanan yang sedang dolakukan mobita
    StackTas tas;                // Tas mobita berisi item yang dipickup
    ListGadget inventory_gadget; // Daftar gadget yang dimiliki mobita
    Matrix adj_matrix;           // peta
    ListDin daftar_lokasi;       // lokasi-lokasi yang ada
    map peta;                    // peta lokasi-lokasi yang ada
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
    boolean berhasil;  // apakah konfig berhasil atau tidak

    // ============================================================Algoritma==============================================================
    printf("============GO MOBITA============\n");
    printf("Main Menu:\n");
    printf("1. New Game\n");
    printf("2. Exit\n");
    printf("3. Load Game\n");
    while (main_menu != 1 && main_menu != 2 && main_menu != 3)
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
        CreateLinkedList(&to_do_list);
        CreateLinkedList(&in_progress_list);
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
        konfig(&adj_matrix, &daftar_lokasi, &daftar_pesanan, &berhasil, currentWord);
        while (!berhasil)
        {
            printf("File Konfigurasi tidak valid, mohon coba lagi\n");
            printf("Masukkan File Konfigurasi: ");
            advWord();
            konfig(&adj_matrix, &daftar_lokasi, &daftar_pesanan, &berhasil, currentWord);
        }
        // inisialisasi lainnya
        waktu = 0;
        waktu_speed = 0;
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
                move(adj_matrix, daftar_lokasi, &mobita);
                updateToDoList(&daftar_pesanan, &to_do_list, waktu);
                if (speed_up != 0)
                {
                    waktu_speed += 0.5;
                    speed_up -= 1;
                    if (waktu_speed == 1.0)
                    {
                        waktu += 1;
                        waktu_speed -= 1.0;
                    }
                }
                else
                {
                    waktu += satuan_waktu;
                }
            }
            else if (isWordSame(currentWord, cpick_up))
            {
                if (pickUpAble(&to_do_list, mobita))
                {
                    removePesananDariToDo(&to_do_list, mobita, &pesanan);
                    insertLinkedListFirst(&in_progress_list, pesanan);
                    pushTas(&tas, pesanan);
                    switch (pesanan.itype)
                    {
                    case 'N':
                        printf("Normal Item Berhasil di Pick Up\n");
                        break;
                    case 'H':
                        printf("Heavy Item Berhasil di Pick Up, Speed Mobita akan berkurang\n");
                        satuan_waktu += 1;
                        speed_up = 0;
                        break;
                    case 'P':
                        printf("Perishable Item Berhasil di Pick Up\n");
                    default:
                        break;
                    }
                }
                else
                {
                    printf("Tidak Ada Pesanan yang dapat di pick up");
                }
            }
            else if (isWordSame(currentWord, cdrop_off))
            {
                if (mobita.locname == pesanan.dropoff)
                {
                    popTas(&tas, &pesanan);
                    deleteLinkedListFirst(&in_progress_list, &pesanan);
                    switch (pesanan.itype)
                    {
                    case 'N':
                        uang += 200;
                        printf("Normal item berhasil diantarkan. Uang mobita bertambah 200 Yen\n");
                        break;
                    case 'H':
                        uang += 400;
                        satuan_waktu -= 1;
                        if (satuan_waktu == 1)
                        {
                            speed_up = 10;
                        }
                        printf("Normal item berhasil diantarkan. Uang mobita bertambah 400 Yen\n");
                    case 'P':
                        uang += 400;
                        increaseTas(&tas);
                        printf("Normal item berhasil diantarkan. Uang mobita bertambah 400 Yen\n");
                        break;
                    default:
                        break;
                    }
                }
                else
                {
                    printf("Pesanan gagal diantar\n");
                }
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

                int opsi_beli;
                boolean opsi_beli_valid = false;

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

                if (isGadgetFull(inventory_gadget)) /* Cek kasus inventory penuh */
                {
                    printf("Inventory gadget penuh!\n");
                    printf("Kembali ke menu awal...\n");
                }
                else
                {
                    do
                    {
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
                            opsi_beli_valid = true;
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
                            opsi_beli_valid = true;
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
                            opsi_beli_valid = true;
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
                            opsi_beli_valid = true;
                        }
                        else if (opsi_beli == 0)
                        {
                            printf("Kembali ke menu awal...\n");
                            opsi_beli_valid = true;
                        }
                        else
                        {
                            printf("Masukan tidak valid!\n");
                            printf("ENTER COMMAND: ");
                            opsi_beli = getAngka();
                            printf("%d\n", opsi_beli);
                        }
                    } while (!opsi_beli_valid);
                }
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

                // update: use_gadget belum diimplementasikan. bingung input parameternya apa aja
                //         apa better tiap gadget punya fungsinya masing-masing?

                int opsi_gadget; /* menyimpan pilihan gadget dari user pada inventory */
                int kode_gadget; /* menyimpan kode gadget dari opsi_gadget */
                boolean opsi_gadget_valid = false;

                displayListGadget(inventory_gadget);
                printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n\n");
                printf("ENTER COMMAND: ");
                opsi_gadget = getAngka();
                printf("%d\n", opsi_gadget);

                if (LGELMT(inventory_gadget, opsi_gadget) == VAL_UNDEF) /* Cek kasus opsi gadget kosong */
                {
                    printf("Tidak ada Gadget yang dapat digunakan!\n");
                }
                else
                {
                    do
                    {
                        deleteGadget(&inventory_gadget, opsi_gadget, &kode_gadget);
                        if (kode_gadget == 1)
                        {
                            printf("Kain Pembungkus Waktu berhasil digunakan!\n");
                            useKainPembungkusWaktu(&in_progress_list, &tas, waktu);
                            opsi_gadget_valid = true;
                        }
                        else if (kode_gadget == 2)
                        {
                            senterPembesar(&tas);
                            printf("Senter Pembesar berhasil digunakan!\n");
                            opsi_gadget_valid = true;
                        }
                        else if (kode_gadget == 3)
                        {
                            pintuKemanaSaja(daftar_lokasi, &mobita);
                            printf("Pintu Kemana Saja berhasil digunakan!\n");
                            opsi_gadget_valid = true;
                        }
                        else if (kode_gadget == 4)
                        {
                            useMesinWaktu(&in_progress_list, &tas, &waktu);
                            printf("Mesin Waktu berhasil digunakan!\n");
                            opsi_gadget_valid = true;
                        }
                        else if (kode_gadget == 0)
                        {
                            printf("Kembali ke menu awal...\n");
                            opsi_gadget_valid = true;
                        }
                        else
                        {
                            printf("Masukan tidak valid!\n");
                            printf("ENTER COMMAND: ");
                            opsi_gadget = getAngka();
                            printf("%d\n", opsi_gadget);
                        }
                    } while (!opsi_gadget_valid);
                }
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
