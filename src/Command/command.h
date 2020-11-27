#ifndef command_H
#define command_H

#include "../boolean.h"
#include "../Matriks/matriks.h"
#include "../Player/player.h"
#include "../Array/arraydinbarang.h"
#include "../Wahana/wahana.h"
#include "../Tree/bintree.h"

// Buy material
void Buy(Player * P, TabBarang B, IdxTypeBarang i, int Jumlah);

// Membuat wahana baru
void BuildWahana(Wahana W, Player * P, MATRIKS * M, boolean * success);

// Mengupgrade wahana
void UpgradeWahana(BinTree T, Player * P, MATRIKS *M);

#endif