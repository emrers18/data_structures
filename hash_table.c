#include <stdint.h>
#include <stdbool.h>

#define TABLO_BOYUTU 8

typedef struct {
    uint32_t anahtar;
    int deger;
    bool dolu;
} Kayit;


static Kayit tablo[TABLO_BOYUTU];

void tablo_baslat(void){
    for(int i = 0; i<TABLO_BOYUTU; i++){
        tablo[i].dolu = false;
    }
}

bool tablo_ekle(uint32_t anahtar, int deger){
    uint32_t i = anahtar % TABLO_BOYUTU;

    for(int deneme = 0; deneme<TABLO_BOYUTU; deneme++){
        if(!tablo[i].dolu){
            tablo[i].anahtar = anahtar;
            tablo[i].deger = deger;
            tablo[i].dolu = true;
            return true;
        }

        if(tablo[i].anahtar == anahtar){
            tablo[i].deger = deger;
            return true;
        }
        i = (i + 1) % TABLO_BOYUTU;
    }
    return false;
}


bool tablo_bul(uint32_t anahtar, int *deger){
    uint32_t i = anahtar % TABLO_BOYUTU;

    for(int deneme =0; deneme<TABLO_BOYUTU; deneme++){
        if(!tablo[i].dolu){
            return false;
        }
        if(tablo[i].anahtar == anahtar){
            *deger = tablo[i].deger;
            return true;
        }
        i = (i+1) % TABLO_BOYUTU;
    }
    return false;
}