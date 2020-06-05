//
// Created by Flowko on 13.05.2020.
//

#ifndef SWE1_DE_LIST_H
#define SWE1_DE_LIST_H
#include "stdbool.h"

struct MEM_UNIT{
    char * name;
    bool occupied; //ist diese Adresse belegt?
    int len; //Wv Adressen danach sind belegt?
    struct MEM_UNIT *Next;
    struct MEM_UNIT *Prev;
};
typedef struct MEM_UNIT MEM_NODE;

struct MEM_UNIT_HEADER {
    int size; //Größe des Heaps
    char strategy; // 'n' --> Next Fit, 'f' --> First Fit, 'b' --> Best Fit
    MEM_NODE * First;
    MEM_NODE * Last;
};
typedef struct MEM_UNIT_HEADER MEM_MAN;

extern MEM_MAN * create_mem_man(int, char);
extern MEM_NODE * insertFirst(MEM_MAN *);
extern void deleteFirst(MEM_MAN *);
extern void term_mem(MEM_MAN *header);


#endif //SWE1_DE_LIST_H

