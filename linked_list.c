#include <stdio.h>

typedef struct Dugum {
    int veri;
    struct Dugum *sonraki;
} Dugum;

int main(void){
    Dugum a, b, c;

    a.veri = 10;
    a.sonraki = &b;

    b.veri = 20;
    b.sonraki = &c;

    c.veri = 30;
    c.sonraki = NULL;

    Dugum *bas = &a;

    Dugum *simdiki = bas;
    while(simdiki != NULL){
        printf("%d\n", simdiki->veri);
        simdiki = simdiki->sonraki;
    }

    Dugum x;
    x.veri = 15;
    x.sonraki = a.sonraki;
    a.sonraki = &x;

    return 0;
}



