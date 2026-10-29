void yer_degistir(int *a, int *b){
    int gecici = *a;
    *a = *b;
    *b = gecici;
}

void bubble_sort(int *dizi, int n){
    for(int tur = 0; tur<n-1;tur++){
        bool degisti = false;
        for(int i = 0; i<n-1-tur;i++){
            if(dizi[i] > dizi[i+1]){
                yer_degistir(&dizi[i], &dizi[i+1]);
                degisti = true;
            }
        }
        if(!degisti) break;
    }
}

void insertion_sort(int *dizi, int n){
    for(int i=1; i<n; i++){
        int anahtar = dizi[i];
        int j = i-1;

        while(j>=0 && dizi[j] > anahtar){
            dizi[j+1] = dizi[j];
            j--;
        }
        dizi[j+1]=anahtar;
    }
}

// (Merge Sort)

// Fikir: Böl ve fethet.

// Diziyi ikiye böl.
// Her yarıyı ayrı ayrı sırala (aynı yöntemle, yani yine ikiye bölerek).
// Sıralı iki yarıyı birleştir.


static int bolumle(int *dizi, int bas, int son) {
    int pivot = dizi[son];
    int i = bas - 1;                       /* küçükler bölgesinin sonu */

    for (int j = bas; j < son; j++) {
        if (dizi[j] <= pivot) {            /* pivottan küçük ya da eşitse */
            i++;
            yer_degistir(&dizi[i], &dizi[j]);   /* küçükler bölgesine al */
        }
    }
    yer_degistir(&dizi[i + 1], &dizi[son]);     /* pivotu ortaya koy */
    return i + 1;                               /* pivotun yeni yeri */
}

void hizli_siralama(int *dizi, int bas, int son) {
    if (bas >= son) {
        return;                            /* 0 ya da 1 eleman: zaten sıralı */
    }
    int p = bolumle(dizi, bas, son);
    hizli_siralama(dizi, bas, p - 1);      /* pivotun solu */
    hizli_siralama(dizi, p + 1, son);      /* pivotun sağı */
}

static void asagi_tasi(int *dizi, int n, int i) {
    while (1) {
        int sol = 2 * i + 1;
        int sag = 2 * i + 2;
        int buyuk = i;

        if (sol < n && dizi[sol] > dizi[buyuk]) buyuk = sol;
        if (sag < n && dizi[sag] > dizi[buyuk]) buyuk = sag;
        if (buyuk == i) break;

        yer_degistir(&dizi[i], &dizi[buyuk]);
        i = buyuk;
    }
}

void heap_siralama(int *dizi, int n) {
    /* 1. Diziyi max-heap'e çevir */
    for (int i = n / 2 - 1; i >= 0; i--) {
        asagi_tasi(dizi, n, i);
    }

    /* 2-4. En büyüğü sona koy, heap'i küçült, düzelt */
    for (int son = n - 1; son > 0; son--) {
        yer_degistir(&dizi[0], &dizi[son]);
        asagi_tasi(dizi, son, 0);
    }
}


int linear_search(const int *dizi, int n, int aranan) {
    for (int i = 0; i < n; i++) {
        if (dizi[i] == aranan) {
            return i;               /* bulunduğu indeks */
        }
    }
    return -1;                      /* bulunamadı */
}

int binary_search(const int *dizi, int n, int aranan) {
    int sol = 0;
    int sag = n - 1;

    while (sol <= sag) {
        int orta = sol + (sag - sol) / 2;     /* overflow riskini azaltır */
        if (dizi[orta] == aranan) return orta;
        if (dizi[orta] < aranan)  sol = orta + 1;    /* sağ yarıya geç */
        else                      sag = orta - 1;    /* sol yarıya geç */
    }
    return -1;                                        /* bulunamadı */
}