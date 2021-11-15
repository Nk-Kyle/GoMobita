#include <stdio.h>
#include <stdlib.h>
#include "ADTWordMachine/charmachine.h"
#include "ADTWordMachine/wordmachine.h"
#include "ADTPoint/point.h"
#include "ADTListDin/listdin.h"
#include "ADTLokasi/lokasi.h"
#include "ADTMatrix/matrix.h"
#include "ADTQueue/prioqueue.h"
#include "ADTStack/stackTas.h"
#include "ADTList/listGadget.h"
#include "ADTLinkedList/list_linked.h"
#include "ADTMap/map.h"
#include "MainApp/in_konfigurasi.h"
#include "ADTItem/item.h"
#include "ADTLinkedList/node.h"
#include "ADTColor/pcolor.h"
#include "MainApp/save.h"

int main()
{
    // Kamus
    Loc mobita;                  // lokasi mobita
    int uang;                    // uang yang dimiliki mobita
    int waktu;                   // waktu secara keseluruhan
    float waktu_speed;           // waktu saat speed up aktif
    float satuan_waktu;          // satuan waktu yang akan bertambah setiap mobita bergarak
    int speed_up;                // lama speed_up berefek
    int jumlah_antaran;          // jumlah pesanan yang berhasil diantar mobita
    int return_barang;           // ability return barang yang didapat ketika mengantar VIP item
    boolean senter_pengecil;     // Menandakan senter pengecil aktif atau tidak
    PrioQueue daftar_pesanan;    // seluruh daftar pesanan yang harus dikerjakan mobita agar game selesai
    LinkedList to_do_list;       // pesanan yang dapat dikerjakan mobita
    LinkedList in_progress_list; // pesanan yang sedang dolakukan mobita
    StackTas tas;                // Tas mobita berisi item yang dipickup
    ListGadget inventory_gadget; // Daftar gadget yang dimiliki mobita
    Matrix adj_matrix;           // peta
    ListDin daftar_lokasi;       // lokasi-lokasi yang ada
    map peta;                    // peta lokasi-lokasi yang ada
    Pesanan pesanan;
    Address p;

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
    Word creturn;      // mengembalikan pesanan di tas ke tempat semulanya
    Word csave;        // save kondisi game
    Word namafile;

    // input lainnya
    int main_menu = 0; // pilihan user di main menu
    boolean berhasil;  // apakah konfig berhasil atau tidak

    //============================================================Inisialisasi============================================================
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
    chelp = makeWord("HELP");              // menampilkan list command yang ada
    creturn = makeWord("RETURN");          // mengembalikan pesanan di tas ke tempat semulanya
    csave = makeWord("SAVE");

    // ============================================================Algoritma==============================================================
    printf("============GO MOBITA============\n");
    printf("Main Menu:\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Exit\n");
    printf("Masukkan Menu yang ingin dilakukan (1/2/3): ");
    startWord();
    main_menu = getAngka();
    while (main_menu != 1 && main_menu != 2 && main_menu != 3)
    {
        printf("Inputan salah!");
        printf("Masukkan Menu yang ingin dilakukan (1/2/3): ");
        advWord();
        main_menu = getAngka();
    }
    switch (main_menu)
    {
    case 1:
        CreateLinkedList(&to_do_list);
        CreateLinkedList(&in_progress_list);
        CreateTas(&tas);
        CreateListGadget(&inventory_gadget);
        printf("Masukkan File Konfigurasi: ");
        startWord();
        namafile = getWord();
        konfig(&adj_matrix, &daftar_lokasi, &daftar_pesanan, namafile, &peta);
        // inisialisasi lainnya
        uang = 0;
        waktu = 0;
        waktu_speed = 0;
        satuan_waktu = 1;
        speed_up = 0;
        jumlah_antaran = 0;
        return_barang = 0;
        senter_pengecil = false;
        mobita = MakeLoc(daftar_lokasi.buffer[0].locname, daftar_lokasi.buffer[0].coord.X, daftar_lokasi.buffer[0].coord.Y);
        break;
    case 2:
        printf("Masukkan File Konfigurasi: ");
        startWord();
        namafile = getWord();
        load_konfig(&mobita, &uang, &waktu, &waktu_speed, &satuan_waktu,
                    &speed_up, &jumlah_antaran, &return_barang, &daftar_pesanan, &to_do_list,
                    &in_progress_list, &tas, &inventory_gadget, &adj_matrix,
                    &daftar_lokasi, &peta, namafile, &senter_pengecil);
        break;
    case 3:
        return 0;
        break;
    }
    //=============================================GAME START=====================================
    while (!isWordSame(currentWord, cexit) && mobita.locname != '8' || !isEmpty(daftar_pesanan) || !isEmptyLinkedList(to_do_list) || !isEmptyLinkedList(in_progress_list))
    {
        printf("=================================================================\n");
        printf("Lokasi Mobita   : ");
        DispLoc(mobita);
        printf("\nUang Mobita     : %d\n", uang);
        printf("Waktu           : %d\n", waktu);
        printf("Masukkan Command: ");
        advWord();
        if (isWordSame(currentWord, cmove))
        {
            move(adj_matrix, daftar_lokasi, &mobita);
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
            updateToDoList(&daftar_pesanan, &to_do_list, waktu);
            updateInProgressList(&in_progress_list, waktu);
        }
        else if (isWordSame(currentWord, cpick_up))
        {
            if (TOP(tas).itype == 'V')
            {
                printf("Pesanan Gagal di Pickup, Anda Harus mengantarkan pesanan VIP terlebih dahulu!\n");
            }
            else if (isTasFull(tas))
            {
                printf("Tas penuh! Barang tidak bisa di pick up\n");
            }

            else if (isPickUpAble(&to_do_list, mobita))
            {
                if (adaVIPItemDiTempatLain(to_do_list, mobita))
                {
                    printf("Pesanan gagal diambil karena ada pesanan VIP di tempat lain\n");
                }
                else
                {
                    removePesananDariToDo(&to_do_list, mobita, &pesanan);
                    pesanan.pickuptime = waktu;
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
                        break;
                    case 'V':
                        printf("VIP Item Berhasil di Pickup, VIP Item harus segera diantar!\n");
                        break;
                    default:
                        break;
                    }
                }
            }
            else
            {
                printf("Tidak Ada Pesanan yang dapat di pick up\n");
            }
        }
        else if (isWordSame(currentWord, cdrop_off))
        {
            if (mobita.locname == TOP(tas).dropoff)
            {
                popTas(&tas, &pesanan);
                deleteLinkedListFirst(&in_progress_list, &pesanan);
                jumlah_antaran++;
                switch (pesanan.itype)
                {
                case 'N':
                    uang += 200;
                    printf("Normal item berhasil diantarkan. Uang mobita bertambah 200 Yen\n");
                    break;
                case 'H':
                    uang += 400;
                    if (!senter_pengecil)
                    {
                        satuan_waktu -= 1;
                    }
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
                case 'V':
                    uang += 600;
                    printf("VIP item berhasil diantarkan. Uang mobita bertambah 600 Yen\n");
                    return_barang += 1;
                default:
                    break;
                }
                if (senter_pengecil)
                {
                    senter_pengecil = false;
                }
            }
            else
            {
                printf("Pesanan gagal diantar\n");
            }
        }
        else if (isWordSame(currentWord, cmap))
        {
            printMap(peta, daftar_lokasi, adj_matrix, mobita, to_do_list, tas);
        }
        else if (isWordSame(currentWord, cto_do))
        {
            displayToDoList(to_do_list);
        }
        else if (isWordSame(currentWord, cin_progress))
        {
            displayInProgressList(in_progress_list, waktu);
        }
        else if (isWordSame(currentWord, cbuy))
        {
            // - Fay
            // fungsi beli item (display ada apa aja, pas belu duit cukup/kaga, inventory_gadget mobita nambah kalo berhasil beli)

            int opsi_beli;
            boolean opsi_beli_valid = false;

            if (mobita.locname == '8')
            {
                printf("Uang Anda sekarang: %d\n", uang);
                printf("Gadget yang tersedia:\n");
                printf("1. Kain Pembungkus Waktu (800 Yen)\n");
                printf("2. Senter Pembesar (1200 Yen)\n");
                printf("3. Pintu Kemana Saja (1500 Yen)\n");
                printf("4. Mesin Waktu (3000 Yen)\n");
                printf("5. Senter Pengecil (800 Yen)\n");
                printf("Gadget mana yang ingin kau beli? (ketik 0 jika ingin kembali)\n");
                printf("Masukkan Opsi: ");
                advWord();
                opsi_beli = getAngka();

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
                        else if (opsi_beli == 5)
                        {
                            if (uang >= 800)
                            {
                                uang = uang - 800;
                                insertGadget(&inventory_gadget, opsi_beli);
                                printf("Senter Pengecil berhasil dibeli!\n");
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
                            printf("Masukkan Opsi: ");
                            advWord();
                            opsi_beli = getAngka();
                            printf("%d\n", opsi_beli);
                        }
                    } while (!opsi_beli_valid);
                }
            }
            else
            {
                printf("Anda harus kembali ke headquarter!\n");
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

            int opsi_gadget; /* menyimpan pilihan gadget dari user pada inventory */
            int kode_gadget; /* menyimpan kode gadget dari opsi_gadget */
            boolean opsi_gadget_valid = false;

            displayListGadget(inventory_gadget);
            printf("Gadget mana yang ingin digunakan? (ketik 0 jika ingin kembali)\n");
            do
            {
                printf("Masukkan Opsi: ");
                advWord();
                opsi_gadget = getAngka();
                if ((opsi_gadget >= 0) && (opsi_gadget <= 5))
                {
                    opsi_gadget_valid = true;
                }
                else
                {
                    printf("Masukan invalid!\n");
                }
            } while (!opsi_gadget_valid);

            if (opsi_gadget == 0)
            {
                printf("Kembali ke menu awal...\n");
            }
            else
            {
                opsi_gadget--;
                if (LGELMT(inventory_gadget, opsi_gadget) == VAL_UNDEF) /* Cek kasus opsi gadget kosong */
                {
                    printf("Tidak ada Gadget yang dapat digunakan!\n");
                }
                else
                {
                    deleteGadget(&inventory_gadget, opsi_gadget, &kode_gadget);
                    if (kode_gadget == 1)
                    {
                        printf("Kain Pembungkus Waktu berhasil digunakan!\n");
                        useKainPembungkusWaktu(&in_progress_list, &tas, waktu);
                    }
                    else if (kode_gadget == 2)
                    {
                        senterPembesar(&tas);
                        printf("Senter Pembesar berhasil digunakan!\n");
                    }
                    else if (kode_gadget == 3)
                    {
                        pintuKemanaSaja(daftar_lokasi, &mobita);
                        printf("Pintu Kemana Saja berhasil digunakan!\n");
                    }
                    else if (kode_gadget == 4)
                    {
                        useMesinWaktu(&in_progress_list, &tas, &waktu);
                        printf("Mesin Waktu berhasil digunakan!\n");
                    }
                    else if (kode_gadget == 5)
                    {
                        if (TOP(tas).itype == 'H')
                        {
                            if (senter_pengecil)
                            {
                                printf("Senter Pengecil Sudah Aktif! Senter pengecil ini akan hangus\n");
                            }
                            else
                            {
                                printf("Senter Pengecil Berhasil digunakan!\n");
                                senter_pengecil = true;
                                satuan_waktu--;
                            }
                        }
                        else
                        {
                            printf("Barang paling atas di tas bukan Heavy Item! Senter Pengecil akan hangus\n");
                        }
                    }
                }
            }
        }
        else if (isWordSame(currentWord, creturn))
        {
            if (TOP(tas).itype == 'V')
            {
                printf("Ability gagal digunakan karena barang VIP Harus Segera Diantar!!!\n");
            }
            else
            {
                if (return_barang != 0)
                {
                    returnToSender(&to_do_list, &in_progress_list, &tas);
                    printf("Barang berhasil dikembalikan ke tempat semula\n");
                    return_barang--;
                }
                else
                {
                    printf("Anda tidak memiliki Ability RETURN\n");
                }
            }
        }
        else if (isWordSame(currentWord, chelp))
        {
            printf("List Command: \n");
            printf("MOVE        --> menggerakan mobita\n");
            printf("PICKUP      --> mengambil pesanan (harus di lokasi yang ada pesanannya)\n");
            printf("DROPOFF     --> mengantar pesanan (menurunkan barang terakhir yang di PICKUP dan harus di lokasi tujuan pesanan)\n");
            printf("MAP         --> menampilkan peta\n");
            printf("TODO        --> menampilkan daftar pesanan yang ada\n");
            printf("INPROGRESS  --> menampilkan daftar pesanan yang sedang dibawa mobita\n");
            printf("BUY         --> membeli gadget (harus di headquarter)\n");
            printf("INVENTORY   --> menampilkan dan menggunakan list gadget yang dimiliki mobita\n");
            printf("RETURN      --> mengembalikan barang di tas ke tempat semula. Hanya dapat digunakan jika berhasil mengantar VIP Item\n");
            printf("SAVE        --> menyimpan progress game ke file agar dapat di load kembali\n");
            printf("HELP        --> menampilkan list commbad yang dapat digunakan\n");
            printf("EXIT        --> keluar game\n");
        }
        else if (isWordSame(currentWord, csave))
        {
            printf("Masukkan File tujuan save: ");
            advWord();
            namafile = getWord();
            save_konfig(mobita, uang, waktu, waktu_speed, satuan_waktu,
                        speed_up, jumlah_antaran, return_barang, daftar_pesanan, to_do_list,
                        in_progress_list, tas, inventory_gadget, adj_matrix,
                        daftar_lokasi, peta, namafile, senter_pengecil);
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
    if (!isWordSame(currentWord, cexit))
    {
        printf("Selamat!!!! Game Berhasil Diselesaikan\n");
        printf("Jumlah pesanan yang berhasil diantar: %d\n", jumlah_antaran);
        printf("Lama waktu game: %d satuan\n", waktu);
    }
}
