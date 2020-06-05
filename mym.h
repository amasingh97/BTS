//
// Created by Flowko on 13.05.2020.
//

#ifndef SWE1_MYM_H
#define SWE1_MYM_H
#include "mem_list.h"
#include "stdio.h"

MEM_MAN * myminit(int size, char strategy); //Größe des Heaps --> max Seiten
void mymterm(MEM_MAN * heap); //free den ganzen Speicher
MEM_NODE * mymmalloc(MEM_MAN * heap, int len, char * name); //Bereich allozieren
void mymfree(MEM_NODE * to_free); //free eine Einheit
void mymdump(MEM_MAN * heap, FILE *); // printed den momentanen Heap/*0

#endif //SWE1_MYM_H
