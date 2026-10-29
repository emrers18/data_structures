#include <stdio.h>

int topla(int *dizi, int uzunluk){
    int toplam = 0;
    for(int i = 0; i < uzunluk; i++){
        toplam = toplam + dizi[i];
    }
    return toplam;
}


int main(void){
    int notlar[5] = {70, 85, 90, 60, 75};


    // Diziyi fonksiyona gönderdiğinde aslında sadece ilk elemanın adresi gider.
    int sonuc = topla(notlar, 5);
    printf("Toplam: %d\n", sonuc);

    return
}