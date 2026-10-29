#include <stdio.h>
#include <stdlib.h>

#define HAVUZ_BOYUTU 4

typedef struct Dugum {
    int veri;
    struct Dugum *sonraki;
} Dugum;

static Dugum havuz[HAVUZ_BOYUTU]; /* 4 düğümlük sabit dizi */
static Dugum *bos_liste = NULL;   /* boş düğümler listesinin başı */
static int bos_sayisi = 0;       /* kaç boş düğüm kaldı */

void havuzu_baslat(void){
    for(int i = 0; i<HAVUZ_BOYUTU; i++){
        havuz[i].sonraki = &havuz[i+1];  /* her düğüm bir sonrakini göstersin */

    }
    havuz[HAVUZ_BOYUTU -1].sonraki = NULL; /* son düğüm kimseyi göstermesin */
    bos_liste = &havuz[0];                /* boş listeyi ilk elemana bağla */
    bos_sayisi = HAVUZ_BOYUTU;            /* boş düğüm sayısını ayarla */

}

Dugum *havuz_al(void) {
    if (bos_liste == NULL) {
        return NULL;                /* havuz tükendi */
    }
    Dugum *d = bos_liste;           /* baştaki boş düğümü al */
    bos_liste = d->sonraki;         /* boş listenin başı bir sonrakine geçsin */
    d->sonraki = NULL;              /* alınan düğüm artık havuza bağlı olmasın */
    bos_sayisi--;
    return d;
}

void havuz_ver(Dugum *d) {
    if (d == NULL) {
        return;                     /* NULL verilirse hiçbir şey yapma */
    }
    d->sonraki = bos_liste;         /* geri verilen düğüm, eski başı göstersin */
    bos_liste = d;                  /* boş listenin başı artık bu düğüm */
    bos_sayisi++;
}

Dugum *dugum_olustur(int deger){
    Dugum *yeni = havuz_al();
    if (yeni == NULL){
        return NULL;
    }
    yeni->veri = deger;
    yeni->sonraki = NULL;
    return yeni;
}

Dugum *basa_ekle(Dugum *bas, int deger){
    Dugum *yeni = dugum_olustur(deger);
    if (yeni == NULL){
        return bas;
    }
    yeni->sonraki = bas;
    return yeni;
}

Dugum *diziden_listele(const int *dizi, int n){
    Dugum *bas = NULL;
    for(int i = n-1; i >=0; i--){
        bas = basa_ekle(bas,dizi[i]);
    }
    return bas;
}

int havuz_bos_sayisi(void) {
    return bos_sayisi;
}

void test_listeyi_silince_havuz_dolar(void) {
    havuzu_baslat();                                   /* Hazırla */
    int baslangic[] = {10, 20, 30};
    Dugum *bas = diziden_liste(baslangic, 3);
    assert(havuz_bos_sayisi() == 1);                  /* 3 düğüm kullanıldı */

    listeyi_sil(bas);                                 /* Çalıştır */

    assert(havuz_bos_sayisi() == HAVUZ_BOYUTU);       /* Doğrula: hepsi geri geldi */
}


// void test_havuz_tukenmesi(void){
//     havuzu_baslat();

//     int baslangic[] = {10, 20, 30, 40};
//     Dugum *bas = diziden_liste(baslangic, 4);

//     assert(havuz_bos_sayisi()==0);

//     Dugum *d5 = havuz_al();
//     assert(d5 == NULL);

//     listeyi_sil(bas);
// }

void test_havuz_tukenmesi(void) {
    havuz_baslat();                                   /* Hazırla */
    Dugum *alinanlar[HAVUZ_BOYUTU];

    for (int i = 0; i < HAVUZ_BOYUTU; i++) {          /* Çalıştır: havuzu tüket */
        alinanlar[i] = havuz_al();
        assert(alinanlar[i] != NULL);                 /* her biri başarılı olmalı */
    }
    assert(havuz_bos_sayisi() == 0);

    Dugum *fazladan = havuz_al();                     /* 5. istek */
    assert(fazladan == NULL);                         /* Doğrula: tükenme */
}