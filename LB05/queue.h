//
// Created by Inderjit on 05.06.2020.
//

#ifndef TEAM_ITS_PRO_PROGRAMMERS_QUEUE_H
#define TEAM_ITS_PRO_PROGRAMMERS_QUEUE_H
#include "stdbool.h"

struct QUEUE_UNIT{
    char * type; //'p' --> Producer, 'c' --> consumer
    int len; //Length of threads, which are going to be produced or consumed
    struct QUEUE_UNIT *Next;
    struct QUEUE_UNIT *Prev;
};
typedef struct QUEUE_UNIT QUEUE_NODE;

struct QUEUE_UNIT_HEADER {
    int size; //Size of buffer
    QUEUE_NODE * First;
    QUEUE_NODE * Last;
};
typedef struct QUEUE_UNIT_HEADER QUEUE_HEAD;

extern QUEUE_HEAD * create_mem_man(int);
extern QUEUE_NODE * insertFirst(QUEUE_HEAD *);
extern void deleteLast(QUEUE_HEAD *);
extern void term_mem(QUEUE_HEAD *header);

#endif //TEAM_ITS_PRO_PROGRAMMERS_QUEUE_H
