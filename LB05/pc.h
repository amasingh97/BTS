//
// Created by Inderjit on 05.06.2020.
//

#ifndef TEAM_ITS_PRO_PROGRAMMERS_PC_H
#define TEAM_ITS_PRO_PROGRAMMERS_PC_H
#include "queue.h"
#include "stdio.h"

QUEUE_HEAD * pcinit(int size); //Größe des Buffers --> max Seiten
void pcterm(QUEUE_HEAD * buffer); //free den ganzen Speicher
QUEUE_NODE * pcmalloc(QUEUE_HEAD * buffer, int len, char * type); //Bereich allozieren
void pcfree(QUEUE_NODE * to_free); //free eine Einheit
void pcdump(QUEUE_HEAD * buffer, FILE *); // printed den momentanen Buffer/*0

#endif //TEAM_ITS_PRO_PROGRAMMERS_PC_H
