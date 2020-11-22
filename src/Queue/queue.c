/* File: queue.c */
/* Implementasi Queue */
/* Model Implementasi Versi III dengan Priority Queue */

#include <stdio.h>
#include "queue.h"
#include "../boolean.h"
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q){
/* Mengirim true jika Q kosong: lihat definisi di atas */
    return ((Head(Q)==Nil) && (Tail(Q)==Nil));
}
boolean IsFull (Queue Q){
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
    return (NBElmt(Q) == MaxEl(Q));
}
int NBElmt (Queue Q){
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
    int count;
    int el = MaxEl(Q);
    if (IsEmpty(Q)){
        return 0;
    } else {
        count = (((Tail(Q)-Head(Q) + el) % el) + 1);
        return count;
    }
}
/* *** Kreator *** */
void MakeEmptyQueue (Queue * Q, int Max){
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
    (*Q).T = (pengunjung *)malloc(Max * sizeof(pengunjung));
    if ((*Q).T != NULL) {
        MaxEl(*Q) = Max;
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    } else {
        MaxEl(*Q) = 0;
    }
}
/* *** Destruktor *** */
void DeAlokasi(Queue * Q){
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
    MaxEl(*Q) = 0;
    free((*Q).T);
}
/* *** Primitif Add/Delete *** */
void EnqueuePrio (Queue * Q){
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
    address i,prev;
    pengunjung X,QTemp;

    if (!IsFull(*Q)){
        JumlahOrang(X) = 1;
        Kesabaran(X) = 5;   //Inisiasi kesabaran awal tiap pengunjung
        //Jika antrian masih kosong, maka tambahkan langsung pengunjung tersebut
        if (IsEmpty(*Q)){
            Head(*Q) = 1;
            Tail(*Q) = 1;
            InfoTail(*Q) = X;
        //Jika sudah terisi
        } else {
            if (Tail(*Q) == MaxEl(*Q)){
                Tail(*Q) = 1;
            } else {
                Tail(*Q) = Tail(*Q) + 1;
            }
            InfoTail(*Q) = X;
        }
        i = Tail(*Q);
        if (i == 1){
            prev = MaxEl(*Q);
        } else {
            prev = i - 1;
        }

        //Priority queue dengan tingkat kesabaran yang lebih rendah ke tinggi
        while ((Kesabaran(ElmtQueue(*Q,i)) < Kesabaran(ElmtQueue(*Q,prev))) && (i != Head(*Q))){
            QTemp = ElmtQueue(*Q,i);
            ElmtQueue(*Q,i) = ElmtQueue(*Q,prev);
            ElmtQueue(*Q,prev) = QTemp;

            i = i-1;
            prev = prev-1;
            if (i < 1){
                i = MaxEl(*Q);
            } if (prev < 1){
                prev = MaxEl(*Q);
            }
        }
    } else { //Jika antrian sudah mencapai max
            printf("Antrian sudah penuh.\n");
    }
}
void Dequeue (Queue * Q, pengunjung * X){
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
    if (!IsEmpty(*Q)){
          *X = InfoHead(*Q);
          if (Head(*Q) == Tail(*Q)){
               Head(*Q) = Nil;
               Tail(*Q) = Nil;
          }
          else {
               int orang = Head(*Q);
               while (orang < Tail(*Q)){
                    ElmtQueue(*Q,orang) = ElmtQueue(*Q,orang+1);
                    orang = orang + 1;
               }
               Tail(*Q) = orang-1;
          }
    }
}
void KurangKesabaran (Queue * Q){
/* I.S. Q terdefinisi, mengurangi jumlah kesabaran yang dimiliki pengunjung sebanyak 1 satuan */
/* F.S. Kesabaran pengunjung berkurang satu */
    pengunjung X;
    //JIka tidak kosong
    if (!IsEmpty(*Q)){
        int orang = Head(*Q);
        while (orang < Tail(*Q)){ //Mengurangi kesabaran pengunjung sesuai prioritas kedatangannya.
            Kesabaran(ElmtQueue(*Q,orang)) = Kesabaran(ElmtQueue(*Q,orang)) - 1;
            orang = orang + 1;
        }
        //Jika kesabaran sudah 0 dan di antrian masih ada pengunjung maka pengunjung yang habis kesabarannya di Dequeue
        while (InfoHeadKesabaran(*Q) == 0 && !IsEmpty(*Q)){
            Dequeue(Q,&X);
        }
    }
}
void PrintAntrian (Queue Q){
/* I.S. Q terdefinisi, Q mungkin kosong */
/* F.S. Isi dari Antrian itu ditampilkan ke layar
        "Antrian [2/5]:
         (Daftar Wahana), kesabaran: 5
         (Daftar Wahana), kesabaran: 5 */
    if (IsEmpty(Q)){
          printf("Antrian [0/5]: \n");
          printf("Tidak ada antrian\n");
     }
     else {
          int orang = Head(Q);
          printf("Antrian [%d/5]:", NBElmt(Q)); printf("\n");
          while (orang<=Tail(Q)){
              printf("(Daftar wahana)");
              printf(", kesabaran: %d\n", Q.T[orang].kesabaran);
              orang = orang + 1;
          }
     }
}
