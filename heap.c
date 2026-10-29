#include <stdbool.h>

#define HEAP_KAPASITE 16

typedef struct{
    int elemanlar[HEAP_KAPASITE];
    int boyut;
} MinHeap;

void heap_baslat(MinHeap *h){
    h->boyut = 0;
}

static void yer_degistir(int *a, int *b){
    int gecici = *a;
    *a = *b;
    *b = gecici;
}

bool heap_ekle(MinHeap *h, int deger) {
    if (h->boyut == HEAP_KAPASITE) {
        return false;                               /* heap dolu */
    }

    int i = h->boyut;                               /* sona koy */
    h->elemanlar[i] = deger;
    h->boyut++;

    while (i > 0) {                                 /* köke gelmediysek */
        int ebeveyn = (i - 1) / 2;
        if (h->elemanlar[i] >= h->elemanlar[ebeveyn]) {
            break;                                  /* ebeveyninden küçük değil: yerinde */
        }
        yer_degistir(&h->elemanlar[i], &h->elemanlar[ebeveyn]);
        i = ebeveyn;                                /* bir seviye yukarı çık */
    }
    return true;
}

bool heap_cikar(MinHeap *h, int *en_kucuk) {
    if (h->boyut == 0) {
        return false;                               /* heap boş */
    }

    *en_kucuk = h->elemanlar[0];                    /* 1. kökü al */
    h->boyut--;
    h->elemanlar[0] = h->elemanlar[h->boyut];       /* 2. son elemanı köke taşı */

    int i = 0;
    while (1) {                                     /* 3. aşağı taşı */
        int sol = 2 * i + 1;
        int sag = 2 * i + 2;
        int kucuk = i;                              /* şimdilik en küçük kendisi */

        if (sol < h->boyut && h->elemanlar[sol] < h->elemanlar[kucuk]) {
            kucuk = sol;
        }
        if (sag < h->boyut && h->elemanlar[sag] < h->elemanlar[kucuk]) {
            kucuk = sag;
        }
        if (kucuk == i) {
            break;                                  /* iki çocuktan da küçük: yerinde */
        }
        yer_degistir(&h->elemanlar[i], &h->elemanlar[kucuk]);
        i = kucuk;                                  /* bir seviye aşağı in */
    }
    return true;
}


bool heap_bak(const MinHeap *h, int *en_kucuk) {
    if (h->boyut == 0) {
        return false;
    }
    *en_kucuk = h->elemanlar[0];
    return true;
}

typedef struct {
    uint32_t dolma_zamani;    /* milisaniye cinsinden */
    int      kimlik;          /* hangi iş yapılacak */
} Zamanlayici;

/* Her milisaniyede çağrılır (temsili) */
void zamanlayicilari_kontrol_et(uint32_t simdiki_zaman) {
    Zamanlayici z;
    while (heap_bak(&zamanlayicilar, &z) && z.dolma_zamani <= simdiki_zaman) {
        heap_cikar(&zamanlayicilar, &z);
        isi_calistir(z.kimlik);
    }
}

bool heap_gecerli_mi(const MinHeap *h) {
    for (int i = 1; i < h->boyut; i++) {
        int ebeveyn = (i - 1) / 2;
        if (h->elemanlar[ebeveyn] > h->elemanlar[i]) {
            return false;               /* ebeveyn çocuğundan büyük: kural bozuk */
        }
    }
    return true;
}


void test_cikarma_sirasi(void) {
    MinHeap h;
    int degerler[] = {40, 10, 30, 5, 20};
    int beklenen[] = {5, 10, 20, 30, 40};
    int cikan;
    heap_baslat(&h);                                     /* Hazırla */

    for (int i = 0; i < 5; i++) {
        assert(heap_ekle(&h, degerler[i]));
        assert(heap_gecerli_mi(&h));                     /* her eklemeden sonra kural sağlam mı? */
    }

    for (int i = 0; i < 5; i++) {                        /* Çalıştır ve Doğrula */
        assert(heap_cikar(&h, &cikan));
        assert(cikan == beklenen[i]);
        assert(heap_gecerli_mi(&h));                     /* her çıkarmadan sonra kural sağlam mı? */
    }
    assert(heap_cikar(&h, &cikan) == false);             /* artık boş */
}