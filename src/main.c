/*
13519030
13519038
13519150
13519154
13519162
*/

/**
 * gcc main.c Array/arraydinaction.c Array/Action/action.c Array/arraydinbarang.c Array/Barang/barang.c Array/arraydininventory.c Array/Inventory/inventory.c Matriks/matriks.c Mesin/mesinkata.c Mesin/mesinkar.c Point/point.c Jam/jam.c Player/player.c Queue/queue.c Command/command.c Wahana/wahana.c Tree/bintree.c Listberkait/listwahana.c Listberkait/listlinier.c Graph/graph.c Stack/stackt.c -o main
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "boolean.h"
#include "Array/arraydinaction.h"
#include "Array/arraydinbarang.h"
#include "Array/arraydininventory.h"
#include "Matriks/matriks.h"
#include "Mesin/mesinkata.h"
#include "Mesin/mesinkar.h"
#include "Point/point.h"
#include "Jam/jam.h"
#include "Queue/queue.h"
#include "Player/player.h"
#include "Wahana/wahana.h"
#include "Tree/bintree.h"
#include "Command/command.h"
#include "Listberkait/listwahana.h"
#include "Graph/graph.h"
#include "Stack/stackt.h"


int main() {
    /*** DEKLARASI WAHANA ***/
    Wahana W1;
    Wahana W1_1, W1_2;
    MakeWahana(&W1, "Wahana/wahana1.txt");
    MakeWahana(&W1_1, "Wahana/wahana1_1.txt");
    MakeWahana(&W1_2, "Wahana/wahana1_2.txt");

    /*** DEKLARASI LIST WAHANA ***/
    // List wahana yang tersedia pada map
    List listWahana;
    CreateEmptyWahana(&listWahana);

    // Deklarasi wahana pertama pada map dalam list
    Wahana def = W1;
    def.statusWahana = 1;
    def.lokasiWahana = MakePOINT(11, 4);
    def.zona = 1;
    InsVLastWahana(&listWahana, def);

    // List wahana yang dapat dibangun
    List daftarWahana;
    CreateEmptyWahana(&daftarWahana);
    W1.lokasiWahana = MakePOINT(0,0);
    InsVLastWahana(&daftarWahana, W1);
    


    /*** DEKLARASI GRAPH ***/
    Graph G;
    MakeGraph(&G, 4);   // Membuat graph dengan 4 node untuk merepresentasikan zona pada Map
    /* Menghubungkan masing-masing zona Map */
    AddLink(&G, 1, 2);
    AddLink(&G, 1, 3);
    AddLink(&G, 2, 4);
    AddLink(&G, 3, 4);
    int currentZone = G.First->info;    // Deklarasi zona pertama yaitu pada Map 1

    /*** DEKLARASI STACK ***/
    Stack StackPerintah;
    CreateEmptyStack(&StackPerintah);

    /*** DEKLARASI UPGRADE TREE ***/
    BinTree T1;
    T1 = Tree(W1, AlokNode(W1_1), AlokNode(W1_2));

    /*** DEKLARASI LIST BARANG ***/
    TabBarang ListBarang;
    MakeEmptyBarang(&ListBarang, 5);
    MakeListBarang(&ListBarang, "Array/Barang/barang.txt");

    /*** DEKLARASI LIST PERINTAH ***/
    // List perintah pada Prep Phase
    TabAction TAPrep;
    MakeEmptyAction(&TAPrep, 7);
    MakeListAction(&TAPrep, "Array/Action/actionPrep.txt");

    // List perintah pada Main Phase
    TabAction TAMain;
    MakeEmptyAction(&TAMain, 6);
    MakeListAction(&TAMain, "Array/Action/actionMain.txt");

    /*** DEKLARASI KATA ***/
    Kata new;
    new = MakeKata("new");

    Kata exitProgram;
    exitProgram = MakeKata("exit");

    // Deklarasi kata untuk input perintah
    Kata First, Nama, PerintahPrep, PerintahMain;

    printf("// Welcome to Willy wangky's fum factory!!//\n");
    printf("// New game / exit? //\n");
    do {
        Input(&First, false); // Input pertama
    } while (!IsKataSama(First,new) && !IsKataSama(First,exitProgram));

    /***** NEW GAME *****/
    if (IsKataSama(First, new)) {
        printf("Memulai permainan baru...\n");
        printf("Masukkan nama:\n");
        Input(&Nama, false);        // Input nama pemain
        printf("Halo, %s\n", Nama.TabKata);
        sleep(1);
        printf("Loading...\n");
        sleep(1);
        printf("Selamat bermain!\n");
        sleep(1);

        /***** DEKLARASI PLAYER *****/
        Player P1, PTemp;
        P1 = MakePlayer(Nama, "Array/Inventory/inventory.txt");
        PTemp = MakePlayer(Nama, "Array/Inventory/inventory.txt");

        /***** DEKLARASI VARIABEL UNIVERSAL *****/
        int day;
        boolean prepPhase;
        boolean mainPhase;
        boolean exit = false;
        day = 1; // Hari ke-day
        prepPhase = true;
        MATRIKS Map1, Map2, Map3, Map4;
        MATRIKS currentMap;

        /***** LOAD MAP *****/
        BacaMATRIKS(&Map1, "FileEksternal/peta1.txt");
        BacaMATRIKS(&Map2, "FileEksternal/peta2.txt");
        BacaMATRIKS(&Map3, "FileEksternal/peta3.txt");
        BacaMATRIKS(&Map4, "FileEksternal/peta4.txt");

        // Penulisan wahana pertama dan player
        Elmt(Map1, 5, 12) = 'W';
        currentMap = Map1;
        Elmt(currentMap, 5, 11) = 'P';
        


        while (!exit) { // Loop pergantian day
            /***** DEKLARASI VARIABEL *****/
            JAM currentJam, closingJam, hourRemaining;
            int timeRemaining;
            Queue Q;
            MakeEmptyQueue(&Q, 5); // Deklarasi queue dan mengosongkan queue.

            POINT PO;
            PO = PosisiOffice(Map1); // Deklarasi Posisi office pada map pertama.

            /***************************************/
            /********** PREPERATION PHASE **********/
            /***************************************/

            currentJam = MakeJAM(21,0); // Deklarasi Jam saat preperation phase.
            closingJam = MakeJAM(9,0);

            while (prepPhase) {
                printf("Preperation day %d\n", day);

                TulisMATRIKS(currentMap);

                /*** Menampilkan detail player ***/
                printf("\n\n");
                printf("Name: %s\n", Name(P1).TabKata);
                printf("Money: %d\n", Money(P1));

                /*** Menampilkan waktu ***/
                timeRemaining = Durasi(currentJam, closingJam);
                hourRemaining = MenitToJAM(timeRemaining);
                printf("Current Time : ");
                TulisJAM(currentJam);
                printf("Closing Time : ");
                TulisJAM(closingJam);
                printf("Time Remaining : ");
                TulisJAM(hourRemaining);
                printf("Temporary ");
                TulisIsiTabInventory(InvPlayer(PTemp));
                PrintStack(StackPerintah);

                /*** Menerima input pengguna ***/
                printf("Masukkan perintah\n");
                Input(&PerintahPrep, false);


                /* **** EKSEKUSI **** */
                if (IsKataSama(PerintahPrep, ElmtAction(TAPrep, 4).Aksi)) {             // Execute
                    /* Memastikan bahwa total durasi dan total uang yang dibutuhkan tidak melebihi batas */
                    if (IsEnough(P1, BiayaStack(StackPerintah)) && DurasiStack(StackPerintah) <= JAMToMenit(hourRemaining)) {
                        Stack S;
                        infoStack X;

                        // Penyimpan posisi player pada current map
                        POINT currentP;
                        currentP = PosisiPlayer(currentMap);

                        /* Membalik stack agar perintah pengguna sesuai dengan urutan */
                        CreateEmptyStack(&S);
                        while (!IsEmptyStack(StackPerintah)) {
                            Pop(&StackPerintah, &X, 0, 0);
                            Push(&S, X, 0, 0);
                        }

                        /* Proses eksekusi perintah dari stack */
                        while (!IsEmptyStack(S)) {
                            Pop(&S, &X, 0, 0);
                            if (X.action == 1) {                                // Buy
                                Buy(&P1, ListBarang, X.idxcode, X.Jumlah);
                            } else if (X.action == 2) {                         // Build
                                /* Pemilihan wahana */
                                addressWahana P;
                                P = FirstLWahana(daftarWahana);
                                for (int i = 0; i < X.idxcode; i++){
                                    P = NextLWahana(P);
                                }
                                /* Pembuatan jenis wahana yang akan dibuild */
                                Wahana WBuild;
                                WBuild.statusWahana = 1;
                                WBuild = P->info;
                                WBuild.lokasiWahana = X.lokasiBuild;
                                WBuild.zona = X.Jumlah;
                                switch (X.Jumlah)   // Zona
                                {
                                case 1:
                                    BuildWahana(WBuild, &P1, &Map1, X.lokasiBuild);
                                    break;
                                case 2:
                                    BuildWahana(WBuild, &P1, &Map2, X.lokasiBuild);
                                    break;
                                case 3:
                                    BuildWahana(WBuild, &P1, &Map3, X.lokasiBuild);
                                    break;
                                case 4:
                                    BuildWahana(WBuild, &P1, &Map4, X.lokasiBuild);
                                    break;
                                default:
                                    break;
                                }
                                /* Memasukkan wahana yang telah dibuild dalam list wahana */
                                InsVLastWahana(&listWahana, WBuild);
                            } else if (X.action == 3) {                         // Upgrade
                                switch (X.Jumlah)   // Zona
                                {
                                case 1:
                                    UpgradeWahana(T1, &P1, &Map1, X.idxcode, X.lokasiBuild, &listWahana, X.Jumlah);
                                    break;
                                case 2:
                                    UpgradeWahana(T1, &P1, &Map2, X.idxcode, X.lokasiBuild, &listWahana, X.Jumlah);
                                    break;
                                case 3:
                                    UpgradeWahana(T1, &P1, &Map3, X.idxcode, X.lokasiBuild, &listWahana, X.Jumlah);
                                    break;
                                case 4:
                                    UpgradeWahana(T1, &P1, &Map4, X.idxcode, X.lokasiBuild, &listWahana, X.Jumlah);
                                    break;
                                default:
                                    break;
                                }
                            }
                        }

                        // Refresh map
                        switch (currentZone)
                        {
                        case 1:
                            currentMap = Map1;
                            break;
                        case 2:
                            currentMap = Map2;
                            break;
                        case 3:
                            currentMap = Map3;
                            break;
                        case 4:
                            currentMap = Map4;
                            break;
                        default:
                            break;
                        }
                        Elmt(currentMap, Ordinat(currentP)+1, Absis(currentP)+1) = 'P';

                        /* Mengosongkan stack */
                        DurasiStack(StackPerintah) = 0;
                        BiayaStack(StackPerintah) = 0;

                        /* Memulai main phase */
                        mainPhase = true;
                        prepPhase = false;
                    } else {
                        printf("Durasi melebihi batas wawktu tersisa!\n");
                    }
                } else if (IsKataSama(PerintahPrep, ElmtAction(TAPrep, 5).Aksi)) {      // Main
                    /* Pengosongan stack tanpa menjalankan eksekusinya */
                    infoStack X;
                    while (!IsEmptyStack(StackPerintah)) {
                        Pop(&StackPerintah, &X, 0, 0);

                        /* Khusus untuk build, maka 'W' yang tertulis pada map akan di-undo menjadi '-' */
                        if (X.action == 2) {
                            int j;
                            addressWahana P;
                            POINT lokBuild = X.lokasiBuild;
                            P = FirstLWahana(daftarWahana);
                            // Mencari jenis wahana yang dibuild
                            for (j = 0; j < X.idxcode; j++) {
                                P = NextLWahana(P);
                            }
                            // Menghapus W pada map
                            switch (X.Jumlah)   // Zona
                            {
                            case 1:
                                Elmt(Map1, Ordinat(lokBuild)+1, Absis(lokBuild)+1) = '-';
                                break;
                            case 2:
                                Elmt(Map2, Ordinat(lokBuild)+1, Absis(lokBuild)+1) = '-';
                                break;
                            case 3:
                                Elmt(Map3, Ordinat(lokBuild)+1, Absis(lokBuild)+1) = '-';
                                break;
                            case 4:
                                Elmt(Map4, Ordinat(lokBuild)+1, Absis(lokBuild)+1) = '-';
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    // Refresh map
                    POINT currentP;
                    currentP = PosisiPlayer(currentMap);
                    switch (currentZone)
                    {
                    case 1:
                        currentMap = Map1;
                        break;
                    case 2:
                        currentMap = Map2;
                        break;
                    case 3:
                        currentMap = Map3;
                        break;
                    case 4:
                        currentMap = Map4;
                        break;
                    default:
                        break;
                    }
                    Elmt(currentMap, Ordinat(currentP)+1, Absis(currentP)+1) = 'P';

                    /* Memulai main phase */
                    mainPhase = true;
                    prepPhase = false;
                }
                /* **** PERGERAKAN **** */
                else if (PerintahPrep.Length == 1) {
                    boolean changeZone;     // Deklarasi pindah zone (true jika berpindah dari satu map ke yang lain)
                    int prevZone;           // Variabel yang menyimpan zona sebelum mulai bergerak
                    if (PerintahPrep.TabKata[0] == 'w') {
                        prevZone = currentZone;
                        Move(&currentMap, 'w', PO, &currentZone);
                        changeZone = prevZone == currentZone;
                        if (!changeZone) {
                            if (currentZone == 1) {                 // Map 3 ke 1
                                CopyMATRIKS(currentMap, &Map3);
                                MoveZone(&currentMap, Map1, '^');
                                PO = PosisiOffice(Map1);
                            }
                             else if (currentZone == 2) {
                                CopyMATRIKS(currentMap, &Map4);     // Map 4 ke 2
                                MoveZone(&currentMap, Map2, '^');
                                PO = MakePOINT(0, 0);
                            }
                        }
                    } else if (PerintahPrep.TabKata[0] == 'a') {
                        prevZone = currentZone;
                        Move(&currentMap, 'a', PO, &currentZone);
                        changeZone = prevZone == currentZone;
                        if (!changeZone) {
                            if (currentZone == 1) {                 // Map 2 ke 1
                                CopyMATRIKS(currentMap, &Map2);
                                MoveZone(&currentMap, Map1, '<');
                                PO = PosisiOffice(Map1);
                            }
                            else if (currentZone == 3) {
                                CopyMATRIKS(currentMap, &Map4);     // Map 4 ke 3
                                MoveZone(&currentMap, Map3, '<');
                                PO = MakePOINT(0, 0);
                            }
                        }
                    } else if (PerintahPrep.TabKata[0] == 's') {
                        prevZone = currentZone;
                        Move(&currentMap, 's', PO, &currentZone);
                        changeZone = prevZone == currentZone;
                        if (!changeZone) {
                            if (currentZone == 3) {                 // Map 1 ke 3
                                CopyMATRIKS(currentMap, &Map1);
                                MoveZone(&currentMap, Map3, 'v');
                                PO = MakePOINT(0, 0);
                            }
                            else if (currentZone == 4) {
                                CopyMATRIKS(currentMap, &Map2);     // Map 2 ke 4
                                MoveZone(&currentMap, Map4, 'v');
                                PO = MakePOINT(0, 0);
                            }
                        }
                    } else if (PerintahPrep.TabKata[0] == 'd') {
                        prevZone = currentZone;
                        Move(&currentMap, 'd', PO, &currentZone);
                        changeZone = prevZone == currentZone;
                        if (!changeZone) {
                            if (currentZone == 2) {                 // Map 1 ke 2
                                CopyMATRIKS(currentMap, &Map1);
                                MoveZone(&currentMap, Map2, '>');
                                PO = MakePOINT(0, 0);
                            }
                            else if (currentZone == 4) {
                                CopyMATRIKS(currentMap, &Map3);     // Map 3 ke 4
                                MoveZone(&currentMap, Map4, '>');
                                PO = MakePOINT(0, 0);
                            }
                        }
                    }
                /* **** PERINTAH **** */
                } else if (IsAksiAda(TAPrep, PerintahPrep)) {
                    Kata inputAksi;
                    if (IsKataSama(PerintahPrep, ElmtAction(TAPrep, 0).Aksi)) {         // Buy
                        int i, j;

                        /* Menampilkan list barang yang dapat dibeli */
                        TulisIsiTabBarang(ListBarang);
                        while (true) {
                            printf("Beli barang nomor : ");
                            Input(&inputAksi, false);
                            i = atoi(inputAksi.TabKata);
                            if (i >= 1 && i <= NbElmtBarang(ListBarang)) break;
                            printf("Input tidak valid, silakan ulangi.\n");
                        }
                        while (true) {
                            printf("Jumlah : ");
                            Input(&inputAksi, false);
                            j = atoi(inputAksi.TabKata);
                            if (j > 0) break;
                            printf("Input tidak valid, silakan ulangi.\n");
                        }

                        /* Mengecek apakah uang player cukup */
                        int B = j * (ListBarang.TIBarang[i-1].Harga); // Harga barang dikali jumlah barang
                        if (IsEnough(PTemp, B)) {
                            infoStack X;
                            int D;

                            /* Memasukkan info pada infostack */
                            X.action = 1;
                            X.idxcode = i;
                            X.Jumlah = j;
                            D = ElmtAction(TAPrep, 0).Durasi;
                            Push(&StackPerintah, X, D, B);

                            /* Mengurangi uang dan inventory player temporer (Bukan P1) */
                            PTemp.Money -= B;
                            switch (i)
                            {
                            case 1:
                                ElmtInventory(PTemp.InvPlayer, 0).Jumlah += j;
                                break;
                            case 2:
                                ElmtInventory(PTemp.InvPlayer, 1).Jumlah += j;
                                break;
                            case 3:
                                ElmtInventory(PTemp.InvPlayer, 2).Jumlah += j;
                                break;
                            default:
                                break;
                            }
                        } else printf("Uang anda tidak mencukupi!\n");

                    } else if (IsKataSama(PerintahPrep, ElmtAction(TAPrep, 1).Aksi)) {  // Build
                        POINT currentP;
                        currentP = PosisiPlayer(currentMap);

                        /* Mengecek apakah 1 blok di atas player kosong */
                        if (Elmt(currentMap, Ordinat(currentP), Absis(currentP)+1) != '-') {
                            char C = Elmt(currentMap, Ordinat(currentP), Absis(currentP)+1);
                            printf("Tidak bisa membangun! Ada ");
                            switch (C)
                            {
                            case '*':
                                printf("tembok ");
                                break;
                            case 'O':
                                printf("office ");
                                break;
                            case 'A':
                                printf("antrian ");
                                break;
                            case '^':
                                printf("gerbang ");
                                break;
                            default:
                                printf("wahana ");
                                break;
                            } printf("di atas.\n");
                        }
                        /* Jika kosong, dijalankan perintah build */
                        else {
                            int i;
                            PrintInfoWahana(daftarWahana);
                                while (true) {
                                printf("Bangun wahana nomor : ");
                                Input(&inputAksi, false);
                                i = atoi(inputAksi.TabKata);
                                if (i >= 1 && i <= NbElmtWahana(daftarWahana)) break;
                                printf("Input tidak valid, silakan ulangi.\n");
                            }
                            // Loop ke index wahana yang dipilih
                            addressWahana P;
                            P = FirstLWahana(daftarWahana);
                            for (int j = 0; j < i-1; j++) {
                                P = NextLWahana(P);
                            }


                            Wahana WBuild;
                            WBuild = P->info;
                            int B = WBuild.biayaBuild;

                            // Pengecekan apakah uang dan material player akan cukup
                            if (IsEnough(PTemp, WBuild.biayaBuild) && IsEnoughMaterial(PTemp, WBuild)) {
                                infoStack X;
                                POINT currentP;
                                int D;
                                D = ElmtAction(TAPrep, 1).Durasi;

                                X.action = 2;
                                X.Jumlah = currentZone;
                                X.idxcode = i-1;
                                currentP = PosisiPlayer(currentMap);
                                X.lokasiBuild = MakePOINT(Absis(currentP), Ordinat(currentP)-1);

                                Push(&StackPerintah, X, D, B);

                                // Menuliskan W pada map sekaligus refresh map
                                switch (currentZone)
                                {
                                case 1:
                                    Elmt(Map1, Ordinat(currentP), Absis(currentP)+1) = 'W';
                                    currentMap = Map1;
                                    break;
                                case 2:
                                    Elmt(Map2, Ordinat(currentP), Absis(currentP)+1) = 'W';
                                    currentMap = Map2;
                                    break;
                                case 3:
                                    Elmt(Map3, Ordinat(currentP), Absis(currentP)+1) = 'W';
                                    currentMap = Map3;
                                    break;
                                case 4:
                                    Elmt(Map4, Ordinat(currentP), Absis(currentP)+1) = 'W';
                                    currentMap = Map4;
                                    break;
                                default:
                                    break;
                                }

                                Elmt(currentMap, Ordinat(currentP)+1, Absis(currentP)+1) = 'P';
                                
                                /* Mengurangi uang dan inventory player temporer (Bukan P1) */
                                PTemp.Money -= B;
                                ElmtInventory(PTemp.InvPlayer, 0).Jumlah -= WBuild.wood;
                                ElmtInventory(PTemp.InvPlayer, 1).Jumlah -= WBuild.steel;
                                ElmtInventory(PTemp.InvPlayer, 2).Jumlah -= WBuild.iron;
                            } else {
                                if (!IsEnough(PTemp, B)) {
                                    printf("Uang anda tidak akan mencukupi!\n");
                                }
                                if (!IsEnoughMaterial(PTemp, WBuild)) {
                                    printf("Material anda tidak akan mencukupi!\n");
                                }
                            }
                        }
                        sleep(1);
                    } else if (IsKataSama(PerintahPrep, ElmtAction(TAPrep, 2).Aksi)) {  // Upgrade

                        /* Pengecekan apakah ada wahana di sekitar player untuk diupgrade */
                        if (AdaBangunanSekitarPlayer(currentMap, PosisiPlayer(currentMap))) {
                            int i;
                            printf("Upgrade %s menjadi ?\n", Akar(T1).namaWahana.TabKata);
                            printf("\t1. %s (Biaya : %d)\n", Akar(Left(T1)).namaWahana.TabKata, Akar(Left(T1)).biayaUpgrade);
                            printf("\t\tMaterial needed : Wood x%d, Steel x%d, Iron x%d\n", Akar(Left(T1)).wood, Akar(Left(T1)).steel, Akar(Left(T1)).iron);
                            printf("\t2. %s (Biaya : %d)\n", Akar(Right(T1)).namaWahana.TabKata, Akar(Right(T1)).biayaUpgrade);
                            printf("\t\tMaterial needed : Wood x%d, Steel x%d, Iron x%d\n", Akar(Right(T1)).wood, Akar(Right(T1)).steel, Akar(Right(T1)).iron);

                            /* Looping input upgrade (1 = Kiri, 2 = kanan) */
                            while (true) {
                                printf("Input: ");
                                Input(&inputAksi, false);
                                i = atoi(inputAksi.TabKata);
                                if (i == 1 || i == 2) break;
                                printf("Input invalid! Silakan input kembali.\n");
                            }
                            // Mengecek biaya upgrade dan wahana tujuan upgrade
                            int B;
                            Wahana WUp;
                            switch (i)
                            {
                            case 1:
                                WUp = Akar(Left(T1));
                                B = Akar(Left(T1)).biayaUpgrade;
                                break;
                            case 2:
                                WUp = Akar(Right(T1));
                                B = Akar(Right(T1)).biayaUpgrade;
                                break;
                            default:
                                break;
                            }

                            // Mengecek apakah uang dan material player akan cukup
                            if (IsEnough(PTemp, B) && IsEnoughMaterial(PTemp, WUp)) {
                                infoStack X;
                                int D;

                                X.action = 3;
                                X.Jumlah = currentZone;
                                switch (currentZone)
                                {
                                case 1:
                                    X.matriks = Map1;
                                    break;
                                case 2:
                                    X.matriks = Map2;
                                    break;
                                case 3:
                                    X.matriks = Map3;
                                    break;
                                case 4:
                                    X.matriks = Map4;
                                    break;
                                default:
                                    break;
                                }
                                X.idxcode = i;
                                X.lokasiBuild = BangunanSekitarPlayer(currentMap, PosisiPlayer(currentMap));
                                D = ElmtAction(TAPrep, 2).Durasi;

                                Push(&StackPerintah, X, D, B);

                                PTemp.Money -= B;
                                ElmtInventory(PTemp.InvPlayer, 0).Jumlah -= WUp.wood;
                                ElmtInventory(PTemp.InvPlayer, 1).Jumlah -= WUp.steel;
                                ElmtInventory(PTemp.InvPlayer, 2).Jumlah -= WUp.iron;
                            } else {
                                if (!IsEnough(PTemp, B)) {
                                    printf("Uang anda tidak akan mencukupi!\n");
                                }
                                if (!IsEnoughMaterial(PTemp, WUp)) {
                                    printf("Material anda tidak akan mencukupi!\n");
                                }
                            }
                        } else {
                            printf("Tidak ada wahana sekitar player.\n");
                        }
                        sleep(1);
                    } else if (IsKataSama(PerintahPrep, ElmtAction(TAPrep, 3).Aksi)) {  // Undo
                        if (!IsEmptyStack(StackPerintah)) {
                            infoStack X;

                            // Pop perintah terakhir dari stack
                            Pop(&StackPerintah, &X, 0, 0);
                            switch (X.action)
                            {
                            case 1:                                     // Undo Buy
                                /* Mengembalikan material dari inventory temporer player */
                                /* Mengurangi total durasi dan biaya pada stack yang tercatat */
                                DurasiStack(StackPerintah) -= 30;
                                BiayaStack(StackPerintah) -= X.Jumlah * ElmtBarang(ListBarang, X.idxcode-1).Harga;
                                ElmtInventory(PTemp.InvPlayer, X.idxcode-1).Jumlah -= X.Jumlah;
                                PTemp.Money += X.Jumlah * ElmtBarang(ListBarang, X.idxcode-1).Harga;
                                break;
                            case 2:                                     // Undo Build
                                /* Mengembalikan material pada inventory temporer player */
                                DurasiStack(StackPerintah) -= 120;
                                addressWahana P;
                                POINT lokBuild = X.lokasiBuild;
                                P = FirstLWahana(daftarWahana);
                                for (int j = 0; j < X.idxcode; j++) {
                                    P = NextLWahana(P);
                                }
                                BiayaStack(StackPerintah) -= P->info.biayaBuild;
                                ElmtInventory(PTemp.InvPlayer, 0).Jumlah += P->info.wood;
                                ElmtInventory(PTemp.InvPlayer, 1).Jumlah += P->info.steel;
                                ElmtInventory(PTemp.InvPlayer, 2).Jumlah += P->info.iron;
                                PTemp.Money += P->info.biayaBuild;
                                // Menghapus W pada map
                                switch (X.Jumlah)   // Zona
                                {
                                case 1:
                                    Elmt(Map1, Ordinat(lokBuild)+1, Absis(lokBuild)+1) = '-';
                                    break;
                                case 2:
                                    Elmt(Map2, Ordinat(lokBuild)+1, Absis(lokBuild)+1) = '-';
                                    break;
                                case 3:
                                    Elmt(Map3, Ordinat(lokBuild)+1, Absis(lokBuild)+1) = '-';
                                    break;
                                case 4:
                                    Elmt(Map4, Ordinat(lokBuild)+1, Absis(lokBuild)+1) = '-';
                                    break;
                                default:
                                    break;
                                }

                                // Refresh map
                                POINT currentP;
                                currentP = PosisiPlayer(currentMap);
                                switch (currentZone)
                                {
                                case 1:
                                    currentMap = Map1;
                                    break;
                                case 2:
                                    currentMap = Map2;
                                    break;
                                case 3:
                                    currentMap = Map3;
                                    break;
                                case 4:
                                    currentMap = Map4;
                                    break;
                                default:
                                    break;
                                }
                                Elmt(currentMap, Ordinat(currentP)+1, Absis(currentP)+1) = 'P';
                                break;
                            case 3:                                     // Undo Upgrade
                                DurasiStack(StackPerintah) -= 180;
                                int B;
                                /* Mengecek upgrade pilihan (1 = kiri, 2 = kanan) */
                                if (X.idxcode == 1) { // Upgrade kiri
                                    B = Akar(Left(T1)).biayaUpgrade;
                                    ElmtInventory(PTemp.InvPlayer, 0).Jumlah += Akar(Left(T1)).wood;
                                    ElmtInventory(PTemp.InvPlayer, 1).Jumlah += Akar(Left(T1)).steel;
                                    ElmtInventory(PTemp.InvPlayer, 2).Jumlah += Akar(Left(T1)).iron;
                                    PTemp.Money += B;
                                } else {
                                    B = Akar(Left(T1)).biayaUpgrade;
                                    ElmtInventory(PTemp.InvPlayer, 0).Jumlah += Akar(Right(T1)).wood;
                                    ElmtInventory(PTemp.InvPlayer, 1).Jumlah += Akar(Right(T1)).steel;
                                    ElmtInventory(PTemp.InvPlayer, 2).Jumlah += Akar(Right(T1)).iron;
                                    PTemp.Money += B;
                                }
                                BiayaStack(StackPerintah) -= B;
                                break;

                            default:
                                break;
                            }
                        }

                        else {
                            printf("Tak ada aksi!\n");
                        }
                    }
                    sleep(1);
                } else if (IsKataSama(PerintahPrep, exitProgram)) {
                    return 0;
                } else {
                    printf("Command tidak ditemukan.\n");
                }
            }

            ElmtInventory(PTemp.InvPlayer, 0) = ElmtInventory(P1.InvPlayer, 0);
            ElmtInventory(PTemp.InvPlayer, 1) = ElmtInventory(P1.InvPlayer, 1);
            ElmtInventory(PTemp.InvPlayer, 2) = ElmtInventory(P1.InvPlayer, 2);

            /********************************/
            /********** MAIN PHASE **********/
            /********************************/

            currentJam = MakeJAM(9,0); // Deklarasi Jam saat main phase.
            closingJam = MakeJAM(21,0);

            while (mainPhase && JLT(currentJam, closingJam)) {
                printf("Main day %d\n", day);

                TulisMATRIKS(currentMap);

                printf("\n\n");

                printf("Name: %s\n", Name(P1).TabKata);
                printf("Money: %d\n", Money(P1));

                timeRemaining = Durasi(currentJam, closingJam);
                hourRemaining = MenitToJAM(timeRemaining);
                printf("Current Time : ");
                TulisJAM(currentJam);
                printf("Closing Time : ");
                TulisJAM(closingJam);
                printf("Time Remaining : ");
                TulisJAM(hourRemaining);

                // Randomizer wahana rusak
                if (rand() % 30 == 1) { // 3,33% kemungkinan setiap command untuk rusak
                    addressWahana R;
                    int random = rand() % NbElmtWahana(listWahana);
                    R = FirstLWahana(listWahana);
                    for (int j = 0; j < random; j++) {
                        R = NextLWahana(R);
                    }
                    R->info.statusWahana = 0;
                }

                // Pengurangan pengunjung dalam wahana tiap 'durasi-wahana' menit
                if (JAMToMenit(currentJam) % 10 == 0) {
                    addressWahana P;
                    P = FirstLWahana(listWahana);
                    /* Pengurangan 1 pengunjung dari setiap wahana untuk setiap 10 menit */
                    for (int i = 0; i < NbElmtWahana(listWahana); i++) {
                        if (P->info.jumlahPemainWahana > 0) P->info.jumlahPemainWahana--;
                        P = NextLWahana(P);
                    }
                }

                // Print list wahana rusak (Jika ada)
                PrintWahanaRusak(listWahana);

                // Randomizer untuk menambahkan pengunjung (dirandom setiap aksi)
                if (rand() % 5 == 1) {
                    EnqueuePrio(&Q, listWahana);
                }
                PrintAntrian(Q);

                printf("Masukkan perintah ");
                /* Menampilkan perintah khusus jika player dalam office */
                if (IsInOffice(currentMap, PO)) {
                    printf("(Masukkan 'office' untuk mengakses office) ");
                }
                printf(":\n");
                Input(&PerintahMain, false);

                if (IsKataSama(PerintahMain, ElmtAction(TAMain, 4).Aksi)) { // prepare
                    mainPhase = false;
                    prepPhase = true;
                }
                /**** PERGERAKAN ****/
                else if (PerintahMain.Length == 1) {
                    boolean changeZone;
                    int prevZone;
                    if (PerintahMain.TabKata[0] == 'w') {
                        //KurangKesabaran(&Q);
                        prevZone = currentZone;
                        Move(&currentMap, 'w', PO, &currentZone);
                        changeZone = prevZone == currentZone;
                        if (!changeZone) {
                            if (currentZone == 1) {                 // Map 3 ke 1
                                CopyMATRIKS(currentMap, &Map3);
                                MoveZone(&currentMap, Map1, '^');
                                PO = PosisiOffice(Map1);
                            }
                             else if (currentZone == 2) {
                                CopyMATRIKS(currentMap, &Map4);     // Map 4 ke 2
                                MoveZone(&currentMap, Map2, '^');
                                PO = MakePOINT(0, 0);
                            }
                        }
                        currentJam = NextNMenit(currentJam, 1);
                    } else if (PerintahMain.TabKata[0] == 'a') {
                        //KurangKesabaran(&Q);
                        prevZone = currentZone;
                        Move(&currentMap, 'a', PO, &currentZone);
                        changeZone = prevZone == currentZone;
                        if (!changeZone) {
                            if (currentZone == 1) {                 // Map 2 ke 1
                                CopyMATRIKS(currentMap, &Map2);
                                MoveZone(&currentMap, Map1, '<');
                                PO = PosisiOffice(Map1);
                            }
                            else if (currentZone == 3) {
                                CopyMATRIKS(currentMap, &Map4);     // Map 4 ke 3
                                MoveZone(&currentMap, Map3, '<');
                                PO = MakePOINT(0, 0);
                            }
                        }
                        currentJam = NextNMenit(currentJam, 1);
                    } else if (PerintahMain.TabKata[0] == 's') {
                        //KurangKesabaran(&Q);
                        prevZone = currentZone;
                        Move(&currentMap, 's', PO, &currentZone);
                        changeZone = prevZone == currentZone;
                        if (!changeZone) {
                            if (currentZone == 3) {                 // Map 1 ke 3
                                CopyMATRIKS(currentMap, &Map1);
                                MoveZone(&currentMap, Map3, 'v');
                                PO = MakePOINT(0, 0);
                            }
                            else if (currentZone == 4) {
                                CopyMATRIKS(currentMap, &Map2);     // Map 2 ke 4
                                MoveZone(&currentMap, Map4, 'v');
                                PO = MakePOINT(0, 0);
                            }
                        }
                        currentJam = NextNMenit(currentJam, 1);
                    } else if (PerintahMain.TabKata[0] == 'd') {
                        //KurangKesabaran(&Q);
                        prevZone = currentZone;
                        Move(&currentMap, 'd', PO, &currentZone);
                        changeZone = prevZone == currentZone;
                        if (!changeZone) {
                            if (currentZone == 2) {                 // Map 1 ke 2
                                CopyMATRIKS(currentMap, &Map1);
                                MoveZone(&currentMap, Map2, '>');
                                PO = MakePOINT(0, 0);
                            }
                            else if (currentZone == 4) {
                                CopyMATRIKS(currentMap, &Map3);     // Map 3 ke 4
                                MoveZone(&currentMap, Map4, '>');
                                PO = MakePOINT(0, 0);
                            }
                        }
                        currentJam = NextNMenit(currentJam, 1);
                    }
                /**** PERINTAH ****/
                }
                else if (IsAksiAda(TAMain, PerintahMain)) {
                    Kata InputAksi;
                    if (IsKataSama(PerintahMain, ElmtAction(TAMain, 3).Aksi)) { // office
                        /* Mengecek apakah player dalam office */
                        if (IsInOffice(currentMap,PO))
                        {
                            /* Deklarasi sebagai input perintah dalam office */
                            Kata Details = MakeKata("Details");
                            Kata Report = MakeKata("Report");
                            Kata Exit = MakeKata("Exit");

                            printf("Masuk office\n");

                            do {
                                // Input aksi dalam office
                                printf("Masukkan perintah : Details / Report / Exit\n");
                                while (true) {
                                    Input(&InputAksi, false);
                                    if (IsKataSama(InputAksi, Details) || IsKataSama(InputAksi, Report) || IsKataSama(InputAksi, Exit)) break;
                                    printf("Perintah invalid! silakan input kembali.\n");
                                }

                                if (IsKataSama(InputAksi, Details)) {
                                    int i;

                                    // Input wahana yang ingin dilihat detailsnya
                                    printf("Pilih wahana yang akan ditampilkan detailnya :\n");
                                    PrintInfoWahana(listWahana);
                                    while (true) {
                                        Input(&InputAksi, false);
                                        i = atoi(InputAksi.TabKata);
                                        if (i >= 1 && i <= NbElmtWahana(listWahana)) break;
                                        printf("Input invalid! silakan input kembali.\n");
                                    }

                                    // Menggeser address P hingga sesuai dengan wahwana yang dituju
                                    addressWahana P;
                                    P = FirstLWahana(listWahana);
                                    for (int j = 0; j < i-1; j++) {
                                        P = NextLWahana(P);
                                    }

                                    // Membuka detail wahana yang ditunjuk address P
                                    Detail(P->info);
                                    printf("History     : ");
                                    PrintHistoryWahana(P);
                                } else if (IsKataSama(InputAksi, Report)) {
                                    int i;

                                    // Input wahana yang ingin dilihat reportsnya
                                    printf("Pilih wahana yang akan ditampilkan reportnya :\n");
                                    PrintInfoWahana(listWahana);
                                    while (true) {
                                        Input(&InputAksi, false);
                                        i = atoi(InputAksi.TabKata);
                                        if (i >= 1 && i <= NbElmtWahana(listWahana)) break;
                                        printf("Input invalid! silakan input kembali.\n");
                                    }

                                    // Menggeser address P hingga sesuai dengan wahwana yang dituju
                                    addressWahana P;
                                    P = FirstLWahana(listWahana);
                                    for (int j = 0; j < i-1; j++) {
                                        P = NextLWahana(P);
                                    }

                                    // Menampilkan report wahana yang ditunjuk oleh address P
                                    ReportWahana(P);
                                }
                            } while (!IsKataSama(InputAksi, Exit));
                            KurangKesabaran(&Q);
                        }
                        else
                        {
                            printf("Anda tidak berada di office\n");
                        }
                    } else if (IsKataSama(PerintahMain, ElmtAction(TAMain, 0).Aksi)) {  // serve
                        KurangKesabaran(&Q);
                        /* Mengecek apabila player berada di sebelah antrian atau tidak */
                        if (AdaAntrianSekitarPlayer(currentMap, PosisiPlayer(currentMap))) {
                            printf("Anda sekitar antrian.\n");
                            serve(&Q, &P1, &listWahana);
                        } else {
                            printf("Anda tidak berada di sekitar antrian. Tidak dapat melakukan serve.\n");
                        }
                        /* Menambahkan jam sesuai dengan durasi serve yang telah ditentukan */
                        currentJam = NextNMenit(currentJam, ElmtAction(TAMain, 0).Durasi);
                    } else if (IsKataSama(PerintahMain, ElmtAction(TAMain, 2).Aksi)) {  // Details

                        /* Mengecek apakah ada wahana di sekitar player */
                        if (AdaBangunanSekitarPlayer(currentMap, PosisiPlayer(currentMap))){
                            /* Menentukan lokasi wahana yang akan dicek detailsnya */
                            POINT building = BangunanSekitarPlayer(currentMap, PosisiPlayer(currentMap));

                            /* Menerima address P dari lokasi wahana yang akan dicek detailnya */
                            addressWahana P = SerachWahanaLokasi(listWahana, building, currentZone);

                            /* Akses terhadap detail dari wahana yang ditunjuk oleh P */
                            Detail(P->info);
                        } else printf("Tidak ada building di sekitar.\n");
                    }
                    else if (IsKataSama(PerintahMain,  ElmtAction(TAMain, 1).Aksi)) {   //Repair
                        KurangKesabaran(&Q);
                        /* Mengecek apabila ada wahana di sekitar player */
                        if (AdaBangunanSekitarPlayer(currentMap, PosisiPlayer(currentMap)))
                        {
                            /* Deklarasi address pointer untuk elemen list wahana */
                            addressWahana P;
                            P = FirstLWahana(listWahana);
                            POINT BangunanSekitar, BangunanTerdaftar;

                            /* Mengecek lokasi wahana di sekitar player */
                            BangunanSekitar = BangunanSekitarPlayer(currentMap, PosisiPlayer(currentMap));

                            /* Mengecek apakah lokasi wahana tersebut merupakan lokasi wahana yang sedang rusak */
                            BangunanTerdaftar = PosisiWahanaRusak(listWahana, BangunanSekitar);

                            /* Mengecek apabila benar bahwa lokasi wahana merupakan lokasi wahana yang rusak */
                            if ((BangunanSekitar.X == BangunanTerdaftar.X) && (BangunanSekitar.Y == BangunanTerdaftar.Y))
                            {
                                /* Looping hingga ditemukan Wahana dalam list wahana yang lokasinya bersesuaian */
                                while (!EQ(BangunanTerdaftar, InfoLWahana(P).lokasiWahana))
                                {
                                    P = NextLWahana(P);
                                }

                                /* Mengembalikan status wahana menjadi true (berfungsi) */
                                InfoLWahana(P).statusWahana = true;
                                currentJam = NextNMenit(currentJam, 20);
                            }
                            else
                            {
                                printf("Tidak ada wahana yang rusak di sekitar player\n");
                            }
                        }
                        else
                        {
                            printf("Tidak ada bangunan di sekitar player\n");
                        }
                    }
                    sleep(1);
                } else if (IsKataSama(PerintahMain, exitProgram)) {                 // Exit program
                    return 0;
                }
                else {
                    printf("Command tidak ditemukan.\n");
                }
                if (!JLT(currentJam, closingJam)) {
                    mainPhase = false;
                    prepPhase = true;
                }
            }
            day++;
            PTemp.Money = P1.Money;
            /* Reset Laporan harian */
            addressWahana Clr;
            Clr = FirstLWahana(listWahana);
            for (int i = 0; i < NbElmtWahana(listWahana); i++) {
                Clr->laporan.dinaikiHari = 0;
                Clr->laporan.penghasilanHari = 0;
                Clr = NextLWahana(Clr);
            }
        }
    }

    else if (IsKataSama(First, exitProgram)) { // Exit program
        printf("Exiting game..");
        sleep(1);
        printf(".");
        sleep(1);
        printf(".\n");
    }

    return 0;
}
