#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

Dugum *diziden_listele(const int *dizi, int n){
    Dugum *bas = NULL;
    for(int i = n-1; i >=0; i--){
        bas = basa_ekle(bas,dizi[i]);
    }
    return bas;
}

int liste_esit_mi(const Dugum *bas, const int *beklenen, int n){
    for(int i = 0; i<n; i++){
        if (bas == NULL) return 0;
        if(bas->veri != beklenen[i]) return 0;
        bas = bas->sonraki;
    }
    return bas == NULL;
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


void test_bos_listeden_silme(void){
    Dugum *bas = NULL;

    bas = sil(bas, 5);

    assert(bas == NULL);
}


void test_ortadan_silme(void){
    int baslangic[] = {10, 20, 30};
    int beklenen[] = {10, 30};

    Dugum *bas = diziden_listele(baslangic, 3);

    bas = sil(bas, 20);

    assert(liste_esit_mi(bas, beklenen, 2));
    listeyi_sil(bas);
}

void test_sondan_silme(void){
    int baslangic[] = {10, 20, 30};
    int beklenen[] = {10, 20};

    Dugum *bas = diziden_listele(baslangic, 3);

    bas = sil(bas, 30);

    assert(liste_esit_mi(bas, beklenen, 2));
    listeyi_sil(bas);
}

void test_olmayan_deger(void){
    int baslangic[] = {10, 20, 30};

    Dugum *bas = diziden_listele(baslangic, 3);

    bas = sil(bas, 99);

    assert(liste_esit_mi(bas, baslangic, 3));
    listeyi_sil(bas);
}

void test_tekrarli_deger(void){
    int baslangic[] = {10, 20, 20, 30};
    int beklenen[]  = {10, 20, 30};
    Dugum *bas = diziden_listele(baslangic, 4);

    bas = sil(bas, 20);

    assert(liste_esit_mi(bas, beklenen, 3));
    listeyi_sil(bas);
}

void test_bastan_silme(void){
    int baslangic[] = {10, 20, 30};
    int beklenen[] = {20, 30};

    Dugum *bas = diziden_listele(baslangic, 3);

    bas = sil(bas, 10);
    assert(liste_esit_mi(bas, beklenen, 2));
    listeyi_sil(bas);
}

void test_tek_elemanli_listeden_silme(void){

    int baslangic[] = {5};

    Dugum *bas = diziden_listele(baslangic, 1);
    bas = sil(bas, 5);

    assert(bas == NULL);
}


int main (void) {
    test_bos_listeden_silme();
    test_ortadan_silme();
    test_sondan_silme();
    test_olmayan_deger();
    test_tekrarli_deger();
    printf("Tüm testler geçti!");

    return 0;
}