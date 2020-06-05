//
// Created by Flowko on 13.05.2020.
//
//
// Created by Flowko on 08.05.2020.
//
#include "stdio.h"
#include "stdlib.h"
#include "mem_list.h"

extern MEM_MAN * create_mem_man(int size, char strategy){
    MEM_MAN * newHeader = malloc(sizeof(MEM_MAN));
    if(newHeader){
        newHeader->size = 0;
        newHeader->First = NULL;
        newHeader->Last = NULL;
        newHeader->strategy = strategy;

        for (int i = 0; i < size; ++i) {
            insertFirst(newHeader);
        }
        return newHeader;
    }
    else
    {
        perror("Kann keinen Speicher reservieren!");
        exit(EXIT_FAILURE);
    }
}

extern MEM_NODE * insertFirst(MEM_MAN * header){

    MEM_NODE * newWagon = calloc(sizeof(MEM_NODE), 1);
    if(newWagon){
        if(header->size == 0)
        {
            newWagon->len = 1;
            newWagon->occupied = false;
            newWagon->Next = NULL;
            newWagon->Prev = NULL;

            header->First = newWagon;
            header->Last = newWagon;
            ++header->size;

            return newWagon;
        }
        else if(header->size > 0)
            //Hauptfall
        {
            newWagon->occupied = false;
            newWagon->len = 1;
            newWagon->Next = header->First;
            newWagon->Prev = NULL;

            header->First->Prev = newWagon;
            header->First = newWagon;
            ++header->size;

            return newWagon;
        }
        else
        {
            puts("Länge negativ --> Überprüfe delete Functions");
            return NULL;
        }
    }
    else{
        fprintf(stderr,"Konnte keinen Datenwagon erzeugen");
        return NULL;
    }
}


extern void deleteFirst(MEM_MAN * header){

    if (header){
        if (!header->First && !header->Last){
            perror("Liste ist leer, kann nichts löschen!");
        }
        else if(header->size == 1){
            free(header->First);
            header->First = NULL;
            header->Last = NULL;
            --header->size;
        }
        else if(header->size > 1){
            //allgemeiner Fall
            MEM_NODE * temp = header->First->Next;
            free(header->First);
            header->First = temp;
            header->First->Prev = NULL;
            --header->size;
        }
        else{
            perror("Länge negativ");
        }
    }
    else{
        perror("Header nicht vorhanden");
    }
}


extern void term_mem(MEM_MAN * header){
    if(header) {
        int len = header->size;
        for (int i = 0; i < len; ++i) {
            deleteFirst(header);
        }
    }
    free(header);
}




