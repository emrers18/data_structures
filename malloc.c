#include <stdio.h>
#include <stdlib.h>


typedef struct Dugum {
    int veri;
    struct Dugum *sonraki;
} Dugum;

Dugum *dugum_olustur(int deger){
    Dugum *yeni = malloc(sizeof(Dugum));

    if(yeni == NULL){
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

void listeyi_yazdir(Dugum *bas){
    Dugum *simdiki = bas;
    while(simdiki != NULL){
        printf("%d -> ", simdiki->veri);
        simdiki = simdiki->sonraki;
    }
    printf("NULL\n");
}

Dugum *sil(Dugum *bas, int deger){

    // Durum 1: liste boş
    if(bas == NULL){
        return NULL;
    }

    // Durum 2: silinecek düğüm baştaki
    if(bas->veri == deger){
        Dugum *yeni_bas = bas->sonraki;
        free(bas);
        return yeni_bas;
    }

    // Durum 3: ortada ya da sonda
    Dugum *onceki = bas;
    while(onceki->sonraki != NULL && onceki->sonraki->veri != deger){
        onceki=onceki->sonraki;
    }

    if(onceki->sonraki != NULL){
        Dugum *silinecek = onceki->sonraki;
        onceki->sonraki = silinecek->sonraki;
        free(silinecek);
    }

    return bas;
}

void tum_listeyi_sil(Dugum *bas){
    while(bas != NULL){
        Dugum *siradaki = bas->sonraki;
        free(bas);
        bas = siradaki;
    }
}


int main(void){
    int *p = malloc(sizeof(int)) //bir intlik yer iste


    /*
        Bu kontrol her zaman yapılmalı. 
        Bellek bitmişse malloc NULL döner 
        ve NULL adresine yazmak programı çökertir.
    */
    if (p == NULL){
        printf("Bellek Yetersiz! \n");
        return 1;
    }

    *p = 42; // aldığmız yere 42 yaz
    printf("%d\n", *p); // 42

    free(p); // yeri geri ver
    p = NULL; // sonra kullanma (işaretçi çöplüğü olmasın)

    Dugum *bas = NULL;

    bas = basa_ekle(bas, 30);
    bas = basa_ekle(bas, 20);
    bas = basa_ekle(bas, 10);
    listeyi_yazdir(bas);          /* 10 -> 20 -> 30 -> NULL */

    bas = sil(bas, 20);           /* ortadakini sil */
    listeyi_yazdir(bas);          /* 10 -> 30 -> NULL */

    bas = sil(bas, 10);           /* baştakini sil */
    listeyi_yazdir(bas);          /* 30 -> NULL */

    bas = sil(bas, 99);           /* olmayan değer */
    listeyi_yazdir(bas);          /* 30 -> NULL (değişmedi) */

    listeyi_sil(bas);
    bas = NULL;

    return 0;
}