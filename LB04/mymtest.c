//
// Created by Flowko on 13.05.2020.
//

#include "stdio.h"
#include "stdlib.h"
#include "mym.h"
#define getName(var) #var
void Testing_Memory(MEM_MAN * heap, FILE * fp);



int main (){

    MEM_MAN * heap_first = myminit(40,'f');
    Testing_Memory(heap_first, stdout);
    MEM_MAN * heap_best = myminit(40,'b');
    Testing_Memory(heap_best, stdout);
    MEM_MAN * heap_worst = myminit(40,'w');
    Testing_Memory(heap_worst, stdout);
    MEM_MAN * heap_next = myminit(40,'n');
    Testing_Memory(heap_next, stdout);

}


void Testing_Memory (MEM_MAN * heap, FILE * fp) {

    //Ausgangssituation

    MEM_NODE * a = mymmalloc(heap,2,NULL);
    MEM_NODE * p104 = mymmalloc(heap,2,getName(p104));
    MEM_NODE * b = mymmalloc(heap,1,NULL);
    MEM_NODE * p102 = mymmalloc(heap,3,getName(p102));
    MEM_NODE * p100 = mymmalloc(heap,1,getName(p100));
    MEM_NODE * c = mymmalloc(heap,7,NULL);
    MEM_NODE * p106 = mymmalloc(heap,5,getName(p106));
    MEM_NODE * d = mymmalloc(heap,2,NULL);
    MEM_NODE * p101 = mymmalloc(heap,1,getName(p101));
    MEM_NODE * e = mymmalloc(heap,6,NULL);
    MEM_NODE * p103 = mymmalloc(heap,3,getName(p103));
    MEM_NODE * f = mymmalloc(heap,3,NULL);
    MEM_NODE * p105 = mymmalloc(heap,2,getName(p105));

    mymfree(a);
    mymfree(b);
    mymfree(c);
    mymfree(d);
    mymfree(e);
    mymfree(f);
    fprintf(fp, "\nAUSGANGSSITUATION:\n\n");
    mymdump(heap, fp);

    //Aufgabenstellung
    mymfree(p100);
    MEM_NODE * p1 = mymmalloc(heap,4,getName(p1));
    MEM_NODE * p5 = mymmalloc(heap,2,getName(p5));
    mymfree(p1);
    p1 = mymmalloc(heap,5,getName(p1));
    mymfree(p101);
    MEM_NODE * p3 = mymmalloc(heap,1,getName(p3));
    MEM_NODE * p4 = mymmalloc(heap,3,getName(p4));
    mymfree(p3);
    p3 = mymmalloc(heap,2,getName(p3));
    mymfree(p4);
    p4 = mymmalloc(heap,5,getName(p4));


    fprintf(fp, "\nNACH DEN OPERATIONEN LAUT AUFGABENSTELLUNG:\n\n");
    mymdump(heap, fp);
    mymterm(heap);

}
