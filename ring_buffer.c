#include <stdbool.h>

#define KUYRUK_KAPASITE 4

typedef struct {
    int elemanlar[KUYRUK_KAPASITE];
    int yaz;     /* bir sonraki elemanın yazılacağı indeks */
    int oku;     /* bir sonraki okunacak elemanın indeksi */
    int sayi;    /* kuyrukta kaç eleman var */
} Kuyruk;


void kuyruk_baslat(Kuyruk *k) {
    k->yaz = 0;
    k->oku = 0;
    k->sayi = 0;
}

bool kuyruk_bos_mu(const Kuyruk *k) {
    return k->sayi == 0;
}

bool kuyruk_dolu_mu(const Kuyruk *k) {
    return k->sayi == KUYRUK_KAPASITE;
}

bool kuyruk_ekle(Kuyruk *k, int deger){
    if(kuyruk_dolu_mu(k)) return false;

    k->elemanlar[k->yaz] = deger;
    k->yaz = (k->yaz + 1) % KUYRUK_KAPASITE;
    k->sayi = k->sayi+1;
    return true;
}

bool kuyruk_cikar(Kuyruk *k, int *cikan){
    if(kuyruk_bos_mu(k)) return false;

    *cikan = k->elemanlar[k->oku];
    k->oku = (k->oku +1) % KUYRUK_KAPASITE;
    k->sayi = k->sayi -1;
    return true;
}

void test_dolu_kuyruga_ekleme(void){
    Kuyruk *k;
    int cikan;
    kuyruk_baslat(&k);

    for(int i = 0; i<KUYRUK_KAPASITE;i++){
        assert(kuyruk_ekle(&k,i)== true)
    }
    assert(kuyruk_dolu_mu(&k) == true);
    assert(kuyruk_ekle(&k, 99) == false)

    for(int i = 0; i<KUYRUK_KAPASITE; i++){
        assert(kuyruk_cikar(&k, &cikan) == true);
    }
    assert(kuyruk_bos_mu(&k) == true);
    assert(kuyruk_cikar(&k, &cikan) == false);

}


static Kuyruk uart_kuyrugu;
static int kayip_bayt_sayisi = 0;

void UART_interrupt_func(void){
    int gelen = UART_VERI_REGISTERI;

    if(!kuyruk_ekle(&uart_kuyrugu, gelen)){
        kayip_bayt_sayisi++;
    }
}

int main(void){
    kuyruk_baslat(&uart_kuyrugu);

    while(1){
        uint8_t bayt;
        while(kuyruk_cikar(&uart_kuyrugu, &bayt)){
            bayti_isle(bayt);
        }
        diger_isler();
    }
}