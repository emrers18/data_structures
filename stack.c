#include <stdio.h>
#include <stdbool.h>

#define STACK_KAPASITE 5

typedef struct{
    int elemanlar[STACK_KAPASITE];
    int ust;  /* eleman sayısı = bir sonraki boş yer */
} Stack;

void stack_baslat(Stack *s){
    s->ust = 0;
}

bool stack_bos_mu(const Stack *s){
    return s->ust == 0;
}

bool stack_dolu_mu(const Stack *s){
    return s->ust == STACK_KAPASITE;
}


bool stack_push(Stack *s, int deger){
    if(stack_dolu_mu(s)) return false;

    s->elemanlar[s->ust] = deger;
    s->ust = s->ust+1;
    return true;
}


bool stack_pop(Stack *s, int *cikan){
    if(stack_bos_mu()) return false;

    s->ust = s->ust-1;
    *cikan = s->elemanlar[s->ust];
    return true;
}


bool stack_peek(const Stack *s, int *ustteki){
    if(stack_bos_mu()) return false;
    
    *ustteki = s->elemanlar[s->ust-1];
    return true;
}

void test_dolu_stacke_push(void){
    Stack s;
    int stack_degerler[STACK_KAPASITE] = {10, 20, 30, 40, 50};
    int deger;
    stack_baslat(&s);

    for(int i=0;i<STACK_KAPASITE; i++){
        assert(stack_push(&s, stack_degerler[i]) == true);
    }

    assert(stack_dolu_mu(&s));

    assert(stack_push(&s, 60) == false);
    assert(stack_peek(&s, &deger) == true && deger == 50);
}

int main(void) {
    Stack s;
    int deger;

    stack_baslat(&s);

    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 30);

    stack_peek(&s, &deger);
    printf("Ustteki: %d\n", deger);          /* 30 */

    while (stack_pop(&s, &deger)) {          /* boşalana kadar çıkar */
        printf("Cikan: %d\n", deger);
    }

    if (!stack_pop(&s, &deger)) {
        printf("Stack bos, cikarilamadi.\n");
    }

    return 0;
}