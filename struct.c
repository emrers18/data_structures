#include <stdio.h>

typedef struct {
    int numara;
    int notu;
} Ogrenci;

Ogrenci ali = {101, 85};
Ogrenci *p = &ali;

*p.notu = 95; /* 1. yol: p'nin gösterdiği yere git, oradaki notu al */
p->notu = 95; /* 2. yol: aynı şeyin kısa yazımı */

void not_arttir(Ogrenci *o, int miktar){
    o->notu = o->notu + miktar;
}

int main(void){
    Ogrenci emre = {1081, 95};
    not_arttir(&emre, 5);

    printf("Ogrenci Notu: %d\n", emre.notu);

    return 0;
}