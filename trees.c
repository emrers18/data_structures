#include <stdlib.h>

// İkili Ağaç (Binary Tree)
typedef struct AgacDugum{
    int veri;
    struct AgacDugum *sol; // sol çocuk
    struct AgacDugum *sag; // sağ çocuk
} AgacDugum;

// Her düğümde aradığın değeri karşılaştırırsın.
// Küçükse sola, büyükse sağa gidersin.
// Diğer taraf tamamen elenir.
AgacDugum *agacta_ara(AgacDugum *kok, int aranan){
    AgacDugum *simdiki = kok;

    while(simdiki != NULL){
        if(aranan == simdiki->veri){
            return simdiki;
        }
        if(aranan < simdiki->veri){
            simdiki = simdiki->sol;
        }else{
            simdiki = simdiki->sag;
        }
    }
    return NULL;
}


AgacDugum *agac_dugum_olustur(int deger){
    AgacDugum *yeni = malloc(sizeof(AgacDugum));

    if(yeni == NULL) return NULL;

    yeni->veri = deger;
    yeni->sol = NULL;
    yeni->sag = NULL;
    return yeni;
}

AgacDugum *agaca_ekle(AgacDugum *kok, int deger){
    AgacDugum *yeni = agac_dugum_olustur(deger);

    if(yeni == NULL) return kok;

    if(kok == NULL) return yeni;

    AgacDugum *simdiki = kok;
    while(1){
        if(deger < simdiki->veri){
            if(simdiki->sol == NULL){
                simdiki->sol = yeni;
                break;
            }
            simdiki = simdiki->sol;
        }else{
            if(simdiki->sag == NULL){
                simdiki->sag = yeni;
                break;
            }
            simdiki = simdiki->sag;
        }
    }
    return kok;
}

void inorder_yazdir(const AgacDugum *d){
    if (d==NULL) return;

    inorder_yazdir(d->sol);
    printf("%d ", d->veri);
    inorder_yazdir(d->sag);
}

void post_order_agaci_sil(AgacDugum *d){
    if(d==NULL) return;

    post_order_agaci_sil(d->sol);
    post_order_agaci_sil(d->sag);
    free(d);
}